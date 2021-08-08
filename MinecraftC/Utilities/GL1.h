#pragma once
#include <stdint.h>

/* AccumOp */
#define GL1_ACCUM                          0x0100
#define GL1_LOAD                           0x0101
#define GL1_RETURN                         0x0102
#define GL1_MULT                           0x0103
#define GL1_ADD                            0x0104

/* AlphaFunction */
#define GL1_NEVER                          0x0200
#define GL1_LESS                           0x0201
#define GL1_EQUAL                          0x0202
#define GL1_LEQUAL                         0x0203
#define GL1_GREATER                        0x0204
#define GL1_NOTEQUAL                       0x0205
#define GL1_GEQUAL                         0x0206
#define GL1_ALWAYS                         0x0207

/* AttribMask */
#define GL1_CURRENT_BIT                    0x00000001
#define GL1_POINT_BIT                      0x00000002
#define GL1_LINE_BIT                       0x00000004
#define GL1_POLYGON_BIT                    0x00000008
#define GL1_POLYGON_STIPPLE_BIT            0x00000010
#define GL1_PIXEL_MODE_BIT                 0x00000020
#define GL1_LIGHTING_BIT                   0x00000040
#define GL1_FOG_BIT                        0x00000080
#define GL1_DEPTH_BUFFER_BIT               0x00000100
#define GL1_ACCUM_BUFFER_BIT               0x00000200
#define GL1_STENCIL_BUFFER_BIT             0x00000400
#define GL1_VIEWPORT_BIT                   0x00000800
#define GL1_TRANSFORM_BIT                  0x00001000
#define GL1_ENABLE_BIT                     0x00002000
#define GL1_COLOR_BUFFER_BIT               0x00004000
#define GL1_HINT_BIT                       0x00008000
#define GL1_EVAL_BIT                       0x00010000
#define GL1_LIST_BIT                       0x00020000
#define GL1_TEXTURE_BIT                    0x00040000
#define GL1_SCISSOR_BIT                    0x00080000
#define GL1_ALL_ATTRIB_BITS                0x000fffff

/* BeginMode */
#define GL1_POINTS                         0x0000
#define GL1_LINES                          0x0001
#define GL1_LINE_LOOP                      0x0002
#define GL1_LINE_STRIP                     0x0003
#define GL1_TRIANGL1ES                      0x0004
#define GL1_TRIANGL1E_STRIP                 0x0005
#define GL1_TRIANGL1E_FAN                   0x0006
#define GL1_QUADS                          0x0007
#define GL1_QUAD_STRIP                     0x0008
#define GL1_POLYGON                        0x0009

/* BlendingFactorDest */
#define GL1_ZERO                           0
#define GL1_ONE                            1
#define GL1_SRC_COLOR                      0x0300
#define GL1_ONE_MINUS_SRC_COLOR            0x0301
#define GL1_SRC_ALPHA                      0x0302
#define GL1_ONE_MINUS_SRC_ALPHA            0x0303
#define GL1_DST_ALPHA                      0x0304
#define GL1_ONE_MINUS_DST_ALPHA            0x0305
#define GL1_DST_COLOR                      0x0306
#define GL1_ONE_MINUS_DST_COLOR            0x0307
#define GL1_SRC_ALPHA_SATURATE             0x0308

/* Boolean */
#define GL1_TRUE                           1
#define GL1_FALSE                          0

/* ClipPlaneName */
#define GL1_CLIP_PLANE0                    0x3000
#define GL1_CLIP_PLANE1                    0x3001
#define GL1_CLIP_PLANE2                    0x3002
#define GL1_CLIP_PLANE3                    0x3003
#define GL1_CLIP_PLANE4                    0x3004
#define GL1_CLIP_PLANE5                    0x3005

/* DataType */
#define GL1_BYTE                           0x1400
#define GL1_UNSIGNED_BYTE                  0x1401
#define GL1_SHORT                          0x1402
#define GL1_UNSIGNED_SHORT                 0x1403
#define GL1_INT                            0x1404
#define GL1_UNSIGNED_INT                   0x1405
#define GL1_FLOAT                          0x1406
#define GL1_2_BYTES                        0x1407
#define GL1_3_BYTES                        0x1408
#define GL1_4_BYTES                        0x1409
#define GL1_DOUBLE                         0x140A

/* DrawBufferMode */
#define GL1_NONE                           0
#define GL1_FRONT_LEFT                     0x0400
#define GL1_FRONT_RIGHT                    0x0401
#define GL1_BACK_LEFT                      0x0402
#define GL1_BACK_RIGHT                     0x0403
#define GL1_FRONT                          0x0404
#define GL1_BACK                           0x0405
#define GL1_LEFT                           0x0406
#define GL1_RIGHT                          0x0407
#define GL1_FRONT_AND_BACK                 0x0408
#define GL1_AUX0                           0x0409
#define GL1_AUX1                           0x040A
#define GL1_AUX2                           0x040B
#define GL1_AUX3                           0x040C

/* ErrorCode */
#define GL1_NO_ERROR                       0
#define GL1_INVALID_ENUM                   0x0500
#define GL1_INVALID_VALUE                  0x0501
#define GL1_INVALID_OPERATION              0x0502
#define GL1_STACK_OVERFLOW                 0x0503
#define GL1_STACK_UNDERFLOW                0x0504
#define GL1_OUT_OF_MEMORY                  0x0505
/*      GL1_TABLE_TOO_LARGE */

/* FeedBackMode */
#define GL1_2D                             0x0600
#define GL1_3D                             0x0601
#define GL1_3D_COLOR                       0x0602
#define GL1_3D_COLOR_TEXTURE               0x0603
#define GL1_4D_COLOR_TEXTURE               0x0604

