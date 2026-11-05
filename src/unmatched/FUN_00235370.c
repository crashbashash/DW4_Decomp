/* 0x00235370 - FUN_00235370: command-line parser of an Alchemy model-viewer
 * style application (hypothesis: the option names are the strings at
 * 0x4e88b8..0x4e9560 in data/strings.json, and the callers 0x233c10 /
 * 0x234470..0x2348b0 are the matching option-name helpers).
 *
 * Each recognised "--option value" is parsed into `opts` and echoed into the
 * block `opts->applied` points at.  "--help" prints the usage text and exits,
 * "--" or "-n" ends the option scan, any other "-x" token is reported as
 * unrecognised.  The second loop collects the remaining tokens as model files,
 * each with its "-n N" repeat count.
 *
 * Compiler: needs the pinned "combat" mwccps2 (config/SLUS-20836/unit-compilers.tsv) at
 * -O3; with the default compiler the callee-saved registers are assigned in a
 * different order.  The re-read of the list count in the in-capacity increment
 * is spelled with a volatile read, as in beMessengerArgs.c (retail loads the
 * count a second time instead of reusing the index).  `modelFile` lives in
 * memory in retail (its stack slot is the highest), hence volatile. */

#include "dw4/reflected.h"
#include "dw4/igobject_release.h"

typedef struct StringList {
    int _unk00[2];
    int count;      /* +0x08 number of tokens */
} StringList;

typedef struct StringHeader {
    int owner;
    int refCount;
} StringHeader;

typedef struct IntList {
    int _unk00[2];
    int count;
    int capacity;
    int *data;
} IntList;

typedef struct ViewerOptions ViewerOptions;
struct ViewerOptions {
    char *modelName;                    /* +0x00 positional model argument (interned string) */
    unsigned char showBbox;  /* +0x04 --show-bbox */
    unsigned char showNormals;  /* +0x05 --show-normals */
    unsigned char _pad06[2];
    float normalsColor[4];  /* +0x08 --normals-color */
    float invalidStoredNormalsColor[4];  /* +0x18 --invalid-stored-normals-color */
    float scaledNormalsColor[4];  /* +0x28 --scaled-normals-color */
    float invalidNormalsPrecision;  /* +0x38 --invalid-normals-precision */
    unsigned char autoSelectCamera;  /* +0x3C --auto-select-camera */
    unsigned char _pad3D[3];
    float hfov;  /* +0x40 --hfov */
    unsigned char autoPlanes;  /* +0x44 --auto-planes */
    unsigned char _pad45[3];
    float nearPlane;  /* +0x48 --near-plane */
    float farPlane;  /* +0x4C --far-plane */
    float upVector[3];  /* +0x50 --up-vector */
    unsigned char autoSceneLights;  /* +0x5C --auto-scene-lights */
    unsigned char autoHeadLight;  /* +0x5D --auto-head-light */
    unsigned char useSceneLights;  /* +0x5E --use-scene-lights */
    unsigned char useHeadLight;  /* +0x5F --use-head-light */
    unsigned char useHeadLightSpecular;  /* +0x60 --use-head-light-specular */
    unsigned char _pad61[3];
    float headLightDiffuse[4];  /* +0x64 --head-light-diffuse */
    float headLightSpecular[4];  /* +0x74 --head-light-specular */
    float headLightAmbient[4];  /* +0x84 --head-light-ambient */
    float clearColor[4];  /* +0x94 --clear-color */
    unsigned char wireframeMode;  /* +0xA4 --wireframe-mode */
    unsigned char forceWireframe;  /* +0xA5 --force-wireframe */
    unsigned char backfaceCullingMode;  /* +0xA6 --backface-culling-mode */
    unsigned char forceBackfaceCulling;  /* +0xA7 --force-backface-culling */
    unsigned char alphaTest;  /* +0xA8 --alpha-test */
    unsigned char forceAlphaTest;  /* +0xA9 --force-alpha-test */
    unsigned char _padAA[2];
    float alphaTestReference;  /* +0xAC --alpha-test-reference */
    float maximumFrameRate;  /* +0xB0 --maximum-frame-rate */
    unsigned char optimizeTextures;  /* +0xB4 --optimize-textures */
    unsigned char halfBuffer;  /* +0xB5 --half-buffer */
    unsigned char palVideoMode;  /* +0xB6 --pal-video-mode */
    unsigned char _padB7[1];
    int width;  /* +0xB8 --width */
    int height;  /* +0xBC --height */
    int swapInterval;  /* +0xC0 --swap-interval */
    int colorBits;  /* +0xC4 --color-bits */
    int alphaBits;  /* +0xC8 --alpha-bits */
    int depthBits;  /* +0xCC --depth-bits */
    int stencilBits;  /* +0xD0 --stencil-bits */
    unsigned char reportVideoFormat;  /* +0xD4 --report-video-format */
    unsigned char showLogo;  /* +0xD5 --show-logo */
    unsigned char showUi;  /* +0xD6 --show-ui */
    unsigned char enableMayaControls;  /* +0xD7 --enable-maya-controls */
    unsigned char benchmark;  /* +0xD8 --benchmark */
    unsigned char _padD9[3];
    int benchmarkSkipFrames;  /* +0xDC --benchmark-skip-frames */
    int benchmarkFrames;  /* +0xE0 --benchmark-frames */
    unsigned char columnStatistics;  /* +0xE4 --column-statistics */
    unsigned char allocateVisualContextInScratchpad;  /* +0xE5 --allocate-visual-context-in-scratchpad */
    unsigned char _padE6[2];
    struct igObject *intList;  /* +0xE8 */
    struct igObject *stringList;  /* +0xEC */
    ViewerOptions *applied;   /* +0xF0 */
};


