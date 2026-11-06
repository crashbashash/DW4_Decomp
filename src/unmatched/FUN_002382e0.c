/* Saves the Alchemy viewer (INSIGHT) options into the property tree: the INSIGHT group is looked
 * up in the property set held by the global (+56), falling back to 'Viewer', and each option is
 * written under its string name. Every write is guarded by its name pointer (the original option
 * table can drop a name); the guards are kept because the compiler does not fold them. Callee
 * names come from their roles: StoreString (thunk_FUN_00306910), StoreByte (thunk_FUN_00306e50),
 * StoreFloat (thunk_FUN_003066b0), StoreInt (thunk_FUN_003065f0), StoreVec4 (FUN_001e71f0),
 * StoreVec3 (FUN_001e70a0). */
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec4 { float x, y, z, w; } Vec4;
typedef struct ViewerOptions {
  char * extraCommandLine;
  unsigned char showBBox;
  unsigned char showNormals;
  char pad6[2];
  Vec4 normalsColor;
  Vec4 invalidStoredNormalsColor;
  Vec4 scaledNormalsColor;
  float invalidNormalsPrecision;
  unsigned char autoSelectCamera;
  char pad61[3];
  float horizontalFieldOfView;
  unsigned char autoPlanes;
  char pad69[3];
  float defaultNearPlane;
  float defaultFarPlane;
  Vec3 upVector;
  unsigned char autoSceneLights;
  unsigned char autoHeadLight;
  unsigned char useSceneLights;
  unsigned char useHeadLight;
  unsigned char useHeadLightSpecular;
  char pad97[3];
  Vec4 headLightDiffuse;
  Vec4 headLightSpecular;
  Vec4 headLightAmbient;
  Vec4 clearColor;
  unsigned char wireframeMode;
  unsigned char forceWireframe;
  unsigned char backFaceCullingMode;
  unsigned char forceBackFaceCulling;
  unsigned char alphaTest;
  unsigned char forceAlphaTest;
  char pad170[2];
  float alphaTestReference;
  float maxFrameRate;
  unsigned char optimizeTextures;
  unsigned char halfBuffer;
  unsigned char palVideoMode;
  char pad183[1];
  int width;
  int height;
  int swapInterval;
  int colorBits;
  int alphaBits;
  int depthBits;
  int stencilBits;
  unsigned char reportVideoFormat;
  unsigned char showLogo;
  unsigned char showUI;
  unsigned char enableMayaControls;
  unsigned char benchmark;
  char pad217[3];
  int benchmarkSkipFrames;
  int benchmarkFrames;
  unsigned char columnStatistics;
  unsigned char allocateVisualContextInScratchPad;
} ViewerOptions;

typedef struct PropertySet { char pad[56]; int props; } PropertySet;
extern PropertySet *DAT_00586dc8[4];   /* global holder: +56 is the property set */
extern char DAT_004e9870[];            /* "INSIGHT" */
extern char DAT_004e9878[];            /* "Viewer" */
extern char DAT_004e9880[];   /* "extraCommandLine" */
extern char DAT_004e9898[];   /* "showBBox" */
extern char DAT_004e98a8[];   /* "showNormals" */
extern char DAT_004e98b8[];   /* "normalsColor" */
extern char DAT_004e98d0[];   /* "invalidStoredNormalsColor" */
extern char DAT_004e98f0[];   /* "scaledNormalsColor" */
extern char DAT_004e9910[];   /* "invalidNormalsPrecision" */
extern char DAT_004e9930[];   /* "autoSelectCamera" */
extern char DAT_004e9950[];   /* "horizontalFieldOfView" */
extern char DAT_004e9968[];   /* "autoPlanes" */
extern char DAT_004e9980[];   /* "defaultNearPlane" */
extern char DAT_004e99a0[];   /* "defaultFarPlane" */
extern char DAT_004e99b0[];   /* "upVector" */
extern char DAT_004e99c0[];   /* "autoSceneLights" */
extern char DAT_004e99d0[];   /* "autoHeadLight" */
extern char DAT_004e99e0[];   /* "useSceneLights" */
extern char DAT_004e99f0[];   /* "useHeadLight" */
extern char DAT_004e9a00[];   /* "useHeadLightSpecular" */
extern char DAT_004e9a20[];   /* "headLightDiffuse" */
extern char DAT_004e9a40[];   /* "headLightSpecular" */
extern char DAT_004e9a60[];   /* "headLightAmbient" */
extern char DAT_004e9a78[];   /* "clearColor" */
extern char DAT_004e9a88[];   /* "wireframeMode" */
extern char DAT_004e9a98[];   /* "forceWireframe" */
extern char DAT_004e9ab0[];   /* "backFaceCullingMode" */
extern char DAT_004e9ad0[];   /* "forceBackFaceCulling" */
extern char DAT_004e9ae8[];   /* "alphaTest" */
extern char DAT_004e9af8[];   /* "forceAlphaTest" */
extern char DAT_004e9b10[];   /* "alphaTestReference" */
extern char DAT_004e9b28[];   /* "maxFrameRate" */
extern char DAT_004e9b40[];   /* "optimizeTextures" */
extern char DAT_004e9b58[];   /* "halfBuffer" */
extern char DAT_004e9b68[];   /* "palVideoMode" */
extern char DAT_004e9b78[];   /* "width" */
extern char DAT_004e9b80[];   /* "height" */
extern char DAT_004e9b88[];   /* "swapInterval" */
extern char DAT_004e9b98[];   /* "colorBits" */
extern char DAT_004e9ba8[];   /* "alphaBits" */
extern char DAT_004e9bb8[];   /* "depthBits" */
extern char DAT_004e9bc8[];   /* "stencilBits" */
extern char DAT_004e9be0[];   /* "reportVideoFormat" */
extern char DAT_004e9bf8[];   /* "showLogo" */
extern char DAT_004e9c08[];   /* "showUI" */
extern char DAT_004e9c10[];   /* "enableMayaControls" */
extern char DAT_004e9c28[];   /* "benchmark" */
extern char DAT_004e9c40[];   /* "benchmarkSkipFrames" */
extern char DAT_004e9c60[];   /* "benchmarkFrames" */
extern char DAT_004e9c70[];   /* "columnStatistics" */
extern char DAT_004e9c90[];   /* "allocateVisualContextInScratchPad" */
int FUN_00306360(int, char *, int);
int thunk_FUN_00306910(int, int, char *, char **, char *, int);
int thunk_FUN_00306e50(int, int, char *, unsigned char *, int, int);
int thunk_FUN_003066b0(int, int, char *, float *, int, float);
int thunk_FUN_003065f0(int, int, char *, int *, int, int);
int FUN_001e71f0(int, int, char *, Vec4 *, Vec4 *, int);
int FUN_001e70a0(int, int, char *, Vec3 *, Vec3 *, int);