/* FeedBackToken */
#define GL1_PASS_THROUGH_TOKEN             0x0700
#define GL1_POINT_TOKEN                    0x0701
#define GL1_LINE_TOKEN                     0x0702
#define GL1_POLYGON_TOKEN                  0x0703
#define GL1_BITMAP_TOKEN                   0x0704
#define GL1_DRAW_PIXEL_TOKEN               0x0705
#define GL1_COPY_PIXEL_TOKEN               0x0706
#define GL1_LINE_RESET_TOKEN               0x0707

/* FogMode */
/*      GL1_LINEAR */
#define GL1_EXP                            0x0800
#define GL1_EXP2                           0x0801

/* FrontFaceDirection */
#define GL1_CW                             0x0900
#define GL1_CCW                            0x0901

/* GetMapTarget */
#define GL1_COEFF                          0x0A00
#define GL1_ORDER                          0x0A01
#define GL1_DOMAIN                         0x0A02

/* GetTarget */
#define GL1_CURRENT_COLOR                  0x0B00
#define GL1_CURRENT_INDEX                  0x0B01
#define GL1_CURRENT_NORMAL                 0x0B02
#define GL1_CURRENT_TEXTURE_COORDS         0x0B03
#define GL1_CURRENT_RASTER_COLOR           0x0B04
#define GL1_CURRENT_RASTER_INDEX           0x0B05
#define GL1_CURRENT_RASTER_TEXTURE_COORDS  0x0B06
#define GL1_CURRENT_RASTER_POSITION        0x0B07
#define GL1_CURRENT_RASTER_POSITION_VALID  0x0B08
#define GL1_CURRENT_RASTER_DISTANCE        0x0B09
#define GL1_POINT_SMOOTH                   0x0B10
#define GL1_POINT_SIZE                     0x0B11
#define GL1_POINT_SIZE_RANGE               0x0B12
#define GL1_POINT_SIZE_GRANULARITY         0x0B13
#define GL1_LINE_SMOOTH                    0x0B20
#define GL1_LINE_WIDTH                     0x0B21
#define GL1_LINE_WIDTH_RANGE               0x0B22
#define GL1_LINE_WIDTH_GRANULARITY         0x0B23
#define GL1_LINE_STIPPLE                   0x0B24
#define GL1_LINE_STIPPLE_PATTERN           0x0B25
#define GL1_LINE_STIPPLE_REPEAT            0x0B26
#define GL1_LIST_MODE                      0x0B30
#define GL1_MAX_LIST_NESTING               0x0B31
#define GL1_LIST_BASE                      0x0B32
#define GL1_LIST_INDEX                     0x0B33
#define GL1_POLYGON_MODE                   0x0B40
#define GL1_POLYGON_SMOOTH                 0x0B41
#define GL1_POLYGON_STIPPLE                0x0B42
#define GL1_EDGE_FLAG                      0x0B43
#define GL1_CULL_FACE                      0x0B44
#define GL1_CULL_FACE_MODE                 0x0B45
#define GL1_FRONT_FACE                     0x0B46
#define GL1_LIGHTING                       0x0B50
#define GL1_LIGHT_MODEL_LOCAL_VIEWER       0x0B51
#define GL1_LIGHT_MODEL_TWO_SIDE           0x0B52
#define GL1_LIGHT_MODEL_AMBIENT            0x0B53
#define GL1_SHADE_MODEL                    0x0B54
#define GL1_COLOR_MATERIAL_FACE            0x0B55
#define GL1_COLOR_MATERIAL_PARAMETER       0x0B56
#define GL1_COLOR_MATERIAL                 0x0B57
#define GL1_FOG                            0x0B60
#define GL1_FOG_INDEX                      0x0B61
#define GL1_FOG_DENSITY                    0x0B62
#define GL1_FOG_START                      0x0B63
#define GL1_FOG_END                        0x0B64
#define GL1_FOG_MODE                       0x0B65
#define GL1_FOG_COLOR                      0x0B66
#define GL1_DEPTH_RANGE                    0x0B70
#define GL1_DEPTH_TEST                     0x0B71
#define GL1_DEPTH_WRITEMASK                0x0B72
#define GL1_DEPTH_CLEAR_VALUE              0x0B73
#define GL1_DEPTH_FUNC                     0x0B74
#define GL1_ACCUM_CLEAR_VALUE              0x0B80
#define GL1_STENCIL_TEST                   0x0B90
#define GL1_STENCIL_CLEAR_VALUE            0x0B91
#define GL1_STENCIL_FUNC                   0x0B92
#define GL1_STENCIL_VALUE_MASK             0x0B93
#define GL1_STENCIL_FAIL                   0x0B94
#define GL1_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define GL1_STENCIL_PASS_DEPTH_PASS        0x0B96
#define GL1_STENCIL_REF                    0x0B97
#define GL1_STENCIL_WRITEMASK              0x0B98
#define GL1_MATRIX_MODE                    0x0BA0
#define GL1_NORMALIZE                      0x0BA1
#define GL1_VIEWPORT                       0x0BA2
#define GL1_MODELVIEW_STACK_DEPTH          0x0BA3
#define GL1_PROJECTION_STACK_DEPTH         0x0BA4
#define GL1_TEXTURE_STACK_DEPTH            0x0BA5
#define GL1_MODELVIEW_MATRIX               0x0BA6
#define GL1_PROJECTION_MATRIX              0x0BA7
#define GL1_TEXTURE_MATRIX                 0x0BA8
#define GL1_ATTRIB_STACK_DEPTH             0x0BB0
#define GL1_CLIENT_ATTRIB_STACK_DEPTH      0x0BB1
#define GL1_ALPHA_TEST                     0x0BC0
#define GL1_ALPHA_TEST_FUNC                0x0BC1
#define GL1_ALPHA_TEST_REF                 0x0BC2
#define GL1_DITHER                         0x0BD0
#define GL1_BLEND_DST                      0x0BE0
#define GL1_BLEND_SRC                      0x0BE1
#define GL1_BLEND                          0x0BE2
#define GL1_LOGIC_OP_MODE                  0x0BF0
#define GL1_INDEX_LOGIC_OP                 0x0BF1
#define GL1_COLOR_LOGIC_OP                 0x0BF2
#define GL1_AUX_BUFFERS                    0x0C00
#define GL1_DRAW_BUFFER                    0x0C01
#define GL1_READ_BUFFER                    0x0C02
#define GL1_SCISSOR_BOX                    0x0C10
#define GL1_SCISSOR_TEST                   0x0C11
#define GL1_INDEX_CLEAR_VALUE              0x0C20
#define GL1_INDEX_WRITEMASK                0x0C21
#define GL1_COLOR_CLEAR_VALUE              0x0C22
#define GL1_COLOR_WRITEMASK                0x0C23
#define GL1_INDEX_MODE                     0x0C30
#define GL1_RGBA_MODE                      0x0C31
#define GL1_DOUBLEBUFFER                   0x0C32
#define GL1_STEREO                         0x0C33
#define GL1_RENDER_MODE                    0x0C40
#define GL1_PERSPECTIVE_CORRECTION_HINT    0x0C50
#define GL1_POINT_SMOOTH_HINT              0x0C51
#define GL1_LINE_SMOOTH_HINT               0x0C52
#define GL1_POLYGON_SMOOTH_HINT            0x0C53
#define GL1_FOG_HINT                       0x0C54
#define GL1_TEXTURE_GEN_S                  0x0C60
#define GL1_TEXTURE_GEN_T                  0x0C61
#define GL1_TEXTURE_GEN_R                  0x0C62
#define GL1_TEXTURE_GEN_Q                  0x0C63
#define GL1_INDEX_SHIFT                    0x0D12
#define GL1_INDEX_OFFSET                   0x0D13
#define GL1_RED_SCALE                      0x0D14
#define GL1_RED_BIAS                       0x0D15
#define GL1_ZOOM_X                         0x0D16
#define GL1_ZOOM_Y                         0x0D17
#define GL1_GREEN_SCALE                    0x0D18
#define GL1_GREEN_BIAS                     0x0D19
#define GL1_BLUE_SCALE                     0x0D1A
#define GL1_BLUE_BIAS                      0x0D1B
#define GL1_ALPHA_SCALE                    0x0D1C
#define GL1_ALPHA_BIAS                     0x0D1D
#define GL1_DEPTH_SCALE                    0x0D1E
#define GL1_DEPTH_BIAS                     0x0D1F
#define GL1_MAX_EVAL_ORDER                 0x0D30
#define GL1_MAX_LIGHTS                     0x0D31
#define GL1_MAX_CLIP_PLANES                0x0D32
#define GL1_MAX_TEXTURE_SIZE               0x0D33
#define GL1_MAX_PIXEL_MAP_TABLE            0x0D34
#define GL1_MAX_ATTRIB_STACK_DEPTH         0x0D35
#define GL1_MAX_MODELVIEW_STACK_DEPTH      0x0D36
#define GL1_MAX_NAME_STACK_DEPTH           0x0D37
#define GL1_MAX_PROJECTION_STACK_DEPTH     0x0D38
#define GL1_MAX_TEXTURE_STACK_DEPTH        0x0D39
#define GL1_MAX_VIEWPORT_DIMS              0x0D3A
#define GL1_MAX_CLIENT_ATTRIB_STACK_DEPTH  0x0D3B
#define GL1_SUBPIXEL_BITS                  0x0D50
#define GL1_INDEX_BITS                     0x0D51
#define GL1_RED_BITS                       0x0D52
#define GL1_GREEN_BITS                     0x0D53
#define GL1_BLUE_BITS                      0x0D54
#define GL1_ALPHA_BITS                     0x0D55
#define GL1_DEPTH_BITS                     0x0D56
#define GL1_STENCIL_BITS                   0x0D57
#define GL1_ACCUM_RED_BITS                 0x0D58
#define GL1_ACCUM_GREEN_BITS               0x0D59
#define GL1_ACCUM_BLUE_BITS                0x0D5A
#define GL1_ACCUM_ALPHA_BITS               0x0D5B
#define GL1_NAME_STACK_DEPTH               0x0D70
#define GL1_AUTO_NORMAL                    0x0D80
#define GL1_TEXTURE_1D                     0x0DE0
#define GL1_TEXTURE_2D                     0x0DE1

