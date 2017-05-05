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
Mix_Chunk *flawlessVictory;

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
	flawlessVictory = Mix_LoadWAV("audio/sounds/QuakeSounds/flawless.wav");
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

void sound_quake_roundStart()			//kanske inte kommer användas?
{
	
}

void sound_quake_firstblood()
{
	Mix_PlayChannel(-1, firstBlood[rand() % 4], 0);
}

void sound_quake_doublekill()
{
	Mix_PlayChannel(-1, doubleKill[rand() % 2], 0);					//random sound
}

void sound_quake_suicide()	//call when player commits suicide, for appropriate sound
{
	Mix_PlayChannel(-1, suicide[rand()%4], 0);					//random sound
}
void sound_quake_flawlessVictory()			//flawless victory = kill every other oponent
{
	Mix_PlayChannel(-1, flawlessVictory, 0);
}