/* Matching construct: `group` is declared apart from `props` so the property set lands in the first saved register. */
void FUN_002382e0(ViewerOptions *opt) {
  int group;
  int props = DAT_00586dc8[0]->props;
  group = FUN_00306360(props, DAT_004e9870, 0);
  if (group < 0) {
    group = FUN_00306360(props, DAT_004e9878, 0);
    if (group < 0) return;
  }
  if (DAT_004e9880) thunk_FUN_00306910(props, group, DAT_004e9880, &opt->extraCommandLine, opt->extraCommandLine, 0);
  if (DAT_004e9898) thunk_FUN_00306e50(props, group, DAT_004e9898, &opt->showBBox, opt->showBBox, 0);
  if (DAT_004e98a8) thunk_FUN_00306e50(props, group, DAT_004e98a8, &opt->showNormals, opt->showNormals, 0);
  if (DAT_004e98b8) FUN_001e71f0(props, group, DAT_004e98b8, &opt->normalsColor, &opt->normalsColor, 0);
  if (DAT_004e98d0) FUN_001e71f0(props, group, DAT_004e98d0, &opt->invalidStoredNormalsColor, &opt->invalidStoredNormalsColor, 0);
  if (DAT_004e98f0) FUN_001e71f0(props, group, DAT_004e98f0, &opt->scaledNormalsColor, &opt->scaledNormalsColor, 0);
  if (DAT_004e9910) thunk_FUN_003066b0(props, group, DAT_004e9910, &opt->invalidNormalsPrecision, 0, opt->invalidNormalsPrecision);
  if (DAT_004e9930) thunk_FUN_00306e50(props, group, DAT_004e9930, &opt->autoSelectCamera, opt->autoSelectCamera, 0);
  if (DAT_004e9950) thunk_FUN_003066b0(props, group, DAT_004e9950, &opt->horizontalFieldOfView, 0, opt->horizontalFieldOfView);
  if (DAT_004e9968) thunk_FUN_00306e50(props, group, DAT_004e9968, &opt->autoPlanes, opt->autoPlanes, 0);
  if (DAT_004e9980) thunk_FUN_003066b0(props, group, DAT_004e9980, &opt->defaultNearPlane, 0, opt->defaultNearPlane);
  if (DAT_004e99a0) thunk_FUN_003066b0(props, group, DAT_004e99a0, &opt->defaultFarPlane, 0, opt->defaultFarPlane);
  if (DAT_004e99b0) FUN_001e70a0(props, group, DAT_004e99b0, &opt->upVector, &opt->upVector, 0);
  if (DAT_004e99c0) thunk_FUN_00306e50(props, group, DAT_004e99c0, &opt->autoSceneLights, opt->autoSceneLights, 0);
  if (DAT_004e99d0) thunk_FUN_00306e50(props, group, DAT_004e99d0, &opt->autoHeadLight, opt->autoHeadLight, 0);
  if (DAT_004e99e0) thunk_FUN_00306e50(props, group, DAT_004e99e0, &opt->useSceneLights, opt->useSceneLights, 0);
  if (DAT_004e99f0) thunk_FUN_00306e50(props, group, DAT_004e99f0, &opt->useHeadLight, opt->useHeadLight, 0);
  if (DAT_004e9a00) thunk_FUN_00306e50(props, group, DAT_004e9a00, &opt->useHeadLightSpecular, opt->useHeadLightSpecular, 0);
  if (DAT_004e9a20) FUN_001e71f0(props, group, DAT_004e9a20, &opt->headLightDiffuse, &opt->headLightDiffuse, 0);
  if (DAT_004e9a40) FUN_001e71f0(props, group, DAT_004e9a40, &opt->headLightSpecular, &opt->headLightSpecular, 0);
  if (DAT_004e9a60) FUN_001e71f0(props, group, DAT_004e9a60, &opt->headLightAmbient, &opt->headLightAmbient, 0);
  if (DAT_004e9a78) FUN_001e71f0(props, group, DAT_004e9a78, &opt->clearColor, &opt->clearColor, 0);
  if (DAT_004e9a88) thunk_FUN_00306e50(props, group, DAT_004e9a88, &opt->wireframeMode, opt->wireframeMode, 0);
  if (DAT_004e9a98) thunk_FUN_00306e50(props, group, DAT_004e9a98, &opt->forceWireframe, opt->forceWireframe, 0);
  if (DAT_004e9ab0) thunk_FUN_00306e50(props, group, DAT_004e9ab0, &opt->backFaceCullingMode, opt->backFaceCullingMode, 0);
  if (DAT_004e9ad0) thunk_FUN_00306e50(props, group, DAT_004e9ad0, &opt->forceBackFaceCulling, opt->forceBackFaceCulling, 0);
  if (DAT_004e9ae8) thunk_FUN_00306e50(props, group, DAT_004e9ae8, &opt->alphaTest, opt->alphaTest, 0);
  if (DAT_004e9af8) thunk_FUN_00306e50(props, group, DAT_004e9af8, &opt->forceAlphaTest, opt->forceAlphaTest, 0);
  if (DAT_004e9b10) thunk_FUN_003066b0(props, group, DAT_004e9b10, &opt->alphaTestReference, 0, opt->alphaTestReference);
  if (DAT_004e9b28) thunk_FUN_003066b0(props, group, DAT_004e9b28, &opt->maxFrameRate, 0, opt->maxFrameRate);
  if (DAT_004e9b40) thunk_FUN_00306e50(props, group, DAT_004e9b40, &opt->optimizeTextures, opt->optimizeTextures, 0);
  if (DAT_004e9b58) thunk_FUN_00306e50(props, group, DAT_004e9b58, &opt->halfBuffer, opt->halfBuffer, 0);
  if (DAT_004e9b68) thunk_FUN_00306e50(props, group, DAT_004e9b68, &opt->palVideoMode, opt->palVideoMode, 0);
  if (DAT_004e9b78) thunk_FUN_003065f0(props, group, DAT_004e9b78, &opt->width, opt->width, 0);
  if (DAT_004e9b80) thunk_FUN_003065f0(props, group, DAT_004e9b80, &opt->height, opt->height, 0);
  if (DAT_004e9b88) thunk_FUN_003065f0(props, group, DAT_004e9b88, &opt->swapInterval, opt->swapInterval, 0);
  if (DAT_004e9b98) thunk_FUN_003065f0(props, group, DAT_004e9b98, &opt->colorBits, opt->colorBits, 0);
  if (DAT_004e9ba8) thunk_FUN_003065f0(props, group, DAT_004e9ba8, &opt->alphaBits, opt->alphaBits, 0);
  if (DAT_004e9bb8) thunk_FUN_003065f0(props, group, DAT_004e9bb8, &opt->depthBits, opt->depthBits, 0);
  if (DAT_004e9bc8) thunk_FUN_003065f0(props, group, DAT_004e9bc8, &opt->stencilBits, opt->stencilBits, 0);
  if (DAT_004e9be0) thunk_FUN_00306e50(props, group, DAT_004e9be0, &opt->reportVideoFormat, opt->reportVideoFormat, 0);
  if (DAT_004e9bf8) thunk_FUN_00306e50(props, group, DAT_004e9bf8, &opt->showLogo, opt->showLogo, 0);
  if (DAT_004e9c08) thunk_FUN_00306e50(props, group, DAT_004e9c08, &opt->showUI, opt->showUI, 0);
  if (DAT_004e9c10) thunk_FUN_00306e50(props, group, DAT_004e9c10, &opt->enableMayaControls, opt->enableMayaControls, 0);
  if (DAT_004e9c28) thunk_FUN_00306e50(props, group, DAT_004e9c28, &opt->benchmark, opt->benchmark, 0);
  if (DAT_004e9c40) thunk_FUN_003065f0(props, group, DAT_004e9c40, &opt->benchmarkSkipFrames, opt->benchmarkSkipFrames, 0);
  if (DAT_004e9c60) thunk_FUN_003065f0(props, group, DAT_004e9c60, &opt->benchmarkFrames, opt->benchmarkFrames, 0);
  if (DAT_004e9c70) thunk_FUN_00306e50(props, group, DAT_004e9c70, &opt->columnStatistics, opt->columnStatistics, 0);
  if (DAT_004e9c90) thunk_FUN_00306e50(props, group, DAT_004e9c90, &opt->allocateVisualContextInScratchPad, opt->allocateVisualContextInScratchPad, 0);
}