/* GetTextureParameter */
/*      GL1_TEXTURE_MAG_FILTER */
/*      GL1_TEXTURE_MIN_FILTER */
/*      GL1_TEXTURE_WRAP_S */
/*      GL1_TEXTURE_WRAP_T */
#define GL1_TEXTURE_WIDTH                  0x1000
#define GL1_TEXTURE_HEIGHT                 0x1001
#define GL1_TEXTURE_INTERNAL_FORMAT        0x1003
#define GL1_TEXTURE_BORDER_COLOR           0x1004
#define GL1_TEXTURE_BORDER                 0x1005
/*      GL1_TEXTURE_RED_SIZE */
/*      GL1_TEXTURE_GREEN_SIZE */
/*      GL1_TEXTURE_BLUE_SIZE */
/*      GL1_TEXTURE_ALPHA_SIZE */
/*      GL1_TEXTURE_LUMINANCE_SIZE */
/*      GL1_TEXTURE_INTENSITY_SIZE */
/*      GL1_TEXTURE_PRIORITY */
/*      GL1_TEXTURE_RESIDENT */
/*      GL1_TEXTURE_DEPTH */
/*      GL1_TEXTURE_WRAP_R */
/*      GL1_TEXTURE_MIN_LOD */
/*      GL1_TEXTURE_MAX_LOD */
/*      GL1_TEXTURE_BASE_LEVEL */
/*      GL1_TEXTURE_MAX_LEVEL */

/* HintMode */
#define GL1_DONT_CARE                      0x1100
#define GL1_FASTEST                        0x1101
#define GL1_NICEST                         0x1102

