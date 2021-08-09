#include <string.h>
#include "TextureManager.h"
#include "../Utilities/Log.h"
#include "../Utilities/OpenGL.h"

#include "../../Resources/GUI/GUI.h"
#include "../../Resources/GUI/Icons.h"
#include "../../Resources/Clouds.h"
#include "../../Resources/Default.h"
#include "../../Resources/Dirt.h"
#include "../../Resources/Particles.h"
#include "../../Resources/Rain.h"
#include "../../Resources/Rock.h"
#include "../../Resources/Terrain.h"
#include "../../Resources/Water.h"

TextureManager TextureManagerCreate(GameSettings settings)
{
	TextureManager manager = MemoryAllocate(sizeof(struct TextureManager));
	*manager = (struct TextureManager)
	{
		.Settings = settings,
		.Animations = ListCreate(sizeof(AnimatedTexture)),
		.TextureBuffer = MemoryAllocate(512 * 512),
		.Textures = ListCreate(sizeof(unsigned int)),
		.TextureNames = ListCreate(sizeof(char *)),
	};
	return manager;
}

int TextureManagerLoad(TextureManager manager, char * resource)
{
	bool loaded = false;
	int index = -1;
	for (int i = 0; i < ListCount(manager->TextureNames); i++)
	{
		if (strcmp(manager->TextureNames[i], resource) == 0) { loaded = true; index = i; }
	}
	if (loaded) { return manager->Textures[index]; }
	
	int width = 0, height = 0;
	uint8_t * p = NULL;
	if (strcmp(resource, "Clouds.png") == 0) { p = Resource_Clouds_RGBA; width = Resource_Clouds_Width; height = Resource_Clouds_Height; }
	if (strcmp(resource, "Default.png") == 0) { p = Resource_Default_RGBA; width = Resource_Default_Width; height = Resource_Default_Height; }
	if (strcmp(resource, "Dirt.png") == 0) { p = Resource_Dirt_RGBA; width = Resource_Dirt_Width; height = Resource_Dirt_Height; }
	if (strcmp(resource, "Particles.png") == 0) { p = Resource_Particles_RGBA; width = Resource_Particles_Width; height = Resource_Particles_Height; }
	if (strcmp(resource, "Rain.png") == 0) { p = Resource_Rain_RGBA; width = Resource_Rain_Width; height = Resource_Rain_Height; }
	if (strcmp(resource, "Rock.png") == 0) { p = Resource_Rock_RGBA; width = Resource_Rock_Width; height = Resource_Rock_Height; }
	if (strcmp(resource, "Terrain.png") == 0) { p = Resource_Terrain_RGBA; width = Resource_Terrain_Width; height = Resource_Terrain_Height; }
	if (strcmp(resource, "Water.png") == 0) { p = Resource_Water_RGBA; width = Resource_Water_Width; height = Resource_Water_Height; }
	if (strcmp(resource, "GUI/GUI.png") == 0) { p = Resource_GUI_GUI_RGBA; width = Resource_GUI_GUI_Width; height = Resource_GUI_GUI_Height; }
	if (strcmp(resource, "GUI/Icons.png") == 0) { p = Resource_GUI_Icons_RGBA; width = Resource_GUI_Icons_Width; height = Resource_GUI_Icons_Height; }
	if (p == NULL) { LogFatal("Failed to load image %s.\n", resource); }
	
	uint8_t * pixels = malloc(4 * width * height);
	if (manager->Settings->Anaglyph)
	{
		for (int i = 0; i < 4 * width * height; i += 4)
		{
			Color color = { (p[i + 0] * 30 + p[i + 1] * 59 + p[i + 2] * 11) / 100, (p[i + 0] * 30 + p[i + 1] * 70) / 100, (p[i + 0] * 30 + p[i + 2] * 70) / 100, p[i + 3] };
			memcpy(pixels + i, &color, sizeof(Color));
		}
	}
	else { memcpy(pixels, p, 4 * width * height); }
	
	gl1GenTextures(1, &manager->IDBuffer);
	gl1BindTexture(GL1_TEXTURE_2D, manager->IDBuffer);
	gl1TexParameteri(GL1_TEXTURE_2D, GL1_TEXTURE_MIN_FILTER, GL1_NEAREST);
	gl1TexParameteri(GL1_TEXTURE_2D, GL1_TEXTURE_MAG_FILTER, GL1_NEAREST);
	gl1TexImage2D(GL1_TEXTURE_2D, 0, GL1_RGBA, width, height, 0, GL1_RGBA, GL1_UNSIGNED_BYTE, pixels);
	free(pixels);
	
	manager->TextureNames = ListPush(manager->TextureNames, &resource);
	manager->Textures = ListPush(manager->Textures, &manager->IDBuffer);
	return manager->IDBuffer;
}

void TextureManagerReload(TextureManager manager)
{
	for (int i = 0; i < ListCount(manager->Textures); i++) { gl1DeleteTextures(1, &manager->Textures[i]); }
	manager->Textures = ListClear(manager->Textures);
	manager->TextureNames = ListClear(manager->TextureNames);
}

void TextureManagerRegisterAnimation(TextureManager manager, AnimatedTexture texture)
{
	manager->Animations = ListPush(manager->Animations, &texture);
	AnimatedTextureAnimate(texture);
}

void TextureManagerDestroy(TextureManager manager)
{
	ListDestroy(manager->Textures);
	ListDestroy(manager->TextureNames);
	ListDestroy(manager->Animations);
	MemoryFree(manager->TextureBuffer);
	MemoryFree(manager);
}

