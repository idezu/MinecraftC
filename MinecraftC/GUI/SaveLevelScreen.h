#pragma once
#include "LoadLevelScreen.h"

typedef LoadLevelScreen SaveLevelScreen;

SaveLevelScreen SaveLevelScreenCreate(GUIScreen parent);
void SaveLevelScreenOnOpen(SaveLevelScreen screen);
void SaveLevelScreenOpenLevel(SaveLevelScreen screen, int level);
void SaveLevelScreenPortLevel(SaveLevelScreen screen, char * file);
void SaveLevelScreenRender(SaveLevelScreen screen, int2 mousePos);
