#include "pch.h"
#include "UI/CharacterCreateScreen.h"
#include "UI/ConsoleRenderer.h"
#include "Manager/InputManager.h"

void CharacterCreateScreen::DrawJobSelectionScreen(const std::vector<CharacterJobData>& Jobs)
{
	ConsoleRenderer::ClearScreen();
	ConsoleRenderer::DrawBox(45, 6, 120, 34);
	ConsoleRenderer::SetCursorPosition(92, 8);
	GInput << "직업 선택";

	for (int i = 0; i < static_cast<int>(Jobs.size()); i++)
	{
		const CharacterJobData& Job = Jobs[i];
		const int Y = 12 + (i * 7);

		ConsoleRenderer::SetCursorPosition(52, Y);
		GInput << i + 1 << ". " << Job.JobName;
		ConsoleRenderer::SetCursorPosition(52, Y + 1);
		GInput << Job.Description;
		ConsoleRenderer::SetCursorPosition(52, Y + 3);
		GInput << "HP " << Job.Stats.Health
			<< " / MP " << Job.Stats.Mana
			<< " / ATK " << Job.Stats.Attack
			<< " / DEF " << Job.Stats.Defense
			<< " / SPD " << Job.Stats.ActionSpeed;
	}

	ConsoleRenderer::SetCursorPosition(52, 37);
	GInput << "직업 번호 입력 >> ";
}
