#include "pch.h"
#include "State_Battle.h"
#include "Character/Player/Player.h"
#include "Core/GameInstance.h"
#include "Data/Character/Stat.h"
#include "Manager/InputManager.h"
#include "Manager/StateManager.h"
#include "UI/ConsoleUtil.h"
#include "UI/GameScreen.h"

namespace
{
std::vector<std::pair<int, int>> MakeMonsterPositions(int MonsterCount)
{
	std::vector<std::pair<int, int>> Positions;
	const int ClampedCount = MonsterCount < 1 ? 1 : MonsterCount;
	const int Gap = 50;
	const int CenterX = 105;
	const int StartX = CenterX - ((ClampedCount - 1) * Gap / 2);

	for (int i = 0; i < ClampedCount; i++)
	{
		Positions.push_back({ StartX + (i * Gap), 8 });
	}

	return Positions;
}
}

State_Battle::State_Battle()
{
	Name = "Battle";
}

State_Battle::~State_Battle()
{
}

void State_Battle::Enter()
{
	GameInstance& Instance = GameInstance::GetInstance();
	const BattleStartData* StartData = Instance.GetBattleStartData();

	bInitialized = StartData != nullptr &&
		BattleSystemInst.Initialize(Instance.GetMainPlayer(), *StartData);

	if (!bInitialized)
	{
		Instance.GetLogManager().AddLog("전투 시작 데이터를 찾을 수 없습니다.");
		return;
	}

	SetupRendererFromBattleSystem();
	Instance.GetLogManager().AddLog("전투를 시작합니다.");
}

void State_Battle::Process()
{
	GameInstance& Instance = GameInstance::GetInstance();

	if (!bInitialized)
	{
		StateManager::GetInstance().ChangeState(EState::Map);
		return;
	}

	DrawBattleView();

	const std::vector<BattleSkillOption> Skills = BattleSystemInst.GetSkillOptions();
	DrawSkillInputPrompt();

	int Input = 0;
	InputSession InputResult = GInput >> Input;

	if (!InputResult)
	{
		Instance.GetLogManager().AddLog("잘못된 스킬 번호입니다.");
		GameScreen::DrawLogPanel(Instance.GetLogManager());
		return;
	}

	const int SelectedIndex = Input - 1;

	if (SelectedIndex < 0 || SelectedIndex >= static_cast<int>(Skills.size()))
	{
		Instance.GetLogManager().AddLog("잘못된 스킬 번호입니다.");
		GameScreen::DrawLogPanel(Instance.GetLogManager());
		return;
	}

	const BattleSkillOption& SelectedSkill = Skills[SelectedIndex];
	BattleTurnResult TurnResult = BattleSystemInst.UseSkill(SelectedSkill.SkillId);

	if (!TurnResult.bSkillUsed)
	{
		if (!TurnResult.Message.empty())
		{
			Instance.GetLogManager().AddLog(TurnResult.Message);
		}

		GameScreen::DrawCharacterPanel(Instance.GetMainPlayer());
		GameScreen::DrawBattleCommandPanel(BattleSystemInst.GetSkillOptions());
		ClearBattlePanelInputLine();
		GameScreen::DrawLogPanel(Instance.GetLogManager());
		return;
	}

	AddTurnLogs(TurnResult);

	if (TurnResult.bVictory)
	{
		LogManager& Log = Instance.GetLogManager();
		Player* MainPlayer = Instance.GetMainPlayer();

		if (MainPlayer != nullptr)
		{
			MainPlayer->Restore(EResourceType::Mana);
		}

		Log.AddLog("전투에서 승리했습니다.");
		Log.AddLog("마나를 모두 회복했습니다.");
	}

	PlayTurnResult(TurnResult);
	GameScreen::DrawCharacterPanel(Instance.GetMainPlayer());
	GameScreen::DrawBattleCommandPanel(BattleSystemInst.GetSkillOptions());
	ClearBattlePanelInputLine();
	GameScreen::DrawLogPanel(Instance.GetLogManager());

	if (TurnResult.bVictory)
	{
		if (BattleSystemInst.IsBossBattle())
		{
			Instance.SetEndingType(EEndingType::Clear);
			StateManager::GetInstance().ChangeState(EState::Ending);
		}
		else
		{
			StateManager::GetInstance().ChangeState(EState::Map);
		}

		return;
	}

	if (TurnResult.bDefeat)
	{
		Instance.SetEndingType(EEndingType::GameOver);
		StateManager::GetInstance().ChangeState(EState::Ending);
	}
}

