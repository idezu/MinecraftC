#define SOKOL_IMPL
#define SOKOL_GLCORE33
#include <sokol/sokol_gfx.h>
#include <math.h>
#include "GL1.h"

#define MATRIX_STACK_SIZE 128
#define IDENTITY_MATRIX (struct GLMatrix){ 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 }
#define STACK_ID(mode) ((mode) == GL_MODELVIEW ? 0 : ((mode) == GL_PROJECTION ? 1 : ((mode) == GL_TEXTURE ? 2 : 0)))

struct GLMatrix
{
	float M00, M10, M20, M30;
	float M01, M11, M21, M31;
	float M02, M12, M22, M32;
	float M03, M13, M23, M33;
};

static struct GLState
{
	GLenum AlphaFunc;
	GLclampf AlphaReference;
	bool Began;
	GLclampd ClearDepth;
	GLenum CullFace;
	GLenum DepthFunc;
	GLenum ErrorCode;
	GLenum MatrixMode;
	GLenum ShadeModel;
	
	struct GLMatrix MatrixStack[3][MATRIX_STACK_SIZE];
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
} GL =
{
	.AlphaFunc = GL_ALWAYS,
	.AlphaReference = 0.0f,
	.ClearDepth = 1.0f,
	.CullFace = GL_BACK,
	.DepthFunc = GL_LESS,
	.Enabled.Dither = true,
	.MatrixMode = GL_MODELVIEW,
	.ShadeModel = GL_SMOOTH,
	
	.MatrixStack = { { IDENTITY_MATRIX }, { IDENTITY_MATRIX }, { IDENTITY_MATRIX } },
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
	if (!SetEnable(cap, true)) { GL.ErrorCode = GL_INVALID_ENUM; }
}

void glDisable(GLenum cap)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	if (!SetEnable(cap, false)) { GL.ErrorCode = GL_INVALID_ENUM; }
}

void glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	if (zNear < 0.0 || zFar < 0.0) { GL.ErrorCode = GL_INVALID_VALUE; return; }
	double a = (right + left) / (right - left);
	double b = (top + bottom) / (top - bottom);
	double c = -(zFar + zNear) / (zFar - zNear);
	double d = -(2.0 * zFar * zNear) / (zFar - zNear);
	double e = (2.0 * zNear) / (right - left);
	double f = (2.0 * zNear) / (top - bottom);
	glMultMatrixf((float []){ e, 0.0, 0.0, 0.0, 0.0, f, 0.0, 0.0, a, b, c, 1.0, 0.0, 0.0, d, 0.0 });
}

GLenum glGetError()
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return 0; }
	return GL.ErrorCode;
}

void glLoadIdentity()
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	GL.MatrixStack[STACK_ID(GL.MatrixMode)][GL.MatrixSP[STACK_ID(GL.MatrixMode)]] = IDENTITY_MATRIX;
}

void glLoadMatrixd(const GLdouble * m)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	GL.MatrixStack[STACK_ID(GL.MatrixMode)][GL.MatrixSP[STACK_ID(GL.MatrixMode)]] = (struct GLMatrix)
	{
		m[0], m[4], m[8], m[12],
		m[1], m[5], m[9], m[13],
		m[2], m[6], m[10], m[14],
		m[3], m[7], m[11], m[15],
	};
}

void glLoadMatrixf(const GLfloat * m)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	GL.MatrixStack[STACK_ID(GL.MatrixMode)][GL.MatrixSP[STACK_ID(GL.MatrixMode)]] = (struct GLMatrix)
	{
		m[0], m[4], m[8], m[12],
		m[1], m[5], m[9], m[13],
		m[2], m[6], m[10], m[14],
		m[3], m[7], m[11], m[15],
	};
}

void glMatrixMode(GLenum mode)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	if (mode == GL_MODELVIEW || mode == GL_PROJECTION || mode == GL_TEXTURE) { GL.MatrixMode = mode; }
	else { GL.ErrorCode = GL_INVALID_ENUM; }
}

