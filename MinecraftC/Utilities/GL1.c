#include <stdbool.h>
#include <math.h>
#include "GL1.h"

#define MATRIX_STACK_SIZE 128
#define IDENTITY_MATRIX (struct GL1Matrix){ 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 }
#define STACK_ID(mode) ((mode) == GL1_MODELVIEW ? 0 : ((mode) == GL1_PROJECTION ? 1 : ((mode) == GL1_TEXTURE ? 2 : 0)))

struct GL1Matrix
{
	float M00, M10, M20, M30;
	float M01, M11, M21, M31;
	float M02, M12, M22, M32;
	float M03, M13, M23, M33;
};

static struct GL1State
{
	GL1enum AlphaFunc;
	GL1clampf AlphaReference;
	bool Began;
	GL1clampd ClearDepth;
	GL1enum CullFace;
	GL1enum DepthFunc;
	GL1enum ErrorCode;
	GL1enum MatrixMode;
	GL1enum ShadeModel;
	
	struct GL1Matrix MatrixStack[3][MATRIX_STACK_SIZE];
	int MatrixSP[3];
	
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
} GL1 =
{
	.AlphaFunc = GL1_ALWAYS,
	.AlphaReference = 0.0f,
	.ClearDepth = 1.0f,
	.CullFace = GL1_BACK,
	.DepthFunc = GL1_LESS,
	.Enabled.Dither = true,
	.MatrixMode = GL1_MODELVIEW,
	.ShadeModel = GL1_SMOOTH,
	
	.MatrixStack = { { IDENTITY_MATRIX }, { IDENTITY_MATRIX }, { IDENTITY_MATRIX } },
};

static bool SetEnable(GL1enum cap, bool enable)
{
	switch (cap)
	{
		case GL1_ALPHA_TEST: GL1.Enabled.AlphaTest = enable; return true;
		case GL1_AUTO_NORMAL: GL1.Enabled.AutoNormal = enable; return true;
		case GL1_BLEND: GL1.Enabled.Blend = enable; return true;
		case GL1_CLIP_PLANE0: GL1.Enabled.ClipPlane[0] = enable; return true;
		case GL1_CLIP_PLANE1: GL1.Enabled.ClipPlane[1] = enable; return true;
		case GL1_CLIP_PLANE2: GL1.Enabled.ClipPlane[2] = enable; return true;
		case GL1_CLIP_PLANE3: GL1.Enabled.ClipPlane[3] = enable; return true;
		case GL1_CLIP_PLANE4: GL1.Enabled.ClipPlane[4] = enable; return true;
		case GL1_CLIP_PLANE5: GL1.Enabled.ClipPlane[5] = enable; return true;
		case GL1_COLOR_LOGIC_OP: GL1.Enabled.ColorLogicOP = enable; return true;
		case GL1_COLOR_MATERIAL: GL1.Enabled.ColorMaterial = enable; return true;
		case GL1_CULL_FACE: GL1.Enabled.CullFace = enable; return true;
		case GL1_DEPTH_TEST: GL1.Enabled.DepthTest = enable; return true;
		case GL1_DITHER: GL1.Enabled.Dither = enable; return true;
		case GL1_FOG: GL1.Enabled.Fog = enable; return true;
		case GL1_INDEX_LOGIC_OP: GL1.Enabled.IndexLogicOP = enable; return true;
		case GL1_LIGHT0: GL1.Enabled.Light[0] = enable; return true;
		case GL1_LIGHT1: GL1.Enabled.Light[1] = enable; return true;
		case GL1_LIGHT2: GL1.Enabled.Light[2] = enable; return true;
		case GL1_LIGHT3: GL1.Enabled.Light[3] = enable; return true;
		case GL1_LIGHT4: GL1.Enabled.Light[4] = enable; return true;
		case GL1_LIGHT5: GL1.Enabled.Light[5] = enable; return true;
		case GL1_LIGHT6: GL1.Enabled.Light[6] = enable; return true;
		case GL1_LIGHT7: GL1.Enabled.Light[7] = enable; return true;
		case GL1_LIGHTING: GL1.Enabled.Lighting = enable; return true;
		case GL1_LINE_SMOOTH: GL1.Enabled.LineSmooth = enable; return true;
		case GL1_NORMALIZE: GL1.Enabled.Normalize = enable; return true;
		case GL1_POINT_SMOOTH: GL1.Enabled.PointSmooth = enable; return true;
		case GL1_POLYGON_OFFSET_FILL: GL1.Enabled.PolygonOffsetFill = enable; return true;
		case GL1_POLYGON_OFFSET_LINE: GL1.Enabled.PolygonOffsetLine = enable; return true;
		case GL1_POLYGON_OFFSET_POINT: GL1.Enabled.PolygonOffsetPoint = enable; return true;
		case GL1_POLYGON_SMOOTH: GL1.Enabled.PolygonSmooth = enable; return true;
		case GL1_SCISSOR_TEST: GL1.Enabled.ScissorTest = enable; return true;
		case GL1_STENCIL_TEST: GL1.Enabled.StencilTest = enable; return true;
		case GL1_TEXTURE_1D: GL1.Enabled.Texture1D = enable; return true;
		case GL1_TEXTURE_2D: GL1.Enabled.Texture2D = enable; return true;
		case GL1_TEXTURE_GEN_Q: GL1.Enabled.TextureGenQ = enable; return true;
		case GL1_TEXTURE_GEN_R: GL1.Enabled.TextureGenR = enable; return true;
		case GL1_TEXTURE_GEN_S: GL1.Enabled.TextureGenS = enable; return true;
		case GL1_TEXTURE_GEN_T: GL1.Enabled.TextureGenT = enable; return true;
		default: return false;
	}
}