int FUN_00233c10(char *programName);
int FUN_00234470(StringList *args, int *index, const char *name);
int FUN_002346c0(StringList *args, int *index, const char *name, ViewerOptions *opts);
int FUN_00234510(StringList *args, int *index, const char *name, int *value);
int thunk_FUN_00234510(StringList *args, int *index, const char *name, int *value);
int FUN_00234770(StringList *args, int *index, const char *name, unsigned char *value);
int FUN_00234810(StringList *args, int *index, const char *name, float *value);
int FUN_00234860(StringList *args, int *index, const char *name, float *value);
int FUN_002348b0(StringList *args, int *index, const char *name, float *value);
int StringList_CopyRetained(char **out, StringList *list, int index);
int StringList_AppendRetained(StringList *list, char **item);
int StringChunk_ReleaseHeader(int owner, StringHeader *header);
int List_Resize(IntList *list, int newCount, int elementSize);
int igObject_Destroy(igObject *object);
int printf(const char *format, ...);
int FUN_00124d60(int status);

extern const char s_help_004e9700[16];
extern const char s_n_004e9708[8];
extern const char s_dashdash_004e9710[8];
extern const char s_unrecognized_004e9720[32];
extern const char s_showBbox_004e88b8[16];
extern const char s_showNormals_004e88f8[16];
extern const char s_normalsColor_004e8930[16];
extern const char s_invalidStoredNormalsColor_004e8960[16];
extern const char s_scaledNormalsColor_004e89b0[16];
extern const char s_invalidNormalsPrecision_004e89f0[16];
extern const char s_autoSelectCamera_004e8a40[16];
extern const char s_hfov_004e8a90[16];
extern const char s_autoPlanes_004e8ac8[16];
extern const char s_nearPlane_004e8b10[16];
extern const char s_farPlane_004e8b48[16];
extern const char s_upVector_004e8b88[16];
extern const char s_autoSceneLights_004e8be0[16];
extern const char s_autoHeadLight_004e8c30[16];
extern const char s_useSceneLights_004e8c80[16];
extern const char s_useHeadLight_004e8cd0[16];
extern const char s_useHeadLightSpecular_004e8d20[16];
extern const char s_headLightDiffuse_004e8d60[16];
extern const char s_headLightSpecular_004e8db0[16];
extern const char s_headLightAmbient_004e8e00[16];
extern const char s_clearColor_004e8e50[16];
extern const char s_wireframeMode_004e8e80[16];
extern const char s_forceWireframe_004e8ec0[16];
extern const char s_backfaceCullingMode_004e8f10[16];
extern const char s_forceBackfaceCulling_004e8f50[16];
extern const char s_alphaTest_004e8fa0[16];
extern const char s_forceAlphaTest_004e8fd0[16];
extern const char s_alphaTestReference_004e9020[16];
extern const char s_maximumFrameRate_004e9060[16];
extern const char s_optimizeTextures_004e90c0[16];
extern const char s_halfBuffer_004e9100[16];
extern const char s_palVideoMode_004e9130[16];
extern const char s_width_004e9168[16];
extern const char s_height_004e9188[16];
extern const char s_swapInterval_004e91c0[16];
extern const char s_colorBits_004e9200[16];
extern const char s_alphaBits_004e9240[16];
extern const char s_depthBits_004e9280[16];
extern const char s_stencilBits_004e92c0[16];
extern const char s_reportVideoFormat_004e9300[16];
extern const char s_showLogo_004e9358[16];
extern const char s_showUi_004e9388[16];
extern const char s_enableMayaControls_004e93c0[16];
extern const char s_benchmark_004e9408[16];
extern const char s_benchmarkSkipFrames_004e9450[16];
extern const char s_benchmarkFrames_004e94b0[16];
extern const char s_columnStatistics_004e9500[16];
extern const char s_allocateVisualContextInScratchpad_004e9560[16];

