#include <string.h>
#include "LoadLevelScreen.h"
#include "SaveLevelScreen.h"
#include "../Minecraft.h"
#include "Screen.h"

LoadLevelScreen LoadLevelScreenCreate(GUIScreen parent)
{
	GUIScreen screen = GUIScreenCreate();
	screen->Type = GUIScreenTypeLoadLevel;
	screen->TypeData = MemoryAllocate(sizeof(struct LoadLevelScreenData));
	LoadLevelScreenData this = screen->TypeData;
	this->Parent = parent;
	this->Title = "Load level";
	return screen;
}

void LoadLevelScreenOnOpen(LoadLevelScreen screen)
{
	for (int i = 0; i < 5; i++)
	{
		String name = StringConcatFront("Level", StringCreateFromInt(i));
		screen->Buttons = ListPush(screen->Buttons, &(Button){ ButtonCreate(i, screen->Width / 2 - 100, screen->Height / 6 + i * 24, name) });
		StringDestroy(name);
		screen->Buttons[i]->Active = false;
	}
	screen->Buttons = ListPush(screen->Buttons, &(Button){ ButtonCreate(5, screen->Width / 2 - 100, screen->Height / 6 + 132, "Load file...") });
	screen->Buttons[5]->Active = false;
	screen->Buttons = ListPush(screen->Buttons, &(Button){ ButtonCreate(6, screen->Width / 2 - 100, screen->Height / 6 + 168, "Cancel") });
	if (screen->Type == GUIScreenTypeSaveLevel) { SaveLevelScreenOnOpen(screen); return; }
}

void LoadLevelScreenOnButtonClicked(LoadLevelScreen screen, Button button)
{
	LoadLevelScreenData this = screen->TypeData;
	if (button->Active)
	{
		if (button->ID < 5) { LoadLevelScreenOpenLevel(screen, button->ID); }
		
		if (button->ID == 5)
		{
			
		}
		
		if (button->ID == 6)
		{
			MinecraftSetCurrentScreen(screen->Minecraft, this->Parent);
		}
	}
}

void LoadLevelScreenOpenLevel(LoadLevelScreen screen, int level)
{
	if (screen->Type == GUIScreenTypeSaveLevel) { SaveLevelScreenOpenLevel(screen, level); return; }
	MinecraftLoadOnlineLevel(screen->Minecraft, screen->Minecraft->Session->UserName, level);
	MinecraftSetCurrentScreen(screen->Minecraft, NULL);
	MinecraftGrabMouse(screen->Minecraft);
}

void LoadLevelScreenOpenLevelFromFile(LoadLevelScreen screen, char * file)
{
	if (screen->Type == GUIScreenTypeSaveLevel) { SaveLevelScreenOpenLevelFromFile(screen, file); return; }
	LoadLevelScreenData this = screen->TypeData;
	Level level = LevelIOLoad(screen->Minecraft->LevelIO, SDL_RWFromFile(file, "rb"));
	if (level != NULL) { MinecraftSetLevel(screen->Minecraft, level); }
	MinecraftSetCurrentScreen(screen->Minecraft, this->Parent);
}

void LoadLevelScreenOnClose(LoadLevelScreen screen)
{
	/*
	 super.onClose();
	       if(this.chooser != null) {
		  this.chooser.cancelSelection();
	       }
	 */
}

void LoadLevelScreenTick(LoadLevelScreen screen)
{
	LoadLevelScreenData this = screen->TypeData;
	/*if (this->SelectedFile != NULL)
	{
		LoadLevelScreenOpenLevelFromFile(screen, this->SelectedFile);
		this->SelectedFile = NULL;
	}*/
}

void LoadLevelScreenRender(LoadLevelScreen screen, int2 mousePos)
{
	LoadLevelScreenData this = screen->TypeData;
	ScreenDrawFadingBox((int2){ 0, 0 }, (int2){ screen->Width, screen->Height }, ColorFromHex(0x05050060), ColorFromHex(0x303060A0));
	ScreenDrawCenteredString(screen->Font, this->Title, (int2){ screen->Width / 2, 20 }, ColorWhite);
	screen->Type = GUIScreenTypeNone;
	GUIScreenRender(screen, mousePos);
	screen->Type = GUIScreenTypeLoadLevel;
	if (screen->Type == GUIScreenTypeSaveLevel) { SaveLevelScreenRender(screen, mousePos); return; }
}

void LoadLevelScreenDestroy(LoadLevelScreen screen)
{
	LoadLevelScreenData this = screen->TypeData;
	MemoryFree(this);
}
