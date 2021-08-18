#include "LevelIO.h"
#include "../Utilities/Log.h"

LevelIO LevelIOCreate(ProgressBarDisplay progress)
{
	LevelIO levelIO = MemoryAllocate(sizeof(struct LevelIO));
	*levelIO = (struct LevelIO){ .ProgressBar = progress, };
	return levelIO;
}

bool LevelIOSave(LevelIO levelIO, Level level, char * filePath, char * levelName)
{
	SDL_RWops * file = SDL_RWFromFile(filePath, "wb");
	SDL_RWwrite(file, levelName, strlen(levelName) + 1, 1);
	SDL_RWwrite(file, &(uint16_t){ level->Width }, 2, 1);
	SDL_RWwrite(file, level->Blocks, level->Width * level->Height * level->Depth, 1);
	SDL_RWwrite(file, &(uint8_t){ level->WaterLevel }, 1, 1);
	SDL_RWwrite(file, &(int16_t){ level->Spawn.x }, 2, 1);
	SDL_RWwrite(file, &(int16_t){ level->Spawn.y }, 2, 1);
	SDL_RWwrite(file, &(int16_t){ level->Spawn.z }, 2, 1);
	SDL_RWclose(file);
	return false;
}

Level LevelIOLoad(LevelIO levelIO, char * filePath)
{
	SDL_RWops * file = SDL_RWFromFile(filePath, "rb");
	uint8_t byte = SDL_ReadU8(file);
	while (byte != 0) { byte = SDL_ReadU8(file); }
	uint16_t size = 0;
	SDL_RWread(file, &size, 2, 1);
	uint8_t * data = MemoryAllocate(size * size * 64);
	SDL_RWread(file, data, size * size * 64, 1);
	uint8_t waterLevel = 0;
	SDL_RWread(file, &waterLevel, 1, 1);
	uint16_t spawnX = 0, spawnY = 0, spawnZ = 0;
	SDL_RWread(file, &spawnX, 2, 1);
	SDL_RWread(file, &spawnY, 2, 1);
	SDL_RWread(file, &spawnZ, 2, 1);
	SDL_RWclose(file);
	
	Level level = LevelCreate();
	level->WaterLevel = waterLevel;
	LevelSetData(level, size, 64, size, data);
	LevelSetSpawnPosition(level, spawnX, spawnY, spawnZ, 0.0);
	
	MemoryFree(data);
	return level;
}

void LevelIODestroy(LevelIO levelIO)
{
	MemoryFree(levelIO);
}