void gl1AlphaFunc(GL1enum func, GL1clampf ref)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	if (func < GL1_NEVER || func > GL1_ALWAYS) { GL1.ErrorCode = GL1_INVALID_ENUM; }
	else
	{
		GL1.AlphaFunc = func;
		GL1.AlphaReference = ref > 1.0 ? 1.0 : (ref < 0.0 ? 0.0 : ref);
	}
}

void gl1ClearDepth(GL1clampd depth)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	GL1.ClearDepth = depth > 1.0 ? 1.0 : (depth < 0.0 ? 0.0 : depth);
}

void gl1CullFace(GL1enum mode)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	if (mode == GL1_BACK || mode == GL1_FRONT || mode == GL1_FRONT_AND_BACK) { GL1.CullFace = mode; }
	else { GL1.ErrorCode = GL1_INVALID_ENUM; }
}

void gl1DepthFunc(GL1enum func)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	if (func < GL1_NEVER || func > GL1_ALWAYS) { GL1.ErrorCode = GL1_INVALID_ENUM; }
	else { GL1.DepthFunc = func; }
}

void gl1Enable(GL1enum cap)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	if (!SetEnable(cap, true)) { GL1.ErrorCode = GL1_INVALID_ENUM; }
}

void gl1Disable(GL1enum cap)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	if (!SetEnable(cap, false)) { GL1.ErrorCode = GL1_INVALID_ENUM; }
}

void gl1Frustum(GL1double left, GL1double right, GL1double bottom, GL1double top, GL1double zNear, GL1double zFar)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	if (zNear < 0.0 || zFar < 0.0) { GL1.ErrorCode = GL1_INVALID_VALUE; return; }
	double a = (right + left) / (right - left);
	double b = (top + bottom) / (top - bottom);
	double c = -(zFar + zNear) / (zFar - zNear);
	double d = -(2.0 * zFar * zNear) / (zFar - zNear);
	double e = (2.0 * zNear) / (right - left);
	double f = (2.0 * zNear) / (top - bottom);
	gl1MultMatrixf((float []){ e, 0.0, 0.0, 0.0, 0.0, f, 0.0, 0.0, a, b, c, 1.0, 0.0, 0.0, d, 0.0 });
}

GL1enum gl1GetError()
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return 0; }
	return GL1.ErrorCode;
}

void gl1LoadIdentity()
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	GL1.MatrixStack[STACK_ID(GL1.MatrixMode)][GL1.MatrixSP[STACK_ID(GL1.MatrixMode)]] = IDENTITY_MATRIX;
}

