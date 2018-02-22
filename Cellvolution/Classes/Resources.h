#pragma once

#include <string>

using namespace std;

enum class Color
{
	Red = 0,
	Green,
	Blue,
	None
};

enum class Sound
{
	None = 0,
	Explosion_Bad,
	Explosion_Good

};

const static string music_theme = "music/theme.mp3";

const static string sound_explosion_good = "sound/explosion_good.mp3";
const static string sound_explosion_bad = "sound/explosion_bad.mp3";