/* LightName */
#define GL1_LIGHT0                         0x4000
#define GL1_LIGHT1                         0x4001
#define GL1_LIGHT2                         0x4002
#define GL1_LIGHT3                         0x4003
#define GL1_LIGHT4                         0x4004
#define GL1_LIGHT5                         0x4005
#define GL1_LIGHT6                         0x4006
#define GL1_LIGHT7                         0x4007

/* LightParameter */
#define GL1_AMBIENT                        0x1200
#define GL1_DIFFUSE                        0x1201
#define GL1_SPECULAR                       0x1202
#define GL1_POSITION                       0x1203
#define GL1_SPOT_DIRECTION                 0x1204
#define GL1_SPOT_EXPONENT                  0x1205
#define GL1_SPOT_CUTOFF                    0x1206
#define GL1_CONSTANT_ATTENUATION           0x1207
#define GL1_LINEAR_ATTENUATION             0x1208
#define GL1_QUADRATIC_ATTENUATION          0x1209

/* ListMode */
#define GL1_COMPILE                        0x1300
#define GL1_COMPILE_AND_EXECUTE            0x1301

/* LogicOp */
#define GL1_CLEAR                          0x1500
#define GL1_AND                            0x1501
#define GL1_AND_REVERSE                    0x1502
#define GL1_COPY                           0x1503
#define GL1_AND_INVERTED                   0x1504
#define GL1_NOOP                           0x1505
#define GL1_XOR                            0x1506
#define GL1_OR                             0x1507
#define GL1_NOR                            0x1508
#define GL1_EQUIV                          0x1509
#define GL1_INVERT                         0x150A
#define GL1_OR_REVERSE                     0x150B
#define GL1_COPY_INVERTED                  0x150C
#define GL1_OR_INVERTED                    0x150D
#define GL1_NAND                           0x150E
#define GL1_SET                            0x150F

/* MaterialParameter */
#define GL1_EMISSION                       0x1600
#define GL1_SHININESS                      0x1601
#define GL1_AMBIENT_AND_DIFFUSE            0x1602
#define GL1_COLOR_INDEXES                  0x1603
/*      GL1_AMBIENT */
/*      GL1_DIFFUSE */
/*      GL1_SPECULAR */

/* MatrixMode */
#define GL1_MODELVIEW                      0x1700
#define GL1_PROJECTION                     0x1701
#define GL1_TEXTURE                        0x1702

/* PixelCopyType */
#define GL1_COLOR                          0x1800
#define GL1_DEPTH                          0x1801
#define GL1_STENCIL                        0x1802

/* PixelFormat */
#define GL1_COLOR_INDEX                    0x1900
#define GL1_STENCIL_INDEX                  0x1901
#define GL1_DEPTH_COMPONENT                0x1902
#define GL1_RED                            0x1903
#define GL1_GREEN                          0x1904
#define GL1_BLUE                           0x1905
#define GL1_ALPHA                          0x1906
#define GL1_RGB                            0x1907
#define GL1_RGBA                           0x1908
#define GL1_LUMINANCE                      0x1909
#define GL1_LUMINANCE_ALPHA                0x190A
/*      GL1_ABGR */

/* PolygonMode */
#define GL1_POINT                          0x1B00
#define GL1_LINE                           0x1B01
#define GL1_FILL                           0x1B02

/* ShadingModel */
#define GL1_FLAT                           0x1D00
#define GL1_SMOOTH                         0x1D01

/* StencilOp */
/*      GL1_ZERO */
#define GL1_KEEP                           0x1E00
#define GL1_REPLACE                        0x1E01
#define GL1_INCR                           0x1E02
#define GL1_DECR                           0x1E03
/*      GL1_INVERT */

/* StringName */
#define GL1_VENDOR                         0x1F00
#define GL1_RENDERER                       0x1F01
#define GL1_VERSION                        0x1F02
#define GL1_EXTENSIONS                     0x1F03

/* TextureCoordName */
#define GL1_S                              0x2000
#define GL1_T                              0x2001
#define GL1_R                              0x2002
#define GL1_Q                              0x2003

/* TextureEnvMode */
#define GL1_MODULATE                       0x2100
#define GL1_DECAL                          0x2101
/*      GL1_BLEND */
/*      GL1_REPLACE */

/* TextureEnvParameter */
#define GL1_TEXTURE_ENV_MODE               0x2200
#define GL1_TEXTURE_ENV_COLOR              0x2201

/* TextureEnvTarget */
#define GL1_TEXTURE_ENV                    0x2300

/* TextureGenMode */
#define GL1_EYE_LINEAR                     0x2400
#define GL1_OBJECT_LINEAR                  0x2401
#define GL1_SPHERE_MAP                     0x2402

/* TextureGenParameter */
#define GL1_TEXTURE_GEN_MODE               0x2500
#define GL1_OBJECT_PLANE                   0x2501
#define GL1_EYE_PLANE                      0x2502

/* TextureMagFilter */
#define GL1_NEAREST                        0x2600
#define GL1_LINEAR                         0x2601

/* TextureMinFilter */
/*      GL1_NEAREST */
/*      GL1_LINEAR */
#define GL1_NEAREST_MIPMAP_NEAREST         0x2700
#define GL1_LINEAR_MIPMAP_NEAREST          0x2701
#define GL1_NEAREST_MIPMAP_LINEAR          0x2702
#define GL1_LINEAR_MIPMAP_LINEAR           0x2703

/* TextureParameterName */
#define GL1_TEXTURE_MAG_FILTER             0x2800
#define GL1_TEXTURE_MIN_FILTER             0x2801
#define GL1_TEXTURE_WRAP_S                 0x2802
#define GL1_TEXTURE_WRAP_T                 0x2803
/*      GL1_TEXTURE_BORDER_COLOR */
/*      GL1_TEXTURE_PRIORITY */
/*      GL1_TEXTURE_WRAP_R */
/*      GL1_TEXTURE_MIN_LOD */
/*      GL1_TEXTURE_MAX_LOD */
/*      GL1_TEXTURE_BASE_LEVEL */
/*      GL1_TEXTURE_MAX_LEVEL */

