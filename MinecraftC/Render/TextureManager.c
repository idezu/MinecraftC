#include <string.h>
#include <OpenGL.h>
#include <stb_image.h>
#include "TextureManager.h"
#include "../Utilities/Log.h"

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

sg_image TextureManagerLoad(TextureManager manager, char * resource)
{
	bool loaded = false;
	int index = -1;
	for (int i = 0; i < ListCount(manager->TextureNames); i++)
	{
		if (strcmp(manager->TextureNames[i], resource) == 0) { loaded = true; index = i; }
	}
	if (loaded) { return manager->Textures[index]; }
	
	SDL_RWops * file = SDL_RWFromFile(resource, "rb");
	if (file == NULL) { LogFatal("Fialed to open file %s: %s\n", resource, SDL_GetError()); }
	int fileSize = (int)SDL_RWseek(file, 0, RW_SEEK_END);
	SDL_RWseek(file, 0, RW_SEEK_SET);
	void * fileData = MemoryAllocate(fileSize);
	SDL_RWread(file, fileData, fileSize, 1);
	SDL_RWclose(file);
	
	int width, height, channels;
	unsigned char * p = stbi_load_from_memory(fileData, fileSize, &width, &height, &channels, 4);
	if (p == NULL) { LogFatal("Failed to open file %s: %s\n", resource, stbi_failure_reason()); }
	MemoryFree(fileData);
	
	if (manager->Settings->Anaglyph)
	{
		for (int i = 0; i < 4 * width * height; i += 4)
		{
			Color color = { (p[i + 0] * 30 + p[i + 1] * 59 + p[i + 2] * 11) / 100, (p[i + 0] * 30 + p[i + 1] * 70) / 100, (p[i + 0] * 30 + p[i + 2] * 70) / 100, p[i + 3] };
			memcpy(p + i, &color, sizeof(Color));
		}
	}
	
	sg_image_desc imageInfo =
	{
		.type = SG_IMAGETYPE_2D,
		.render_target = false,
		.width = width,
		.height = height,
		.usage = SG_USAGE_IMMUTABLE,
		.pixel_format = SG_PIXELFORMAT_RGBA8,
		.min_filter = SG_FILTER_NEAREST,
		.mag_filter = SG_FILTER_NEAREST,
		.data = { .subimage[0][0] = { .ptr = p, .size = 4 * width * height } },
	};
	sg_image image = sg_make_image(&imageInfo);
	stbi_image_free(p);
	
	manager->TextureNames = ListPush(manager->TextureNames, &resource);
	manager->Textures = ListPush(manager->Textures, &image);
	return image;
}

void TextureManagerReload(TextureManager manager)
{
	for (int i = 0; i < ListCount(manager->Textures); i++) { sg_destroy_image(manager->Textures[i]); }
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

