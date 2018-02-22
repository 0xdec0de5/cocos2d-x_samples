#pragma once

#include <string>

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
    Explosion_Success,
    Explosion_Fail
    
};

static const std::string music_theme = "music/theme.mp3";

static const std::string sound_explosion_bad = "sound/explosion_bad.mp3";
static const std::string sound_explosion_good = "sound/explosion_good.mp3";

static const std::string sound_arrow_shot = "sound/arrow-shot.mp3";
static const std::string sound_explosion_mutant = "sound/mutant_explode.mp3";
static const std::string sound_explosion_exploded = "sound/explosion_exploded.mp3";
static const std::string sound_explosion_grenade = "sound/explosion_grenade.mp3";
static const std::string sound_explosion_evolved = "sound/explosion_evolved.mp3";
static const std::string sound_explosion_mutation = "sound/explosion_mutation.mp3";

static const std::string sound_speed = "sound/speed_start.mp3";
static const std::string sound_speed_finished = "sound/speed_finish.mp3";
static const std::string sound_score = "sound/score.mp3";
static const std::string sound_pain = "sound/pain.mp3";
static const std::string sound_explosion_pain_evolved = "sound/pain_evolved.mp3";
static const std::string sound_pain_immune = "sound/pain_immune.mp3";
static const std::string sound_damage = "sound/damage.mp3";
static const std::string sound_pacman = "sound/wow.mp3";//change
static const std::string sound_health = "sound/umm.mp3";
static const std::string sound_time = "sound/time.mp3";//change
static const std::string sound_tick = "sound/tick.mp3";
static const std::string sound_rogue_tick = "sound/rogue_tick.mp3";
static const std::string sound_powerend = "sound/timeup.mp3";
static const std::string sound_slomo_reload = "sound/slomo_reload.mp3";
static const std::string sound_slomo_expired = "sound/slomo_expire.mp3";
static const std::string sound_slomo_begin = "sound/slomo_begin.mp3";

static const std::string sound_rogue_pain = "sound/pain_evolved.mp3";