/* TextureWrapMode */
#define GL1_CLAMP                          0x2900
#define GL1_REPEAT                         0x2901
/*      GL1_CLAMP_TO_EDGE */

/* polygon_offset */
#define GL1_POLYGON_OFFSET_FACTOR          0x8038
#define GL1_POLYGON_OFFSET_UNITS           0x2A00
#define GL1_POLYGON_OFFSET_POINT           0x2A01
#define GL1_POLYGON_OFFSET_LINE            0x2A02
#define GL1_POLYGON_OFFSET_FILL            0x8037

#define GL1_ALPHA4                         0x803B
#define GL1_ALPHA8                         0x803C
#define GL1_ALPHA12                        0x803D
#define GL1_ALPHA16                        0x803E
#define GL1_LUMINANCE4                     0x803F
#define GL1_LUMINANCE8                     0x8040
#define GL1_LUMINANCE12                    0x8041
#define GL1_LUMINANCE16                    0x8042
#define GL1_LUMINANCE4_ALPHA4              0x8043
#define GL1_LUMINANCE6_ALPHA2              0x8044
#define GL1_LUMINANCE8_ALPHA8              0x8045
#define GL1_LUMINANCE12_ALPHA4             0x8046
#define GL1_LUMINANCE12_ALPHA12            0x8047
#define GL1_LUMINANCE16_ALPHA16            0x8048
#define GL1_INTENSITY                      0x8049
#define GL1_INTENSITY4                     0x804A
#define GL1_INTENSITY8                     0x804B
#define GL1_INTENSITY12                    0x804C
#define GL1_INTENSITY16                    0x804D
#define GL1_R3_G3_B2                       0x2A10
#define GL1_RGB4                           0x804F
#define GL1_RGB5                           0x8050
#define GL1_RGB8                           0x8051
#define GL1_RGB10                          0x8052
#define GL1_RGB12                          0x8053
#define GL1_RGB16                          0x8054
#define GL1_RGBA2                          0x8055
#define GL1_RGBA4                          0x8056
#define GL1_RGB5_A1                        0x8057
#define GL1_RGBA8                          0x8058
#define GL1_RGB10_A2                       0x8059
#define GL1_RGBA12                         0x805A
#define GL1_RGBA16                         0x805B
#define GL1_TEXTURE_RED_SIZE               0x805C
#define GL1_TEXTURE_GREEN_SIZE             0x805D
#define GL1_TEXTURE_BLUE_SIZE              0x805E
#define GL1_TEXTURE_ALPHA_SIZE             0x805F
#define GL1_TEXTURE_LUMINANCE_SIZE         0x8060
#define GL1_TEXTURE_INTENSITY_SIZE         0x8061
#define GL1_PROXY_TEXTURE_1D               0x8063
#define GL1_PROXY_TEXTURE_2D               0x8064

#define GL1_VERTEX_ARRAY                   0x8074
#define GL1_NORMAL_ARRAY                   0x8075
#define GL1_COLOR_ARRAY                    0x8076
#define GL1_INDEX_ARRAY                    0x8077
#define GL1_TEXTURE_COORD_ARRAY            0x8078
#define GL1_EDGE_FLAG_ARRAY                0x8079
#define GL1_VERTEX_ARRAY_SIZE              0x807A
#define GL1_VERTEX_ARRAY_TYPE              0x807B
#define GL1_VERTEX_ARRAY_STRIDE            0x807C
#define GL1_NORMAL_ARRAY_TYPE              0x807E
#define GL1_NORMAL_ARRAY_STRIDE            0x807F
#define GL1_COLOR_ARRAY_SIZE               0x8081
#define GL1_COLOR_ARRAY_TYPE               0x8082
#define GL1_COLOR_ARRAY_STRIDE             0x8083
#define GL1_INDEX_ARRAY_TYPE               0x8085
#define GL1_INDEX_ARRAY_STRIDE             0x8086
#define GL1_TEXTURE_COORD_ARRAY_SIZE       0x8088
#define GL1_TEXTURE_COORD_ARRAY_TYPE       0x8089
#define GL1_TEXTURE_COORD_ARRAY_STRIDE     0x808A
#define GL1_EDGE_FLAG_ARRAY_STRIDE         0x808C
#define GL1_VERTEX_ARRAY_POINTER           0x808E
#define GL1_NORMAL_ARRAY_POINTER           0x808F
#define GL1_COLOR_ARRAY_POINTER            0x8090
#define GL1_INDEX_ARRAY_POINTER            0x8091
#define GL1_TEXTURE_COORD_ARRAY_POINTER    0x8092
#define GL1_EDGE_FLAG_ARRAY_POINTER        0x8093
#define GL1_V2F                            0x2A20
#define GL1_V3F                            0x2A21
#define GL1_C4UB_V2F                       0x2A22
#define GL1_C4UB_V3F                       0x2A23
#define GL1_C3F_V3F                        0x2A24
#define GL1_N3F_V3F                        0x2A25
#define GL1_C4F_N3F_V3F                    0x2A26
#define GL1_T2F_V3F                        0x2A27
#define GL1_T4F_V4F                        0x2A28
#define GL1_T2F_C4UB_V3F                   0x2A29
#define GL1_T2F_C3F_V3F                    0x2A2A
#define GL1_T2F_N3F_V3F                    0x2A2B
#define GL1_T2F_C4F_N3F_V3F                0x2A2C
#define GL1_T4F_C4F_N3F_V4F                0x2A2D

/* ClientAttribMask */
#define GL1_CLIENT_PIXEL_STORE_BIT         0x00000001
#define GL1_CLIENT_VERTEX_ARRAY_BIT        0x00000002
#define GL1_CLIENT_ALL_ATTRIB_BITS         0xffffffff

