#include "audio.h"

#define MAX_TRACKS 15
#define MAX_SOUNDS 100

typedef struct Music {
	Mix_Music* track[MAX_TRACKS];
	char* filepath[MAX_TRACKS];
	int index;
};

typedef struct Sound {
	Mix_Chunk* sound[MAX_SOUNDS];
	char *filepath[MAX_SOUNDS];
	int index;
};

struct Music music;
struct Sound sound;
Mix_Chunk *suicide[4];
Mix_Chunk *doubleKill[2];
Mix_Chunk *firstBlood[3];
Mix_Chunk *multiKill;
Mix_Chunk *dominating;
Mix_Chunk *godlike;
Mix_Chunk *holyshit;

Mix_Chunk *powerupSpeed;
Mix_Chunk *powerupHP;
Mix_Chunk *powerupAtk2;
Mix_Chunk *powerupAtk3;
Mix_Chunk *laser[3];
Mix_Chunk *collision;
Mix_Chunk *explosion;
Mix_Chunk *thrusters;
Mix_Chunk *hitShip;

Mix_Music *gameMusic[3];

void initAudio()
{
	SDL_Init(SDL_INIT_AUDIO);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		printf("Error: ", Mix_GetError());

	music.index = 0;
	sound.index = 0;

	//Sound effects
	suicide[0] = Mix_LoadWAV("audio/sounds/QuakeSounds/suicide.wav");			//sound in array for easy playback
	suicide[1] = Mix_LoadWAV("audio/sounds/QuakeSounds/suicide2.wav");
	suicide[2] = Mix_LoadWAV("audio/sounds/QuakeSounds/suicide3.wav");
	suicide[3] = Mix_LoadWAV("audio/sounds/QuakeSounds/suicide4.wav");
	doubleKill[0] = Mix_LoadWAV("audio/sounds/QuakeSounds/doublekill.wav");
	doubleKill[1] = Mix_LoadWAV("audio/sounds/QuakeSounds/doublekill2.wav");
	firstBlood[0] = Mix_LoadWAV("audio/sounds/QuakeSounds/firstblood.wav");
	firstBlood[1] = Mix_LoadWAV("audio/sounds/QuakeSounds/firstblood2.wav");
	firstBlood[2] = Mix_LoadWAV("audio/sounds/QuakeSounds/firstblood3.wav");
	multiKill = Mix_LoadWAV("audio/sounds/QuakeSounds/multikill.wav");
	dominating = Mix_LoadWAV("audio/sounds/QuakeSounds/dominating.wav");
	godlike = Mix_LoadWAV("audio/sounds/QuakeSounds/godlike.wav");
	holyshit = Mix_LoadWAV("audio/sounds/QuakeSounds/holyshit.wav");

	powerupSpeed = Mix_LoadWAV("audio/sounds/powerupSpeed1.wav");
	powerupHP = Mix_LoadWAV("audio/sounds/powerupHealth.wav");
	powerupAtk2 = Mix_LoadWAV("audio/sounds/powerupAtk.wav");
	powerupAtk3 = Mix_LoadWAV("audio/sounds/powerupAtk.wav");
	laser[0] = Mix_LoadWAV("audio/sounds/projectiles/laserNormal.wav");				//normal laser pew
	laser[1] = Mix_LoadWAV("audio/sounds/projectiles/laserNormal.wav");				//shotgun laser, maybe change sound
	laser[2] = Mix_LoadWAV("audio/sounds/projectiles/minePlacement.wav");			//mine placement sound, maybe change sound?
	collision = Mix_LoadWAV("audio/sounds/collision1.wav");
	explosion = Mix_LoadWAV("audio/sounds/explosion1.wav");
	thrusters = Mix_LoadWAV("audio/sounds/thrusters.wav");
	Mix_PlayChannel(5, thrusters, -1);								//channel 100
	Mix_Pause(5);
	hitShip = Mix_LoadWAV("audio/sounds/collision1.wav");

	gameMusic[0] = Mix_LoadMUS("audio/music/music1.mp3");
	gameMusic[1] = Mix_LoadMUS("audio/music/music2.mp3");
	gameMusic[2] = Mix_LoadMUS("audio/music/music3.mp3");
}

