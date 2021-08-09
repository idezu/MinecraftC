#include "Renderer.h"
#include "../Minecraft.h"
#include "../Utilities/SinTable.h"
#include "../Utilities/OpenGL.h"

Renderer RendererCreate(Minecraft minecraft)
{
	Renderer renderer = MemoryAllocate(sizeof(struct Renderer));
	*renderer = (struct Renderer)
	{
		.Minecraft = minecraft,
		.FogColorMultiplier = 1.0,
		.DisplayActive = false,
		.FogEnd = 0.0,
		.HeldBlock = (HeldBlock){ .Minecraft = minecraft },
		.Entity = NULL,
		.Random = RandomGeneratorCreate(time(NULL)),
	};
	return renderer;
}

float3 RendererGetPlayerVector(Renderer renderer, float t)
{
	Player entity = renderer->Minecraft->Player;
	return entity->OldPosition + (entity->Position - entity->Position) * t;
}

void RendererApplyBobbing(Renderer renderer, float t)
{
	Player entity = renderer->Minecraft->Player;
	PlayerData player = entity->TypeData;
	float walk = entity->WalkDistance - entity->OldWalkDistance;
	walk = entity->WalkDistance + walk * t;
	float bob = player->OldBobbing + (player->Bobbing - player->OldBobbing) * t;
	float tilt = player->OldTilt + (player->Tilt - player->OldTilt) * t;
	gl1Translatef(tsin(walk * pi) * bob * 0.5, -fabs(tcos(walk * pi) * bob), 0.0);
	gl1Rotatef(tsin(walk * pi) * bob * 3.0, 0.0, 0.0, 1.0);
	gl1Rotatef(fabs(tcos(walk * pi + 0.2) * bob) * 5.0, 1.0, 0.0, 0.0);
	gl1Rotatef(tilt, 1.0, 0.0, 0.0);
}

void RendererSetLighting(Renderer renderer, bool lighting)
{
	if (!lighting)
	{
		gl1Disable(GL1_LIGHTING);
		gl1Disable(GL1_LIGHT0);
	}
	else
	{
		gl1Enable(GL1_LIGHTING);
		gl1Enable(GL1_LIGHT0);
		gl1Enable(GL1_COLOR_MATERIAL);
		float3 pos = normalize3f((float3){ 0.0, -1.0, 0.5 });
		gl1Lightfv(GL1_LIGHT0, GL1_POSITION, (float[]){ pos.x, pos.y, pos.z, 0.0 });
		gl1Lightfv(GL1_LIGHT0, GL1_DIFFUSE, (float[]){ 0.3, 0.3, 0.3, 1.0 });
		gl1Lightfv(GL1_LIGHT0, GL1_AMBIENT, (float[]){ 0.0, 0.0, 0.0, 1.0 });
		gl1LightModelfv(GL1_LIGHT_MODEL_AMBIENT, (float[]){ 0.7, 0.7, 0.7, 1.0 });
	}
}

void RendererEnableGUIMode(Renderer renderer)
{
	int w = renderer->Minecraft->Width * 240 / renderer->Minecraft->Height;
	int h = renderer->Minecraft->Height * 240 / renderer->Minecraft->Height;
	gl1Clear(GL1_DEPTH_BUFFER_BIT);
	gl1MatrixMode(GL1_PROJECTION);
	gl1LoadIdentity();
	gl1Ortho(0.0, w, h, 0.0, 100.0, 300.0);
	gl1MatrixMode(GL1_MODELVIEW);
	gl1LoadIdentity();
	gl1Translatef(0.0, 0.0, -200.0);
}

void RendererUpdateFog(Renderer renderer)
{
	Level level = renderer->Minecraft->Level;
	Player player = renderer->Minecraft->Player;
	gl1Fogfv(GL1_FOG_COLOR, (float *)&renderer->FogColor);
	gl1Normal3f(0.0, -1.0, 0.0);
	gl1Color4f(1.0, 1.0, 1.0, 1.0);
	Block block = Blocks.Table[LevelGetTile(level, player->Position.x, player->Position.y + 0.12, player->Position.z)];
	if (block != NULL && BlockGetLiquidType(block) != LiquidTypeNone)
	{
		LiquidType liquid = BlockGetLiquidType(block);
		gl1Fogi(GL1_FOG_MODE, GL1_EXP);
		if (liquid == LiquidTypeWater)
		{
			gl1Fogf(GL1_FOG_DENSITY, 0.1);
			float4 a = { 0.4, 0.4, 0.9, 1.0 };
			if (renderer->Minecraft->Settings->Anaglyph)
			{
				a.xyz = (float3){ a.x * 30.0 + a.y * 59.0 + a.z * 11.0, a.x * 30.0 + a.y * 70.0, a.x * 30.0 + a.z * 70.0 } / 100.0;
			}
			gl1LightModelfv(GL1_LIGHT_MODEL_AMBIENT, (float *)&a);
		}
		else if (liquid == LiquidTypeLava)
		{
			gl1Fogf(GL1_FOG_DENSITY, 2.0);
			float4 a = { 0.4, 0.3, 0.3, 1.0 };
			if (renderer->Minecraft->Settings->Anaglyph)
			{
				a.xyz = (float3){ a.x * 30.0 + a.y * 59.0 + a.z * 11.0, a.x * 30.0 + a.y * 70.0, a.x * 30.0 + a.z * 70.0 } / 100.0;
			}
			gl1LightModelfv(GL1_LIGHT_MODEL_AMBIENT, (float *)&a);
		}
	}
	else
	{
		gl1Fogi(GL1_FOG_MODE, GL1_LINEAR);
		gl1Fogf(GL1_FOG_START, 0.0);
		gl1Fogf(GL1_FOG_END, renderer->FogEnd);
		gl1LightModelfv(GL1_LIGHT_MODEL_AMBIENT, (float *)&one4f);
	}
	gl1Enable(GL1_COLOR_MATERIAL);
	gl1ColorMaterial(GL1_FRONT, GL1_AMBIENT);
}

void RendererDestroy(Renderer renderer)
{
	RandomGeneratorDestroy(renderer->Random);
	MemoryFree(renderer);
}
