#include "audio.h"

#define MAX_TRACKS 15

typedef struct Music {
	Mix_Music* track[MAX_TRACKS];
	char* filepath[MAX_TRACKS];
	int index;
};

struct Music music;

void initAudio()
{
	SDL_Init(SDL_INIT_AUDIO);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		printf("Error: ", Mix_GetError());

	music.index = 0;
}

void music_play(char *filepath, int repeats)
{
	bool found = false;
	for (int i = 0; i < music.index; i++) {
		if (strcmp(filepath, music.filepath[i])) {
			found = true;
			Mix_PlayMusic(music.track[i], 1);
		}
	}
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


