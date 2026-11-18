#ifndef DW4_VIEWEROPTIONS_H
#define DW4_VIEWEROPTIONS_H

/* The 240-byte viewer options object every viewer object shares (`g_sharedViewerOptions`): igViewerDefaults_Construct
 * fills it from the INSIGHT properties, and it is freed when its use count drops to zero. The members up to
 * `allocateVisualContextInScratchPad` are the properties' own, named after them. */
struct SharedViewerOptions {
    char *extraCommandLine;                          /* +0 */
    unsigned char showBBox;                          /* +4 */
    unsigned char showNormals;                       /* +5 */
    char pad6[2];
    float normalsColor[4];                           /* +8 */
    float invalidStoredNormalsColor[4];              /* +24 */
    float scaledNormalsColor[4];                     /* +40 */
    float invalidNormalsPrecision;                   /* +56 */
    unsigned char autoSelectCamera;                  /* +60 */
    char pad61[3];
    float horizontalFieldOfView;                     /* +64 */
    unsigned char autoPlanes;                        /* +68 */
    char pad69[3];
    float defaultNearPlane;                          /* +72 */
    float defaultFarPlane;                           /* +76 */
    float upVector[3];                               /* +80 */
    unsigned char autoSceneLights;                   /* +92 */
    unsigned char autoHeadLight;                     /* +93 */
    unsigned char useSceneLights;                    /* +94 */
    unsigned char useHeadLight;                      /* +95 */
    unsigned char useHeadLightSpecular;              /* +96 */
    char pad97[3];
    float headLightDiffuse[4];                       /* +100 */
    float headLightSpecular[4];                      /* +116 */
    float headLightAmbient[4];                       /* +132 */
    float clearColor[4];                             /* +148 */
    unsigned char wireframeMode;                     /* +164 */
    unsigned char forceWireframe;                    /* +165 */
    unsigned char backFaceCullingMode;               /* +166 */
    unsigned char forceBackFaceCulling;              /* +167 */
    unsigned char alphaTest;                         /* +168 */
    unsigned char forceAlphaTest;                    /* +169 */
    char pad170[2];
    float alphaTestReference;                        /* +172 */
    float maxFrameRate;                              /* +176 */
    unsigned char optimizeTextures;                  /* +180 */
    unsigned char halfBuffer;                        /* +181 */
    unsigned char palVideoMode;                      /* +182 */
    char pad183[1];
    int width;                                       /* +184 */
    int height;                                      /* +188 */
    int swapInterval;                                /* +192 */
    int colorBits;                                   /* +196 */
    int alphaBits;                                   /* +200 */
    int depthBits;                                   /* +204 */
    int stencilBits;                                 /* +208 */
    unsigned char reportVideoFormat;                 /* +212 */
    unsigned char showLogo;                          /* +213 */
    unsigned char showUI;                            /* +214 */
    unsigned char enableMayaControls;                /* +215 */
    unsigned char benchmark;                         /* +216 */
    char pad217[3];
    int benchmarkSkipFrames;                         /* +220 */
    int benchmarkFrames;                             /* +224 */
    unsigned char columnStatistics;                  /* +228 */
    unsigned char allocateVisualContextInScratchPad; /* +229 */
    char pad230[2];
    int useCount;                                    /* +232 */
    int internedString;                              /* +236: an interned string released with the object; what it holds is not traced */
};

/* The viewer's parsed command line: the option block, then the repeat counts and the model names. */
struct App;

extern "C" {
extern SharedViewerOptions *g_sharedViewerOptions;
SharedViewerOptions *igViewerDefaults_Construct(SharedViewerOptions *options);
void igCommandLine_ParseArgs(App *args, int argc, char **argv);
}

#endif