void gl1LoadMatrixd(const GL1double * m)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	GL1.MatrixStack[STACK_ID(GL1.MatrixMode)][GL1.MatrixSP[STACK_ID(GL1.MatrixMode)]] = (struct GL1Matrix)
	{
		m[0], m[4], m[8], m[12],
		m[1], m[5], m[9], m[13],
		m[2], m[6], m[10], m[14],
		m[3], m[7], m[11], m[15],
	};
}

void gl1LoadMatrixf(const GL1float * m)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	GL1.MatrixStack[STACK_ID(GL1.MatrixMode)][GL1.MatrixSP[STACK_ID(GL1.MatrixMode)]] = (struct GL1Matrix)
	{
		m[0], m[4], m[8], m[12],
		m[1], m[5], m[9], m[13],
		m[2], m[6], m[10], m[14],
		m[3], m[7], m[11], m[15],
	};
}

void gl1MatrixMode(GL1enum mode)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	if (mode == GL1_MODELVIEW || mode == GL1_PROJECTION || mode == GL1_TEXTURE) { GL1.MatrixMode = mode; }
	else { GL1.ErrorCode = GL1_INVALID_ENUM; }
}

static struct GL1Matrix MatrixMultiply(struct GL1Matrix l, struct GL1Matrix r)
{
	return (struct GL1Matrix)
	{
		r.M00 * l.M00 + r.M10 * l.M01 + r.M20 * l.M02 + r.M30 * l.M03,
		r.M00 * l.M10 + r.M10 * l.M11 + r.M20 * l.M12 + r.M30 * l.M13,
		r.M00 * l.M20 + r.M10 * l.M21 + r.M20 * l.M22 + r.M30 * l.M23,
		r.M00 * l.M30 + r.M10 * l.M31 + r.M20 * l.M32 + r.M30 * l.M33,
		r.M01 * l.M00 + r.M11 * l.M01 + r.M21 * l.M02 + r.M31 * l.M03,
		r.M01 * l.M10 + r.M11 * l.M11 + r.M21 * l.M12 + r.M31 * l.M13,
		r.M01 * l.M20 + r.M11 * l.M21 + r.M21 * l.M22 + r.M31 * l.M23,
		r.M01 * l.M30 + r.M11 * l.M31 + r.M21 * l.M32 + r.M31 * l.M33,
		r.M02 * l.M00 + r.M12 * l.M01 + r.M22 * l.M02 + r.M32 * l.M03,
		r.M02 * l.M10 + r.M12 * l.M11 + r.M22 * l.M12 + r.M32 * l.M13,
		r.M02 * l.M20 + r.M12 * l.M21 + r.M22 * l.M22 + r.M32 * l.M23,
		r.M02 * l.M30 + r.M12 * l.M31 + r.M22 * l.M32 + r.M32 * l.M33,
		r.M03 * l.M00 + r.M13 * l.M01 + r.M23 * l.M02 + r.M33 * l.M03,
		r.M03 * l.M10 + r.M13 * l.M11 + r.M23 * l.M12 + r.M33 * l.M13,
		r.M03 * l.M20 + r.M13 * l.M21 + r.M23 * l.M22 + r.M33 * l.M23,
		r.M03 * l.M30 + r.M13 * l.M31 + r.M23 * l.M32 + r.M33 * l.M33,
	};
}

void gl1MultMatrixf(const GL1float * m)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	struct GL1Matrix matrix =
	{
		m[0], m[4], m[8], m[12],
		m[1], m[5], m[9], m[13],
		m[2], m[6], m[10], m[14],
		m[3], m[7], m[11], m[15],
	};
	int i = STACK_ID(GL1.MatrixMode);
	GL1.MatrixStack[i][GL1.MatrixSP[i]] = MatrixMultiply(GL1.MatrixStack[i][GL1.MatrixSP[i]], matrix);
}

void gl1MultMatrixd(const GL1double * m)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	struct GL1Matrix matrix =
	{
		m[0], m[4], m[8], m[12],
		m[1], m[5], m[9], m[13],
		m[2], m[6], m[10], m[14],
		m[3], m[7], m[11], m[15],
	};
	int i = STACK_ID(GL1.MatrixMode);
	GL1.MatrixStack[i][GL1.MatrixSP[i]] = MatrixMultiply(GL1.MatrixStack[i][GL1.MatrixSP[i]], matrix);
}

