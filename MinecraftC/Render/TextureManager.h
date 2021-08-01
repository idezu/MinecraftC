#pragma once
#include "../Utilities/List.h"
#include "../GameSettings.h"
#include "Texture/AnimatedTexture.h"
#include <sokol/sokol_gfx.h>

typedef struct TextureManager
{
	list(sg_image) Textures;
	list(char *) TextureNames;
	unsigned char * TextureBuffer;
	list(AnimatedTexture) Animations;
	GameSettings Settings;
} * TextureManager;

TextureManager TextureManagerCreate(GameSettings settings);
sg_image TextureManagerLoad(TextureManager textures, char * resource);
void TextureManagerReload(TextureManager manager);
void TextureManagerRegisterAnimation(TextureManager textures, AnimatedTexture texture);
void TextureManagerDestroy(TextureManager textures);
