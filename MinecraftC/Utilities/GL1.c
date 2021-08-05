#define SOKOL_IMPL
#define SOKOL_GLCORE33
#include <sokol/sokol_gfx.h>
#include "GL1.h"

static struct GLState
{
	GLenum AlphaFunc;
	GLclampf AlphaReference;
	bool Began;
	GLclampd ClearDepth;
	GLenum CullFace;
	GLenum DepthFunc;
	GLenum ErrorCode;
	GLenum ShadeModel;
	
	struct
	{
		bool AlphaTest:1;
		bool AutoNormal:1;
		bool Blend:1;
		bool ClipPlane[6];
		bool ColorLogicOP:1;
		bool ColorMaterial:1;
		bool CullFace:1;
		bool DepthTest:1;
		bool Dither:1;
		bool Fog:1;
		bool IndexLogicOP:1;
		bool Light[8];
		bool Lighting:1;
		bool LineSmooth:1;
		bool Normalize:1;
		bool PointSmooth:1;
		bool PolygonOffsetFill:1;
		bool PolygonOffsetLine:1;
		bool PolygonOffsetPoint:1;
		bool PolygonSmooth:1;
		bool ScissorTest:1;
		bool StencilTest:1;
		bool Texture1D:1;
		bool Texture2D:1;
		bool TextureGenQ:1;
		bool TextureGenR:1;
		bool TextureGenS:1;
		bool TextureGenT:1;
	} Enabled;
} GL =
{
	.AlphaFunc = GL_ALWAYS,
	.AlphaReference = 0.0f,
	.ClearDepth = 1.0f,
	.CullFace = GL_BACK,
	.DepthFunc = GL_LESS,
	.Enabled.Dither = true,
	.ShadeModel = GL_SMOOTH,
};

static bool SetEnable(GLenum cap, bool enable)
{
	switch (cap)
	{
		case GL_ALPHA_TEST: GL.Enabled.AlphaTest = enable; return true;
		case GL_AUTO_NORMAL: GL.Enabled.AutoNormal = enable; return true;
		case GL_BLEND: GL.Enabled.Blend = enable; return true;
		case GL_CLIP_PLANE0: GL.Enabled.ClipPlane[0] = enable; return true;
		case GL_CLIP_PLANE1: GL.Enabled.ClipPlane[1] = enable; return true;
		case GL_CLIP_PLANE2: GL.Enabled.ClipPlane[2] = enable; return true;
		case GL_CLIP_PLANE3: GL.Enabled.ClipPlane[3] = enable; return true;
		case GL_CLIP_PLANE4: GL.Enabled.ClipPlane[4] = enable; return true;
		case GL_CLIP_PLANE5: GL.Enabled.ClipPlane[5] = enable; return true;
		case GL_COLOR_LOGIC_OP: GL.Enabled.ColorLogicOP = enable; return true;
		case GL_COLOR_MATERIAL: GL.Enabled.ColorMaterial = enable; return true;
		case GL_CULL_FACE: GL.Enabled.CullFace = enable; return true;
		case GL_DEPTH_TEST: GL.Enabled.DepthTest = enable; return true;
		case GL_DITHER: GL.Enabled.Dither = enable; return true;
		case GL_FOG: GL.Enabled.Fog = enable; return true;
		case GL_INDEX_LOGIC_OP: GL.Enabled.IndexLogicOP = enable; return true;
		case GL_LIGHT0: GL.Enabled.Light[0] = enable; return true;
		case GL_LIGHT1: GL.Enabled.Light[1] = enable; return true;
		case GL_LIGHT2: GL.Enabled.Light[2] = enable; return true;
		case GL_LIGHT3: GL.Enabled.Light[3] = enable; return true;
		case GL_LIGHT4: GL.Enabled.Light[4] = enable; return true;
		case GL_LIGHT5: GL.Enabled.Light[5] = enable; return true;
		case GL_LIGHT6: GL.Enabled.Light[6] = enable; return true;
		case GL_LIGHT7: GL.Enabled.Light[7] = enable; return true;
		case GL_LIGHTING: GL.Enabled.Lighting = enable; return true;
		case GL_LINE_SMOOTH: GL.Enabled.LineSmooth = enable; return true;
		case GL_NORMALIZE: GL.Enabled.Normalize = enable; return true;
		case GL_POINT_SMOOTH: GL.Enabled.PointSmooth = enable; return true;
		case GL_POLYGON_OFFSET_FILL: GL.Enabled.PolygonOffsetFill = enable; return true;
		case GL_POLYGON_OFFSET_LINE: GL.Enabled.PolygonOffsetLine = enable; return true;
		case GL_POLYGON_OFFSET_POINT: GL.Enabled.PolygonOffsetPoint = enable; return true;
		case GL_POLYGON_SMOOTH: GL.Enabled.PolygonSmooth = enable; return true;
		case GL_SCISSOR_TEST: GL.Enabled.ScissorTest = enable; return true;
		case GL_STENCIL_TEST: GL.Enabled.StencilTest = enable; return true;
		case GL_TEXTURE_1D: GL.Enabled.Texture1D = enable; return true;
		case GL_TEXTURE_2D: GL.Enabled.Texture2D = enable; return true;
		case GL_TEXTURE_GEN_Q: GL.Enabled.TextureGenQ = enable; return true;
		case GL_TEXTURE_GEN_R: GL.Enabled.TextureGenR = enable; return true;
		case GL_TEXTURE_GEN_S: GL.Enabled.TextureGenS = enable; return true;
		case GL_TEXTURE_GEN_T: GL.Enabled.TextureGenT = enable; return true;
		default: return false;
	}
}

void glAlphaFunc(GLenum func, GLclampf ref)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	if (func < GL_NEVER || func > GL_ALWAYS) { GL.ErrorCode = GL_INVALID_ENUM; }
	else
	{
		GL.AlphaFunc = func;
		GL.AlphaReference = ref > 1.0 ? 1.0 : (ref < 0.0 ? 0.0 : ref);
	}
}

void glClearDepth(GLclampd depth)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	GL.ClearDepth = depth > 1.0 ? 1.0 : (depth < 0.0 ? 0.0 : depth);
}

void glCullFace(GLenum mode)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	if (mode == GL_BACK || mode == GL_FRONT || mode == GL_FRONT_AND_BACK) { GL.CullFace = mode; }
	else { GL.ErrorCode = GL_INVALID_ENUM; }
}

void glDepthFunc(GLenum func)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	if (func < GL_NEVER || func > GL_ALWAYS) { GL.ErrorCode = GL_INVALID_ENUM; }
	else { GL.DepthFunc = func; }
}

void glEnable(GLenum cap)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	if (!SetEnable(cap, true))
	{
		GL.ErrorCode = GL_INVALID_ENUM;
	}
}

void glDisable(GLenum cap)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	if (!SetEnable(cap, false))
	{
		GL.ErrorCode = GL_INVALID_ENUM;
	}
}

GLenum glGetError()
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return 0; }
	return GL.ErrorCode;
}

void glShadeModel(GLenum mode)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	if (mode == GL_SMOOTH || mode == GL_FLAT) { GL.ShadeModel = mode; }
	else { GL.ErrorCode = GL_INVALID_ENUM; }
}
