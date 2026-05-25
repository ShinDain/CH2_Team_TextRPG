#include "pch.h"
#include "UI/AnimationFrameData.h"

static const std::vector<std::string> SlimeIdle1 =
{
	"             ______             ",
	"          .-'      '-.          ",
	"        .'  o      o  '.        ",
	"       /                \\       ",
	"      |       ____       |      ",
	"      |      \\____/      |      ",
	"       \\                /       ",
	"        '.            .'        ",
	"          '-.______.-'          "
};

static const std::vector<std::string> SlimeIdle2 =
{
	"             ______             ",
	"          .-'      '-.          ",
	"        .'  o      o  '.        ",
	"       /                \\       ",
	"      |        __        |      ",
	"      |      \\____/      |      ",
	"       \\                /       ",
	"        '.            .'        ",
	"          '-.______.-'          "
};

static const std::vector<std::string> SlimeDead =
{
	"             ______             ",
	"          .-'      '-.          ",
	"        .'  X      X  '.        ",
	"       /                \\       ",
	"      |       ____       |      ",
	"      |        --        |      ",
	"       \\                /       ",
	"        '.            .'        ",
	"          '-.______.-'          "
};

static const std::vector<std::string> HitEffect =
{
	"      *** HIT! ***      "
};

const std::vector<std::string>& AnimationFrameData::GetSlimeIdle1()
{
	return SlimeIdle1;
}

const std::vector<std::string>& AnimationFrameData::GetSlimeIdle2()
{
	return SlimeIdle2;
}

const std::vector<std::string>& AnimationFrameData::GetSlimeDead()
{
	return SlimeDead;
}

const std::vector<std::string>& AnimationFrameData::GetHitEffect()
{
	return HitEffect;
}