void gl1Ortho(GL1double left, GL1double right, GL1double bottom, GL1double top, GL1double zNear, GL1double zFar)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	double a = 2.0 / (right - left);
	double b = 2.0 / (top - bottom);
	double c = -2.0 / (zFar - zNear);
	double tx = -(right + left) / (right - left);
	double ty = -(top + bottom) / (top - bottom);
	double tz = -(zFar + zNear) / (zFar - zNear);
	gl1MultMatrixf((float []){ a, 0.0, 0.0, 0.0, 0.0, b, 0.0, 0.0, 0.0, 0.0, c, 0.0, tx, ty, tz, 1.0 });
}

void gl1PushMatrix()
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	int i = STACK_ID(GL1.MatrixMode);
	if (GL1.MatrixSP[i] == MATRIX_STACK_SIZE - 1) { GL1.ErrorCode = GL1_STACK_OVERFLOW; return; }
	GL1.MatrixStack[i][GL1.MatrixSP[i] + 1] = GL1.MatrixStack[i][GL1.MatrixSP[i]];
	GL1.MatrixSP[i]++;
}

void gl1PopMatrix()
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	int i = STACK_ID(GL1.MatrixMode);
	if (GL1.MatrixSP[i] == 0) { GL1.ErrorCode = GL1_STACK_UNDERFLOW; return; }
	GL1.MatrixSP[i]--;
}

void gl1Rotated(GL1double angle, GL1double x, GL1double y, GL1double z)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	double dist = sqrt(x * x + y * y + z * z);
	x /= dist;
	y /= dist;
	z /= dist;
	double c = cos(angle * M_PI / 180.0);
	double s = sin(angle * M_PI / 180.0);
	float matrix[16] =
	{
		x * x * (1.0 - c) + c, y * x * (1.0 - c) + z * s, z * x * (1.0 - c) - y * s, 0.0,
		x * y * (1.0 - c) - z * s, y * y * (1.0 - c) + c, z * y * (1.0 - c) + x * s, 0.0,
		x * z * (1.0 - c) + y * s, y * z * (1.0 - c) - x * s, z * z * (1.0 - c) + c, 0.0,
		0.0, 0.0, 0.0, 1.0,
	};
	gl1MultMatrixf(matrix);
}

void gl1Rotatef(GL1float angle, GL1float x, GL1float y, GL1float z)
{
	gl1Rotated(angle, x, y, z);
}

void gl1Scaled(GL1double x, GL1double y, GL1double z)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	gl1MultMatrixf((float []){ x, 0.0, 0.0, 0.0, 0.0, y, 0.0, 0.0, 0.0, 0.0, z, 0.0, 0.0, 0.0, 0.0, 1.0 });
}

void gl1Scalef(GL1float x, GL1float y, GL1float z)
{
	gl1Scaled(x, y, z);
}

void gl1ShadeModel(GL1enum mode)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	if (mode == GL1_SMOOTH || mode == GL1_FLAT) { GL1.ShadeModel = mode; }
	else { GL1.ErrorCode = GL1_INVALID_ENUM; }
}

void gl1Translated(GL1double x, GL1double y, GL1double z)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	gl1MultMatrixf((float []){ 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, x, y, z, 1.0 });
}

void gl1Translatef(GL1float x, GL1float y, GL1float z)
{
	gl1Translated(x, y, z);
}

void gl1uPerspective(GL1double fovy, GL1double aspect, GL1double zNear, GL1double zFar)
{
	if (GL1.Began) { GL1.ErrorCode = GL1_INVALID_OPERATION; return; }
	double f = 1.0 / tan((fovy / 2.0) * M_PI / 180.0);
	float matrix[16] =
	{
		f / aspect, 0.0, 0.0, 0.0,
		0.0, f, 0.0, 0.0,
		0.0, 0.0, (zFar + zNear) / (zNear - zFar), -1.0,
		0.0, 0.0, (2.0 * zFar * zNear) / (zNear - zFar), 0.0
	};
	gl1MultMatrixf(matrix);
}
