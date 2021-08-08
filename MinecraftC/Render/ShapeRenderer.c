#include <OpenGL.h>
#include "ShapeRenderer.h"
#include "../Utilities/Memory.h"
#include "../Utilities/Log.h"

struct ShapeRenderer ShapeRenderer = { 0 };
static int MaxFloats = 524288;

void ShapeRendererInitialize()
{
	ShapeRenderer.Buffer = MemoryAllocate(MaxFloats * sizeof(float));
	ShapeRenderer.Vertices = 0;
	ShapeRenderer.HasColor = false;
	ShapeRenderer.HasTexture = false;
	ShapeRenderer.VertexLength = 3;
	ShapeRenderer.Length = 0;
	ShapeRenderer.NoColor = false;
}

void ShapeRendererBegin()
{
	ShapeRendererClear();
	ShapeRenderer.HasTexture = false;
	ShapeRenderer.HasColor = false;
	ShapeRenderer.NoColor = false;
}

void ShapeRendererEnd()
{
	if (ShapeRenderer.Vertices > 0)
	{
		if (ShapeRenderer.HasTexture && ShapeRenderer.HasColor) { gl1InterleavedArrays(GL1_T2F_C3F_V3F, 0, ShapeRenderer.Buffer); }
		else if (ShapeRenderer.HasTexture) { gl1InterleavedArrays(GL1_T2F_V3F, 0, ShapeRenderer.Buffer); }
		else if (ShapeRenderer.HasColor) { gl1InterleavedArrays(GL1_C3F_V3F, 0, ShapeRenderer.Buffer); }
		else { gl1InterleavedArrays(GL1_V3F, 0, ShapeRenderer.Buffer); }
		
		gl1EnableClientState(GL1_VERTEX_ARRAY);
		if (ShapeRenderer.HasTexture) { gl1EnableClientState(GL1_TEXTURE_COORD_ARRAY); }
		if (ShapeRenderer.HasColor) { gl1EnableClientState(GL1_COLOR_ARRAY); }
		
		gl1DrawArrays(GL1_QUADS, 0, ShapeRenderer.Vertices);
		gl1DisableClientState(GL1_VERTEX_ARRAY);
		if (ShapeRenderer.HasTexture) { gl1DisableClientState(GL1_TEXTURE_COORD_ARRAY); }
		if (ShapeRenderer.HasColor) { gl1DisableClientState(GL1_COLOR_ARRAY); }
	}
	
	ShapeRendererClear();
}

void ShapeRendererClear()
{
	ShapeRenderer.Vertices = 0;
	ShapeRenderer.Length = 0;
}

void ShapeRendererColor(float3 color)
{
	if (!ShapeRenderer.NoColor)
	{
		if (!ShapeRenderer.HasColor) { ShapeRenderer.VertexLength += 3; }
		ShapeRenderer.HasColor = true;
		ShapeRenderer.RGB = color;
	}
}

void ShapeRendererVertexUV(float3 vertex, float2 uv)
{
	if (!ShapeRenderer.HasTexture) { ShapeRenderer.VertexLength += 2; }
	ShapeRenderer.HasTexture = true;
	ShapeRenderer.UV = uv;
	ShapeRendererVertex(vertex);
}

void ShapeRendererVertex(float3 vertex)
{
	if (ShapeRenderer.HasTexture)
	{
		ShapeRenderer.Buffer[ShapeRenderer.Length++] = ShapeRenderer.UV.x;
		ShapeRenderer.Buffer[ShapeRenderer.Length++] = ShapeRenderer.UV.y;
	}
	
	if (ShapeRenderer.HasColor)
	{
		ShapeRenderer.Buffer[ShapeRenderer.Length++] = ShapeRenderer.RGB.r;
		ShapeRenderer.Buffer[ShapeRenderer.Length++] = ShapeRenderer.RGB.g;
		ShapeRenderer.Buffer[ShapeRenderer.Length++] = ShapeRenderer.RGB.b;
	}
	
	ShapeRenderer.Buffer[ShapeRenderer.Length++] = vertex.x;
	ShapeRenderer.Buffer[ShapeRenderer.Length++] = vertex.y;
	ShapeRenderer.Buffer[ShapeRenderer.Length++] = vertex.z;
	
	ShapeRenderer.Vertices++;
	if (ShapeRenderer.Vertices % 4 == 0 && ShapeRenderer.Length >= MaxFloats - (ShapeRenderer.VertexLength * 4))
	{
		ShapeRendererEnd();
		ShapeRenderer.VertexLength = 3;
	}
}

void ShapeRendererNoColor()
{
	ShapeRenderer.NoColor = true;
}

void ShapeRendererNormal(float3 normal)
{
	gl1Normal3f(normal.x, normal.y, normal.z);
}

void ShapeRendererDeinitialize()
{
	MemoryFree(ShapeRenderer.Buffer);
}
