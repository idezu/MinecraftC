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
	for (int i = 0; i < ListCount(screen->Buttons); i++) { ButtonDestroy(screen->Buttons[i]); }
	screen->Buttons = ListClear(screen->Buttons);
	
	for (int i = 0; i < 5; i++)
	{
		screen->Buttons = ListPush(screen->Buttons, &(Button){ ButtonCreate(i, screen->Width / 2 - 100, screen->Height / 6 + i * 24, "---") });
		
		String filePath = StringConcatFront(screen->Minecraft->WorkingDirectory, StringConcat(StringConcatFront("Saves/Level", StringCreateFromInt(i)), ".dat"));
		SDL_RWops * file = SDL_RWFromFile(filePath, "rb");
		if (file != NULL)
		{
			String levelName = StringCreate("");
			char byte = SDL_ReadU8(file);
			while (byte != 0)
			{
				levelName = StringConcat(levelName, (char[]){ byte, '\0' });
				byte = SDL_ReadU8(file);
			}
			screen->Buttons[i]->Text = StringSet(screen->Buttons[i]->Text, levelName);
			StringDestroy(levelName);
			SDL_RWclose(file);
		}
		else { screen->Buttons[i]->Active = false; }
		StringDestroy(filePath);
	}
	screen->Buttons = ListPush(screen->Buttons, &(Button){ ButtonCreate(5, screen->Width / 2 - 100, screen->Height / 6 + 132, "Export level...") });
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
		if (button->ID == 5) { LoadLevelScreenPortLevel(screen, ""); }
		if (button->ID == 6) { MinecraftSetCurrentScreen(screen->Minecraft, this->Parent); }
	}
}

void LoadLevelScreenOpenLevel(LoadLevelScreen screen, int id)
{
	if (screen->Type == GUIScreenTypeSaveLevel) { SaveLevelScreenOpenLevel(screen, id); return; }
	String filePath = StringConcatFront(screen->Minecraft->WorkingDirectory, StringConcat(StringConcatFront("Saves/Level", StringCreateFromInt(id)), ".dat"));
	MinecraftSetLevel(screen->Minecraft, LevelIOLoad(screen->Minecraft->LevelIO, filePath));
	StringDestroy(filePath);
	MinecraftSetCurrentScreen(screen->Minecraft, NULL);
	MinecraftGrabMouse(screen->Minecraft);
}

void LoadLevelScreenPortLevel(LoadLevelScreen screen, char * file)
{
	if (screen->Type == GUIScreenTypeSaveLevel) { SaveLevelScreenPortLevel(screen, file); return; }
}

void LoadLevelScreenOnClose(LoadLevelScreen screen)
{
}

void LoadLevelScreenRender(LoadLevelScreen screen, int2 mousePos)
{
	LoadLevelScreenData this = screen->TypeData;
	ScreenDrawFadingBox((int2){ 0, 0 }, (int2){ screen->Width, screen->Height }, ColorFromHex(0x05050060), ColorFromHex(0x303060A0));
	ScreenDrawCenteredString(screen->Font, this->Title, (int2){ screen->Width / 2, 20 }, ColorWhite);
	
	GUIScreenType type = screen->Type;
	screen->Type = GUIScreenTypeNone;
	GUIScreenRender(screen, mousePos);
	screen->Type = type;
	
	if (screen->Type == GUIScreenTypeSaveLevel) { SaveLevelScreenRender(screen, mousePos); return; }
}

void LoadLevelScreenDestroy(LoadLevelScreen screen)
{
	LoadLevelScreenData this = screen->TypeData;
	MemoryFree(this);
}
