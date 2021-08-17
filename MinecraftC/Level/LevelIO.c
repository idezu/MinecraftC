#include "LevelIO.h"

LevelIO LevelIOCreate(ProgressBarDisplay progress)
{
	LevelIO levelIO = MemoryAllocate(sizeof(struct LevelIO));
	*levelIO = (struct LevelIO){ .ProgressBar = progress, };
	return levelIO;
}

bool LevelIOSave(LevelIO levelIO, Level level, char * file, char * levelName)
{
	ProgressBarDisplaySetText(levelIO->ProgressBar, "Failed!");
	return false;
}

Level LevelIOLoad(LevelIO levelIO, char * file)
{
	ProgressBarDisplaySetText(levelIO->ProgressBar, "Failed!");
	return NULL;
}

void LevelIODestroy(LevelIO levelIO)
{
	MemoryFree(levelIO);
}