#include "dw4/fun_00235370_refs.h"

/* The object smart-pointer destructor: the held pointer is copied once (its slot is a plain
 * field, so retail reads it once), then released with the shared sequence. */
#define ReleaseObject(obj) do { igObject *held = (obj); IG_OBJECT_RELEASE(held); } while (0)

void FUN_00235370(ViewerOptions *opts, StringList *args)
{
    char * volatile modelFile;
    int repeat;
    int index;
    /* Each smart-pointer temporary of the original has its own stack slot. */
    char *helpRef;
    char *optionRef;
    char *printRef;
    char *helpRef2;
    char *currentRef;
    char *argumentRef;
    int argc;
    ViewerOptions *applied;
    int slot;
    IntList *repeats;

    modelFile = 0;
    repeat = 1;
    argc = args->count;
    index = 1;

    while (index < argc) {
        if (FUN_00234470(args, &index, s_help_004e9700)) {
            StringList_CopyRetained(&helpRef, args, 0);
            FUN_00233c10(helpRef);
            ReleaseString(helpRef);
            ReleaseObject(opts->intList);
            opts->intList = 0;
            ReleaseObject(opts->stringList);
            opts->stringList = 0;
            FUN_00124d60(0);
        } else if (FUN_002346c0(args, &index, 0, opts)) {
            char *name;
            name = opts->modelName;
            applied = opts->applied;
            if (name != 0) {
                ((int *)name)[-1]++;
            }
            ReleaseString(applied->modelName);
            applied->modelName = opts->modelName;
        } else if (FUN_00234770(args, &index, s_showBbox_004e88b8, &opts->showBbox)) {
            opts->applied->showBbox = opts->showBbox;
        } else if (FUN_00234770(args, &index, s_showNormals_004e88f8, &opts->showNormals)) {
            opts->applied->showNormals = opts->showNormals;
        } else if (FUN_002348b0(args, &index, s_normalsColor_004e8930, &opts->normalsColor[0])) {
            applied = opts->applied;
            applied->normalsColor[0] = opts->normalsColor[0];
            applied->normalsColor[1] = opts->normalsColor[1];
            applied->normalsColor[2] = opts->normalsColor[2];
            applied->normalsColor[3] = opts->normalsColor[3];
        } else if (FUN_002348b0(args, &index, s_invalidStoredNormalsColor_004e8960, &opts->invalidStoredNormalsColor[0])) {
            applied = opts->applied;
            applied->invalidStoredNormalsColor[0] = opts->invalidStoredNormalsColor[0];
            applied->invalidStoredNormalsColor[1] = opts->invalidStoredNormalsColor[1];
            applied->invalidStoredNormalsColor[2] = opts->invalidStoredNormalsColor[2];
            applied->invalidStoredNormalsColor[3] = opts->invalidStoredNormalsColor[3];
        } else if (FUN_002348b0(args, &index, s_scaledNormalsColor_004e89b0, &opts->scaledNormalsColor[0])) {
            applied = opts->applied;
            applied->scaledNormalsColor[0] = opts->scaledNormalsColor[0];
            applied->scaledNormalsColor[1] = opts->scaledNormalsColor[1];
            applied->scaledNormalsColor[2] = opts->scaledNormalsColor[2];
            applied->scaledNormalsColor[3] = opts->scaledNormalsColor[3];
        } else if (FUN_00234810(args, &index, s_invalidNormalsPrecision_004e89f0, &opts->invalidNormalsPrecision)) {
            opts->applied->invalidNormalsPrecision = opts->invalidNormalsPrecision;
        } else if (FUN_00234770(args, &index, s_autoSelectCamera_004e8a40, &opts->autoSelectCamera)) {
            opts->applied->autoSelectCamera = opts->autoSelectCamera;
        } else if (FUN_00234810(args, &index, s_hfov_004e8a90, &opts->hfov)) {
            opts->applied->hfov = opts->hfov;
        } else if (FUN_00234770(args, &index, s_autoPlanes_004e8ac8, &opts->autoPlanes)) {
            opts->applied->autoPlanes = opts->autoPlanes;
        } else if (FUN_00234810(args, &index, s_nearPlane_004e8b10, &opts->nearPlane)) {
            opts->applied->nearPlane = opts->nearPlane;
        } else if (FUN_00234810(args, &index, s_farPlane_004e8b48, &opts->farPlane)) {
            opts->applied->farPlane = opts->farPlane;
        } else if (FUN_00234860(args, &index, s_upVector_004e8b88, &opts->upVector[0])) {
            applied = opts->applied;
            applied->upVector[0] = opts->upVector[0];
            applied->upVector[1] = opts->upVector[1];
            applied->upVector[2] = opts->upVector[2];
        } else if (FUN_00234770(args, &index, s_autoSceneLights_004e8be0, &opts->autoSceneLights)) {
            opts->applied->autoSceneLights = opts->autoSceneLights;
        } else if (FUN_00234770(args, &index, s_autoHeadLight_004e8c30, &opts->autoHeadLight)) {
            opts->applied->autoHeadLight = opts->autoHeadLight;
        } else if (FUN_00234770(args, &index, s_useSceneLights_004e8c80, &opts->useSceneLights)) {
            opts->applied->useSceneLights = opts->useSceneLights;
        } else if (FUN_00234770(args, &index, s_useHeadLight_004e8cd0, &opts->useHeadLight)) {
            opts->applied->useHeadLight = opts->useHeadLight;
        } else if (FUN_00234770(args, &index, s_useHeadLightSpecular_004e8d20, &opts->useHeadLightSpecular)) {
            opts->applied->useHeadLightSpecular = opts->useHeadLightSpecular;
        } else if (FUN_002348b0(args, &index, s_headLightDiffuse_004e8d60, &opts->headLightDiffuse[0])) {
            applied = opts->applied;
            applied->headLightDiffuse[0] = opts->headLightDiffuse[0];
            applied->headLightDiffuse[1] = opts->headLightDiffuse[1];
            applied->headLightDiffuse[2] = opts->headLightDiffuse[2];
            applied->headLightDiffuse[3] = opts->headLightDiffuse[3];
        } else if (FUN_002348b0(args, &index, s_headLightSpecular_004e8db0, &opts->headLightSpecular[0])) {
            applied = opts->applied;
            applied->headLightSpecular[0] = opts->headLightSpecular[0];
            applied->headLightSpecular[1] = opts->headLightSpecular[1];
            applied->headLightSpecular[2] = opts->headLightSpecular[2];
            applied->headLightSpecular[3] = opts->headLightSpecular[3];
        } else if (FUN_002348b0(args, &index, s_headLightAmbient_004e8e00, &opts->headLightAmbient[0])) {
            applied = opts->applied;
            applied->headLightAmbient[0] = opts->headLightAmbient[0];
            applied->headLightAmbient[1] = opts->headLightAmbient[1];
            applied->headLightAmbient[2] = opts->headLightAmbient[2];
            applied->headLightAmbient[3] = opts->headLightAmbient[3];
        } else if (FUN_002348b0(args, &index, s_clearColor_004e8e50, &opts->clearColor[0])) {
            applied = opts->applied;
            applied->clearColor[0] = opts->clearColor[0];
            applied->clearColor[1] = opts->clearColor[1];
            applied->clearColor[2] = opts->clearColor[2];
            applied->clearColor[3] = opts->clearColor[3];
        } else if (FUN_00234770(args, &index, s_wireframeMode_004e8e80, &opts->wireframeMode)) {
            opts->applied->wireframeMode = opts->wireframeMode;
        } else if (FUN_00234770(args, &index, s_forceWireframe_004e8ec0, &opts->forceWireframe)) {
            opts->applied->forceWireframe = opts->forceWireframe;
        } else if (FUN_00234770(args, &index, s_backfaceCullingMode_004e8f10, &opts->backfaceCullingMode)) {
            opts->applied->backfaceCullingMode = opts->backfaceCullingMode;
        } else if (FUN_00234770(args, &index, s_forceBackfaceCulling_004e8f50, &opts->forceBackfaceCulling)) {
            opts->applied->forceBackfaceCulling = opts->forceBackfaceCulling;
        } else if (FUN_00234770(args, &index, s_alphaTest_004e8fa0, &opts->alphaTest)) {
            opts->applied->alphaTest = opts->alphaTest;
        } else if (FUN_00234770(args, &index, s_forceAlphaTest_004e8fd0, &opts->forceAlphaTest)) {
            opts->applied->forceAlphaTest = opts->forceAlphaTest;
        } else if (FUN_00234810(args, &index, s_alphaTestReference_004e9020, &opts->alphaTestReference)) {
            opts->applied->alphaTestReference = opts->alphaTestReference;
        } else if (FUN_00234810(args, &index, s_maximumFrameRate_004e9060, &opts->maximumFrameRate)) {
            opts->applied->maximumFrameRate = opts->maximumFrameRate;
        } else if (FUN_00234770(args, &index, s_optimizeTextures_004e90c0, &opts->optimizeTextures)) {
            opts->applied->optimizeTextures = opts->optimizeTextures;
        } else if (FUN_00234770(args, &index, s_halfBuffer_004e9100, &opts->halfBuffer)) {
            opts->applied->halfBuffer = opts->halfBuffer;
        } else if (FUN_00234770(args, &index, s_palVideoMode_004e9130, &opts->palVideoMode)) {
            opts->applied->palVideoMode = opts->palVideoMode;
        } else if (thunk_FUN_00234510(args, &index, s_width_004e9168, &opts->width)) {
            opts->applied->width = opts->width;
        } else if (thunk_FUN_00234510(args, &index, s_height_004e9188, &opts->height)) {
            opts->applied->height = opts->height;
        } else if (thunk_FUN_00234510(args, &index, s_swapInterval_004e91c0, &opts->swapInterval)) {
            opts->applied->swapInterval = opts->swapInterval;
        } else if (thunk_FUN_00234510(args, &index, s_colorBits_004e9200, &opts->colorBits)) {
            opts->applied->colorBits = opts->colorBits;
        } else if (thunk_FUN_00234510(args, &index, s_alphaBits_004e9240, &opts->alphaBits)) {
            opts->applied->alphaBits = opts->alphaBits;
        } else if (thunk_FUN_00234510(args, &index, s_depthBits_004e9280, &opts->depthBits)) {
            opts->applied->depthBits = opts->depthBits;
        } else if (thunk_FUN_00234510(args, &index, s_stencilBits_004e92c0, &opts->stencilBits)) {
            opts->applied->stencilBits = opts->stencilBits;
        } else if (FUN_00234770(args, &index, s_reportVideoFormat_004e9300, &opts->reportVideoFormat)) {
            opts->applied->reportVideoFormat = opts->reportVideoFormat;
        } else if (FUN_00234770(args, &index, s_showLogo_004e9358, &opts->showLogo)) {
            opts->applied->showLogo = opts->showLogo;
        } else if (FUN_00234770(args, &index, s_showUi_004e9388, &opts->showUi)) {
            opts->applied->showUi = opts->showUi;
        } else if (FUN_00234770(args, &index, s_enableMayaControls_004e93c0, &opts->enableMayaControls)) {
            opts->applied->enableMayaControls = opts->enableMayaControls;
        } else if (FUN_00234770(args, &index, s_benchmark_004e9408, &opts->benchmark)) {
            opts->applied->benchmark = opts->benchmark;
        } else if (thunk_FUN_00234510(args, &index, s_benchmarkSkipFrames_004e9450, &opts->benchmarkSkipFrames)) {
            opts->applied->benchmarkSkipFrames = opts->benchmarkSkipFrames;
        } else if (thunk_FUN_00234510(args, &index, s_benchmarkFrames_004e94b0, &opts->benchmarkFrames)) {
            opts->applied->benchmarkFrames = opts->benchmarkFrames;
        } else if (FUN_00234770(args, &index, s_columnStatistics_004e9500, &opts->columnStatistics)) {
            opts->applied->columnStatistics = opts->columnStatistics;
        } else if (FUN_00234770(args, &index, s_allocateVisualContextInScratchpad_004e9560, &opts->allocateVisualContextInScratchpad)) {
            opts->applied->allocateVisualContextInScratchpad = opts->allocateVisualContextInScratchpad;
        } else if (FUN_00234470(args, &index, s_n_004e9708)) {
            index = index - 1;
            break;
        } else if (FUN_00234470(args, &index, s_dashdash_004e9710)) {
            break;
        } else {
            int isOption;
            StringList_CopyRetained(&optionRef, args, index);
            isOption = optionRef[0] == '-';
            ReleaseString(optionRef);
            if (!isOption) {
                break;
            }
            StringList_CopyRetained(&printRef, args, index);
            printf(s_unrecognized_004e9720, printRef);
            ReleaseString(printRef);
            StringList_CopyRetained(&helpRef2, args, 0);
            FUN_00233c10(helpRef2);
            ReleaseString(helpRef2);
            ReleaseObject(opts->intList);
            opts->intList = 0;
            ReleaseObject(opts->stringList);
            opts->stringList = 0;
            FUN_00124d60(0);
        }
    }

    while (index < argc) {
        if (!FUN_00234510(args, &index, s_n_004e9708, &repeat)) {
            StringList_CopyRetained(&currentRef, args, index);
            if (currentRef != 0) {
                ((int *)currentRef)[-1]++;
            }
            ReleaseString(modelFile);
            modelFile = currentRef;
            ReleaseString(currentRef);
            argumentRef = modelFile;
            if (argumentRef != 0) {
                ((int *)argumentRef)[-1]++;
            }
            StringList_AppendRetained((StringList *)opts->stringList, &argumentRef);
            ReleaseString(argumentRef);
            repeats = (IntList *)opts->intList;
            slot = repeats->count;
            if (slot < repeats->capacity) {
                repeats->count = *(volatile int *)&repeats->count + 1;
            } else {
                List_Resize(repeats, slot + 1, 4);
            }
            repeats->data[slot] = repeat;
            repeat = 1;
            index = index + 1;
        }
    }
    ReleaseString(modelFile);
}
