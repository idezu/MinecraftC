#include "BlockSelectScreen.h"
#include "Screen.h"
#include "../SessionData.h"
#include "../Minecraft.h"
#include "../Level/Tile/Block.h"
#include "../Render/ShapeRenderer.h"
#include "../Utilities/OpenGL.h"

BlockSelectScreen BlockSelectScreenCreate()
{
	GUIScreen screen = GUIScreenCreate();
	screen->Type = GUIScreenTypeBlockSelect;
	screen->GrabsMouse = true;
	return screen;
}

static int GetBlockOnScreen(BlockSelectScreen screen, int2 m)
{
	for (int i = 0; i < ListCount(SessionDataAllowedBlocks); i++)
	{
		int x = screen->Width / 2 + i % 9 * 24 + -108 - 3;
		int y = screen->Height / 2 + i / 9 * 24 + -60 + 3;
		if (m.x >= x && m.x <= x + 24 && m.y >= y - 12 && m.y <= y + 12) { return i; }
	}
	return -1;
}

void BlockSelectScreenRender(BlockSelectScreen screen, int2 mouse)
{
	int blockNum = GetBlockOnScreen(screen, mouse);
	ScreenDrawFadingBox((int2){ screen->Width / 2 - 120, 30 }, (int2){ screen->Width / 2 + 120, 180 }, ColorFromHex(0x05050090), ColorFromHex(0x303060C0));
	if (blockNum >= 0)
	{
		int x = screen->Width / 2 + blockNum % 9 * 24 + -108;
		int y = screen->Height / 2 + blockNum / 9 * 24 + -60;
		ScreenDrawFadingBox((int2){ x - 3, y - 8 }, (int2){ x + 23, y + 24 - 6 }, ColorFromHex(0xFFFFFF90), ColorFromHex(0xFFFFFFC0));
	}
	ScreenDrawCenteredString(screen->Font, "Select block", (int2){ screen->Width / 2, 40 }, ColorWhite);
	
	gl1BindTexture(GL1_TEXTURE_2D, TextureManagerLoad(screen->Minecraft->TextureManager, "Terrain.png"));
	for (int i = 0; i < ListCount(SessionDataAllowedBlocks); i++)
	{
		Block block = SessionDataAllowedBlocks[i];
		gl1PushMatrix();
		int x = screen->Width / 2 + i % 9 * 24 + -108;
		int y = screen->Height / 2 + i / 9 * 24 + -60;
		gl1Translatef(x, y, 0.0);
		gl1Scalef(10.0, 10.0, 10.0);
		gl1Translatef(1.0, 0.5, 8.0);
		gl1Rotatef(-30.0, 1.0, 0.0, 0.0);
		gl1Rotatef(45.0, 0.0, 1.0, 0.0);
		if (blockNum == i) { gl1Scalef(1.6, 1.6, 1.6); }
		gl1Translatef(-1.5, 0.5, 0.5);
		gl1Scalef(-1.0, -1.0, -1.0);
		ShapeRendererBegin();
		BlockRenderFullBrightness(block);
		ShapeRendererEnd();
		gl1PopMatrix();
	}
}

void BlockSelectScreenOnMouseClicked(BlockSelectScreen screen, int x, int y, int button)
{
	if (button == SDL_BUTTON_LEFT)
	{
		InventoryReplaceSlot(((PlayerData)screen->Minecraft->Player->TypeData)->Inventory, GetBlockOnScreen(screen, (int2){ x, y }));
		MinecraftSetCurrentScreen(screen->Minecraft, NULL);
	}
}
