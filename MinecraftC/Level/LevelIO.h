#pragma once
#include <SDL2/SDL_rwops.h>
#include "../ProgressBarDisplay.h"
#include "Level.h"

typedef struct LevelIO
{
	ProgressBarDisplay ProgressBar;
} * LevelIO;

LevelIO LevelIOCreate(ProgressBarDisplay progress);
bool LevelIOSave(LevelIO levelIO, Level level, char * file, char * levelName);
Level LevelIOLoad(LevelIO levelIO, char * file);
void LevelIODestroy(LevelIO levelIO);