typedef uint32_t	GL1bitfield;
typedef uint8_t		GL1boolean;
typedef int8_t		GL1byte;
typedef float		GL1clampf;
typedef uint32_t	GL1enum;
typedef float		GL1float;
typedef int32_t		GL1int;
typedef int16_t		GL1short;
typedef int32_t		GL1sizei;
typedef uint8_t		GL1ubyte;
typedef uint32_t	GL1uint;
typedef uint16_t	GL1ushort;
typedef void		GL1void;
typedef double		GL1double;
typedef double		GL1clampd;

void gl1AlphaFunc(GL1enum func, GL1clampf ref);

void gl1ArrayElement(GL1int i);

void gl1Begin(GL1enum mode);
void gl1End(void);

void gl1BindTexture(GL1enum target, GL1uint texture);

void gl1BlendFunc(GL1enum sfactor, GL1enum dfactor);

void gl1CallList(GL1uint list);

void gl1CallLists(GL1sizei n, GL1enum type, const GL1void * lists);

void gl1Clear(GL1bitfield mask);

void gl1ClearColor(GL1clampf red, GL1clampf green, GL1clampf blue, GL1clampf alpha);

void gl1ClearDepth(GL1clampd depth);

void gl1ClearIndex(GL1float c);

void gl1ClearStencil(GL1int s);

void gl1ClipPlane(GL1enum plane, const GL1double * equation);

void gl1Color3b(GL1byte red, GL1byte green, GL1byte blue);
void gl1Color3d(GL1double red, GL1double green, GL1double blue);
void gl1Color3f(GL1float red, GL1float green, GL1float blue);
void gl1Color3i(GL1int red, GL1int green, GL1int blue);
void gl1Color3s(GL1short red, GL1short green, GL1short blue);
void gl1Color3ub(GL1ubyte red, GL1ubyte green, GL1ubyte blue);
void gl1Color3ui(GL1uint red, GL1uint green, GL1uint blue);
void gl1Color3us(GL1ushort red, GL1ushort green, GL1ushort blue);
void gl1Color4b(GL1byte red, GL1byte green, GL1byte blue, GL1byte alpha);
void gl1Color4d(GL1double red, GL1double green, GL1double blue, GL1double alpha);
void gl1Color4f(GL1float red, GL1float green, GL1float blue, GL1float alpha);
void gl1Color4i(GL1int red, GL1int green, GL1int blue, GL1int alpha);
void gl1Color4s(GL1short red, GL1short green, GL1short blue, GL1short alpha);
void gl1Color4ub(GL1ubyte red, GL1ubyte green, GL1ubyte blue, GL1ubyte alpha);
void gl1Color4ui(GL1uint red, GL1uint green, GL1uint blue, GL1uint alpha);
void gl1Color4us(GL1ushort red, GL1ushort green, GL1ushort blue, GL1ushort alpha);
void gl1Color3bv(const GL1byte * v);
void gl1Color3dv(const GL1double * v);
void gl1Color3fv(const GL1float * v);
void gl1Color3iv(const GL1int * v);
void gl1Color3sv(const GL1short * v);
void gl1Color3ubv(const GL1ubyte * v);
void gl1Color3uiv(const GL1uint * v);
void gl1Color3usv(const GL1ushort * v);
void gl1Color4bv(const GL1byte * v);
void gl1Color4dv(const GL1double * v);
void gl1Color4fv(const GL1float * v);
void gl1Color4iv(const GL1int * v);
void gl1Color4sv(const GL1short * v);
void gl1Color4ubv(const GL1ubyte * v);
void gl1Color4uiv(const GL1uint * v);
void gl1Color4usv(const GL1ushort * v);

void gl1ColorMask(GL1boolean red, GL1boolean green, GL1boolean blue, GL1boolean alpha);

void gl1ColorMaterial(GL1enum face, GL1enum mode);

void gl1ColorPointer(GL1int size, GL1enum type, GL1sizei stride, const GL1void * pointer);

void gl1CullFace(GL1enum mode);

void gl1DeleteLists(GL1uint list, GL1sizei range);

void gl1DeleteTextures(GL1sizei n, const GL1uint * textures);

void gl1DepthFunc(GL1enum func);

void gl1DepthMask(GL1boolean flag);

void gl1DepthRange(GL1clampd zNear, GL1clampd zFar);

void gl1DrawArrays(GL1enum mode, GL1int first, GL1sizei count);

void gl1DrawBuffer(GL1enum mode);

void gl1DrawElements(GL1enum mode, GL1sizei count, GL1enum type, const GL1void * indices);

void gl1Enable(GL1enum cap);
void gl1Disable(GL1enum cap);

void gl1EnableClientState(GL1enum cap);
void gl1DisableClientState(GL1enum cap);

void gl1Finish(void);

void gl1Flush(void);

void gl1Fogf(GL1enum pname, GL1float param);
void gl1Fogi(GL1enum pname, GL1int param);
void gl1Fogfv(GL1enum pname, const GL1float * params);
void gl1Fogiv(GL1enum pname, const GL1int * params);

void gl1FrontFace(GL1enum mode);

void gl1Frustum(GL1double left, GL1double right, GL1double bottom, GL1double top, GL1double zNear, GL1double zFar);

GL1uint gl1GenLists(GL1sizei range);

void gl1GenTextures(GL1sizei n, GL1uint * textures);

void gl1GetBooleanv(GL1enum pname, GL1boolean * params);
void gl1GetDoublev(GL1enum pname, GL1double * params);
void gl1GetFloatv(GL1enum pname, GL1float * params);
void gl1GetIntegerv(GL1enum pname, GL1int * params);

void gl1GetClipPlane(GL1enum plane, GL1double * equation);

GL1enum gl1GetError(void);

void gl1GetLightfv(GL1enum light, GL1enum pname, GL1float * params);
void gl1GetLightiv(GL1enum light, GL1enum pname, GL1int * params);

void gl1GetMaterialfv(GL1enum face, GL1enum pname, GL1float * params);
void gl1GetMaterialiv(GL1enum face, GL1enum pname, GL1int * params);