void State_Battle::Exit()
{
	GameInstance::GetInstance().ClearBattleStartData();
	BattleSystemInst.Clear();
	Renderer.ClearMonsters();
	bInitialized = false;
}

void State_Battle::SetupRendererFromBattleSystem()
{
	Renderer.ClearMonsters();

	const std::vector<BattleMonsterViewData> MonsterViews = BattleSystemInst.GetMonsterViews();
	const std::vector<std::pair<int, int>> Positions = MakeMonsterPositions(static_cast<int>(MonsterViews.size()));

	for (int i = 0; i < static_cast<int>(MonsterViews.size()); i++)
	{
		const BattleMonsterViewData& Monster = MonsterViews[i];
		Renderer.AddMonster(
			Monster.Name,
			Positions[i].first,
			Positions[i].second,
			Monster.CurrentHP,
			Monster.MaxHP
		);
	}
}

void State_Battle::DrawBattleView()
{
	GameInstance& Instance = GameInstance::GetInstance();

	GameScreen::DrawCharacterPanel(Instance.GetMainPlayer());
	Renderer.DrawBattleScreen();
	GameScreen::DrawBattleCommandPanel(BattleSystemInst.GetSkillOptions());
	ClearBattlePanelInputLine();
	GameScreen::DrawLogPanel(Instance.GetLogManager());
}

void State_Battle::DrawSkillInputPrompt()
{
	ConsoleUtil::ClearArea(2, 48, 205, 1);
	ConsoleUtil::SetCursorPosition(2, 48);
	ConsoleUtil::WriteColored("사용할 스킬 번호 입력 >> ", ConsoleColor::White);
}

void State_Battle::ClearBattlePanelInputLine()
{
	ConsoleUtil::ClearArea(2, 38, 205, 1);
}

void State_Battle::AddTurnLogs(const BattleTurnResult& Result)
{
	LogManager& Log = GameInstance::GetInstance().GetLogManager();

	if (Result.SkillId == 1)
	{
		Log.AddLog("기본 공격을 했다.");
	}
	else
	{
		Log.AddLog(Result.SkillName + "을 사용했다.");
	}

	for (const BattleMonsterActionResult& MonsterHit : Result.MonsterHits)
	{
		Log.AddLog(MonsterHit.MonsterName + "에게 " + std::to_string(MonsterHit.Damage) + " 데미지를 입혔다.");

		if (MonsterHit.bKilled)
		{
			Log.AddLog(MonsterHit.MonsterName + "을 처치했다.");
		}
	}

	for (const BattlePlayerDamageResult& PlayerHit : Result.PlayerHits)
	{
		Log.AddLog(PlayerHit.MonsterName + "의 공격!");
		Log.AddLog("플레이어가 " + std::to_string(PlayerHit.Damage) + " 데미지를 받았다.");
	}

	if (!Result.Message.empty())
	{
		Log.AddLog(Result.Message);
	}
}

void State_Battle::PlayTurnResult(const BattleTurnResult& Result)
{
	for (const BattleMonsterActionResult& MonsterHit : Result.MonsterHits)
	{
		if (MonsterHit.MonsterIndex < 0)
		{
			continue;
		}

		Renderer.SetMonsterHP(MonsterHit.MonsterIndex, MonsterHit.CurrentHP);
		Renderer.PlayMonsterHitAnimation(MonsterHit.MonsterIndex);
	}

	for (const BattlePlayerDamageResult& PlayerHit : Result.PlayerHits)
	{
		if (PlayerHit.MonsterIndex < 0)
		{
			continue;
		}

		Renderer.PlayMonsterAttackAnimation(PlayerHit.MonsterIndex);
	}
}
