#pragma once
#include <SDL2/SDL.h>
#include "GUIScreen.h"

typedef GUIScreen LoadLevelScreen;

typedef struct LoadLevelScreenData
{
	GUIScreen Parent;
	char * Title;
	char * LevelNames[5];
} * LoadLevelScreenData;

LoadLevelScreen LoadLevelScreenCreate(GUIScreen parent);
void LoadLevelScreenOnOpen(LoadLevelScreen screen);
void LoadLevelScreenOnButtonClicked(LoadLevelScreen screen, Button button);
void LoadLevelScreenOpenLevel(LoadLevelScreen screen, int level);
void LoadLevelScreenPortLevel(LoadLevelScreen screen, char * file);
void LoadLevelScreenOnClose(LoadLevelScreen screen);
void LoadLevelScreenRender(LoadLevelScreen screen, int2 mousePos);
void LoadLevelScreenDestroy(LoadLevelScreen screen);