void gl1GetPointerv(GL1enum pname, GL1void* * params);

const GL1ubyte * gl1GetString(GL1enum name);

void gl1GetTexEnvfv(GL1enum target, GL1enum pname, GL1float * params);
void gl1GetTexEnviv(GL1enum target, GL1enum pname, GL1int * params);

void gl1GetTexGendv(GL1enum coord, GL1enum pname, GL1double * params);
void gl1GetTexGenfv(GL1enum coord, GL1enum pname, GL1float * params);
void gl1GetTexGeniv(GL1enum coord, GL1enum pname, GL1int * params);

void gl1GetTexImage(GL1enum target, GL1int level, GL1enum format, GL1enum type, GL1void * pixels);

void gl1GetTexParameterfv(GL1enum target, GL1enum pname, GL1float * params);
void gl1GetTexParameteriv(GL1enum target, GL1enum pname, GL1int * params);

void gl1Indexd(GL1double c);
void gl1Indexf(GL1float c);
void gl1Indexi(GL1int c);
void gl1Indexs(GL1short c);
void gl1Indexub(GL1ubyte c);
void gl1Indexdv(const GL1double * c);
void gl1Indexfv(const GL1float * c);
void gl1Indexiv(const GL1int * c);
void gl1Indexsv(const GL1short * c);
void gl1Indexubv(const GL1ubyte * c);

void gl1IndexMask(GL1uint mask);

void gl1IndexPointer(GL1enum type, GL1sizei stride, const GL1void * pointer);

void gl1InterleavedArrays(GL1enum format, GL1sizei stride, const GL1void * pointer);

GL1boolean gl1IsEnabled(GL1enum cap);

GL1boolean gl1IsList(GL1uint list);

GL1boolean gl1IsTexture(GL1uint texture);

void gl1Lightf(GL1enum light, GL1enum pname, GL1float param);
void gl1Lighti(GL1enum light, GL1enum pname, GL1int param);
void gl1Lightfv(GL1enum light, GL1enum pname, const GL1float * params);
void gl1Lightiv(GL1enum light, GL1enum pname, const GL1int * params);

void gl1LightModelf(GL1enum pname, GL1float param);
void gl1LightModeli(GL1enum pname, GL1int param);
void gl1LightModelfv(GL1enum pname, const GL1float * params);
void gl1LightModeliv(GL1enum pname, const GL1int * params);

void gl1LineWidth(GL1float width);

void gl1ListBase(GL1uint base);

void gl1LoadIdentity(void);

void gl1LoadMatrixd(const GL1double * m);
void gl1LoadMatrixf(const GL1float * m);

void gl1LogicOp(GL1enum opcode);

void gl1Materialf(GL1enum face, GL1enum pname, GL1float param);
void gl1Materiali(GL1enum face, GL1enum pname, GL1int param);
void gl1Materialfv(GL1enum face, GL1enum pname, const GL1float * params);
void gl1Materialiv(GL1enum face, GL1enum pname, const GL1int * params);

void gl1MatrixMode(GL1enum mode);

void gl1MultMatrixd(const GL1double * m);
void gl1MultMatrixf(const GL1float * m);

void gl1NewList(GL1uint list, GL1enum mode);
void gl1EndList(void);

void gl1Normal3b(GL1byte nx, GL1byte ny, GL1byte nz);
void gl1Normal3d(GL1double nx, GL1double ny, GL1double nz);
void gl1Normal3f(GL1float nx, GL1float ny, GL1float nz);
void gl1Normal3i(GL1int nx, GL1int ny, GL1int nz);
void gl1Normal3s(GL1short nx, GL1short ny, GL1short nz);
void gl1Normal3bv(const GL1byte * v);
void gl1Normal3dv(const GL1double * v);
void gl1Normal3fv(const GL1float * v);
void gl1Normal3iv(const GL1int * v);
void gl1Normal3sv(const GL1short * v);

void gl1NormalPointer(GL1enum type, GL1sizei stride, const GL1void * pointer);

void gl1Ortho(GL1double left, GL1double right, GL1double bottom, GL1double top, GL1double zNear, GL1double zFar);

void gl1PointSize(GL1float size);

void gl1PolygonMode(GL1enum face, GL1enum mode);

void gl1PolygonOffset(GL1float factor, GL1float units);

void gl1PushAttrib(GL1bitfield mask);
void gl1PopAttrib(void);

void gl1PushMatrix(void);
void gl1PopMatrix(void);

void gl1ReadBuffer(GL1enum mode);

void gl1ReadPixels(GL1int x, GL1int y, GL1sizei width, GL1sizei height, GL1enum format, GL1enum type, GL1void * pixels);

void gl1Rectd(GL1double x1, GL1double y1, GL1double x2, GL1double y2);
void gl1Rectf(GL1float x1, GL1float y1, GL1float x2, GL1float y2);
void gl1Recti(GL1int x1, GL1int y1, GL1int x2, GL1int y2);
void gl1Rects(GL1short x1, GL1short y1, GL1short x2, GL1short y2);
void gl1Rectdv(const GL1double * v1, const GL1double * v2);
void gl1Rectfv(const GL1float * v1, const GL1float * v2);
void gl1Rectiv(const GL1int * v1, const GL1int * v2);
void gl1Rectsv(const GL1short * v1, const GL1short * v2);

void gl1Rotated(GL1double angle, GL1double x, GL1double y, GL1double z);
void gl1Rotatef(GL1float angle, GL1float x, GL1float y, GL1float z);

void gl1Scaled(GL1double x, GL1double y, GL1double z);
void gl1Scalef(GL1float x, GL1float y, GL1float z);

void gl1Scissor(GL1int x, GL1int y, GL1sizei width, GL1sizei height);

void gl1ShadeModel(GL1enum mode);

void gl1StencilFunc(GL1enum func, GL1int ref, GL1uint mask);