void playMusic(char *filepath, int repeats)
{
	bool found = false;
	// First searches in the existing track list for the filepath
	for (int i = 0; i < music.index; i++) {
		if (strcmp(filepath, music.filepath[i])) {
			found = true;
			Mix_PlayMusic(music.track[i], 1);
		}
	}
	// If it's not found it tries to load the track and adds it to the list
	if (!found) {
		if (music.index < MAX_TRACKS) {
			music.track[music.index] = Mix_LoadMUS(filepath);
			if (music.track[music.index] == NULL) {
				printf("Error: failed to add track\n");
			}
			else {
				Mix_PlayMusic(music.track[music.index], repeats);
				music.index++;
			}
		}
		else {
			printf("Error: Maximum amount of tracks already added.\n");
		}
	}
}

void sound_quake_roundStart()			//this is not used.
{

}

void sound_quake_firstblood(bool muted)
{
	if (muted != true)
		Mix_PlayChannel(-1, firstBlood[rand() % 3], 0);
}

void sound_quake_doublekill(bool muted)
{
	if (muted != true)
		Mix_PlayChannel(-1, doubleKill[rand() % 2], 0);						//random sound
}
void sound_quake_suicide(bool muted)									//call when player commits suicide, for appropriate sound
{
	if (muted != true)
		Mix_PlayChannel(-1, suicide[rand() % 4], 0);					//random sound
}
void sound_quake_multikill(bool muted)									//multi kill sound
{
	if (muted != true)
		Mix_PlayChannel(-1, multiKill, 0);
}
void sound_quake_dominating(bool muted)
{
	if (muted != true)
		Mix_PlayChannel(-1, dominating, 0);
}
void sound_quake_godlike(bool muted)
{
	if (muted != true)
		Mix_PlayChannel(-1, godlike, 0);
}
void sound_quake_holyshit(bool muted)
{
	if (muted != true)
		Mix_PlayChannel(-1, holyshit, 0);
}



void sound_powerup_speed(bool muted)
{
	if (muted != true)
		Mix_PlayChannel(-1, powerupSpeed, 0);
}
void sound_powerup_hp(bool muted)
{
	if (muted != true)
		Mix_PlayChannel(-1, powerupHP, 0);
}
void sound_powerup_atk2(bool muted)
{
	if (muted != true)
		Mix_PlayChannel(-1, powerupAtk2, 0);
}
void sound_powerup_atk3(bool muted)
{
	if (muted != true)
		Mix_PlayChannel(-1, powerupAtk3, 0);
}
void sound_projectile(int type, bool muted)
{
	if (muted != true)
		Mix_PlayChannel(-1, laser[type], 0);
}
void sound_game_music(int song)								//fixa med pointers så song++
{
	Mix_PlayMusic(gameMusic[1], -1);
	//song++;
}
void sound_music_finished(int song, int timeSinceStart)
{
	int musicLengths[3];
	musicLengths[0] = 18;						//music1 in milliseconds
	musicLengths[1] = 270;						//music2 milliseconds
	int time = (timeSinceStart / 1000);

	if (time >= musicLengths[song])
	{
		printf("Song %d is over.\n", song);
		//song++;
		sound_game_music(song);
	}
	else
		printf("Song is not over.\n");
}
void sound_collision(bool muted)
{
	if (muted != true)
		Mix_PlayChannel(-1, collision, 0);
}
void sound_explosion(bool muted)
{
	SDL_Delay(50);
	if (muted != true)
		Mix_PlayChannel(-1, explosion, 0);
}
void sound_thrusters(bool muted, bool thrusting)						//INTE BRA
{
	if (muted != true && thrusting != false)
	{
		Mix_Resume(5);
		//Mix_PlayChannel(100, thrusters, -1);								//channel 100
	}
	else if (thrusting != true)
		Mix_Pause(5);
}
void sound_hitShip(bool muted)
{
	if (muted != true)
		Mix_PlayChannel(-1, hitShip, 0);
}