static struct GLMatrix MatrixMultiply(struct GLMatrix l, struct GLMatrix r)
{
	return (struct GLMatrix)
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

void glMultMatrixf(const GLfloat * m)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	struct GLMatrix matrix =
	{
		m[0], m[4], m[8], m[12],
		m[1], m[5], m[9], m[13],
		m[2], m[6], m[10], m[14],
		m[3], m[7], m[11], m[15],
	};
	int i = STACK_ID(GL.MatrixMode);
	GL.MatrixStack[i][GL.MatrixSP[i]] = MatrixMultiply(GL.MatrixStack[i][GL.MatrixSP[i]], matrix);
}

void glMultMatrixd(const GLdouble * m)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	struct GLMatrix matrix =
	{
		m[0], m[4], m[8], m[12],
		m[1], m[5], m[9], m[13],
		m[2], m[6], m[10], m[14],
		m[3], m[7], m[11], m[15],
	};
	int i = STACK_ID(GL.MatrixMode);
	GL.MatrixStack[i][GL.MatrixSP[i]] = MatrixMultiply(GL.MatrixStack[i][GL.MatrixSP[i]], matrix);
}

void glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	double a = 2.0 / (right - left);
	double b = 2.0 / (top - bottom);
	double c = -2.0 / (zFar - zNear);
	double tx = -(right + left) / (right - left);
	double ty = -(top + bottom) / (top - bottom);
	double tz = -(zFar + zNear) / (zFar - zNear);
	glMultMatrixf((float []){ a, 0.0, 0.0, 0.0, 0.0, b, 0.0, 0.0, 0.0, 0.0, c, 0.0, tx, ty, tz, 1.0 });
}

void glPushMatrix()
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	int i = STACK_ID(GL.MatrixMode);
	if (GL.MatrixSP[i] == MATRIX_STACK_SIZE - 1) { GL.ErrorCode = GL_STACK_OVERFLOW; return; }
	GL.MatrixStack[i][GL.MatrixSP[i] + 1] = GL.MatrixStack[i][GL.MatrixSP[i]];
	GL.MatrixSP[i]++;
}

void glPopMatrix()
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	int i = STACK_ID(GL.MatrixMode);
	if (GL.MatrixSP[i] == 0) { GL.ErrorCode = GL_STACK_UNDERFLOW; return; }
	GL.MatrixSP[i]--;
}

void glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
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
	glMultMatrixf(matrix);
}

void glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	glRotated(angle, x, y, z);
}

void glScaled(GLdouble x, GLdouble y, GLdouble z)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	glMultMatrixf((float []){ x, 0.0, 0.0, 0.0, 0.0, y, 0.0, 0.0, 0.0, 0.0, z, 0.0, 0.0, 0.0, 0.0, 1.0 });
}

void glScalef(GLfloat x, GLfloat y, GLfloat z)
{
	glScaled(x, y, z);
}

void glShadeModel(GLenum mode)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	if (mode == GL_SMOOTH || mode == GL_FLAT) { GL.ShadeModel = mode; }
	else { GL.ErrorCode = GL_INVALID_ENUM; }
}

void glTranslated(GLdouble x, GLdouble y, GLdouble z)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	glMultMatrixf((float []){ 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, x, y, z, 1.0 });
}

void glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
	glTranslated(x, y, z);
}

void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	if (GL.Began) { GL.ErrorCode = GL_INVALID_OPERATION; return; }
	double f = 1.0 / tan((fovy / 2.0) * M_PI / 180.0);
	float matrix[16] =
	{
		f / aspect, 0.0, 0.0, 0.0,
		0.0, f, 0.0, 0.0,
		0.0, 0.0, (zFar + zNear) / (zNear - zFar), -1.0,
		0.0, 0.0, (2.0 * zFar * zNear) / (zNear - zFar), 0.0
	};
	glMultMatrixf(matrix);
}