void gl1StencilMask(GL1uint mask);

void gl1StencilOp(GL1enum fail, GL1enum zfail, GL1enum zpass);

void gl1TexCoord1d(GL1double s);
void gl1TexCoord1f(GL1float s);
void gl1TexCoord1i(GL1int s);
void gl1TexCoord1s(GL1short s);
void gl1TexCoord2d(GL1double s, GL1double t);
void gl1TexCoord2f(GL1float s, GL1float t);
void gl1TexCoord2i(GL1int s, GL1int t);
void gl1TexCoord2s(GL1short s, GL1short t);
void gl1TexCoord3d(GL1double s, GL1double t, GL1double r);
void gl1TexCoord3f(GL1float s, GL1float t, GL1float r);
void gl1TexCoord3i(GL1int s, GL1int t, GL1int r);
void gl1TexCoord3s(GL1short s, GL1short t, GL1short r);
void gl1TexCoord4d(GL1double s, GL1double t, GL1double r, GL1double q);
void gl1TexCoord4f(GL1float s, GL1float t, GL1float r, GL1float q);
void gl1TexCoord4i(GL1int s, GL1int t, GL1int r, GL1int q);
void gl1TexCoord4s(GL1short s, GL1short t, GL1short r, GL1short q);
void gl1TexCoord1dv(const GL1double * v);
void gl1TexCoord1fv(const GL1float * v);
void gl1TexCoord1iv(const GL1int * v);
void gl1TexCoord1sv(const GL1short * v);
void gl1TexCoord2dv(const GL1double * v);
void gl1TexCoord2fv(const GL1float * v);
void gl1TexCoord2iv(const GL1int * v);
void gl1TexCoord2sv(const GL1short * v);
void gl1TexCoord3dv(const GL1double * v);
void gl1TexCoord3fv(const GL1float * v);
void gl1TexCoord3iv(const GL1int * v);
void gl1TexCoord3sv(const GL1short * v);
void gl1TexCoord4dv(const GL1double * v);
void gl1TexCoord4fv(const GL1float * v);
void gl1TexCoord4iv(const GL1int * v);
void gl1TexCoord4sv(const GL1short * v);

void gl1TexCoordPointer(GL1int size, GL1enum type, GL1sizei stride, const GL1void * pointer);

void gl1TexEnvf(GL1enum target, GL1enum pname, GL1float param);
void gl1TexEnvi(GL1enum target, GL1enum pname, GL1int param);
void gl1TexEnvfv(GL1enum target, GL1enum pname, const GL1float * params);
void gl1TexEnviv(GL1enum target, GL1enum pname, const GL1int * params);

void gl1TexGend(GL1enum coord, GL1enum pname, GL1double param);
void gl1TexGenf(GL1enum coord, GL1enum pname, GL1float param);
void gl1TexGeni(GL1enum coord, GL1enum pname, GL1int param);
void gl1TexGendv(GL1enum coord, GL1enum pname, const GL1double * params);
void gl1TexGenfv(GL1enum coord, GL1enum pname, const GL1float * params);
void gl1TexGeniv(GL1enum coord, GL1enum pname, const GL1int * params);

void gl1TexImage1D(GL1enum target, GL1int level, GL1int internalformat, GL1sizei width, GL1int border, GL1enum format, GL1enum type, const GL1void * pixels);

void gl1TexImage2D(GL1enum target, GL1int level, GL1int internalformat, GL1sizei width, GL1sizei height, GL1int border, GL1enum format, GL1enum type, const GL1void * pixels);

void gl1TexParameteri(GL1enum target, GL1enum pname, GL1int param);

void gl1TexSubImage1D(GL1enum target, GL1int level, GL1int xoffset, GL1sizei width, GL1enum format, GL1enum type, const GL1void * pixels);

void gl1TexSubImage2D(GL1enum target, GL1int level, GL1int xoffset, GL1int yoffset, GL1sizei width, GL1sizei height, GL1enum format, GL1enum type, const GL1void * pixels);

void gl1Translated(GL1double x, GL1double y, GL1double z);
void gl1Translatef(GL1float x, GL1float y, GL1float z);

void gl1Vertex2s(GL1short x, GL1short y);
void gl1Vertex2i(GL1int x, GL1int y);
void gl1Vertex2f(GL1float x, GL1float y);
void gl1Vertex2d(GL1double x, GL1double y);
void gl1Vertex3s(GL1short x, GL1short y, GL1short z);
void gl1Vertex3i(GL1int x, GL1int y, GL1int z);
void gl1Vertex3f(GL1float x, GL1float y, GL1float z);
void gl1Vertex3d(GL1double x, GL1double y, GL1double z);
void gl1Vertex4s(GL1short x, GL1short y, GL1short z, GL1short w);
void gl1Vertex4i(GL1int x, GL1int y, GL1int z, GL1int w);
void gl1Vertex4f(GL1float x, GL1float y, GL1float z, GL1float w);
void gl1Vertex4d(GL1double x, GL1double y, GL1double z, GL1double w);
void gl1Vertex2sv(const GL1short * v);
void gl1Vertex2iv(const GL1int * v);
void gl1Vertex2fv(const GL1float * v);
void gl1Vertex2dv(const GL1double * v);
void gl1Vertex3sv(const GL1short * v);
void gl1Vertex3iv(const GL1int * v);
void gl1Vertex3fv(const GL1float * v);
void gl1Vertex3dv(const GL1double * v);
void gl1Vertex4sv(const GL1short * v);
void gl1Vertex4iv(const GL1int * v);
void gl1Vertex4fv(const GL1float * v);
void gl1Vertex4dv(const GL1double * v);

void gl1VertexPointer(GL1int size, GL1enum type, GL1sizei stride, const GL1void * pointer);

void gl1Viewport(GL1int x, GL1int y, GL1sizei width, GL1sizei height);

void gl1uPerspective(GL1double fovy, GL1double aspect, GL1double zNear, GL1double zFar);
