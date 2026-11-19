#include <string.h>
#include "dw4/p2/p2core.h"
#include "dw4/p2/p2dma.h"
#include "dw4/p2/dmaChannel.h"
#include "dw4/p2/p2draw.h"
#include "dw4/p2/p2lighting.h"
#include "dw4/p2/renderState.h"
#include "dw4/p2/p2viewport.h"
#include <math.h>

/* A VIF code, written to the packet as one word. */
typedef union p2VifCode {
    struct {
        unsigned short immediate;
        unsigned char num;
        unsigned char command;
    } field;
    unsigned int word;
} p2VifCode;

/* A DMA tag with its quadword count in the low half, written to the packet as four words. */
typedef union p2DmaTag {
    unsigned short qwc;
    unsigned int word[4];
} p2DmaTag;

/* p2DirtyFlags: the renderer state the next draw must send again. */
enum {
    P2_DIRTY_LIGHTING = 0x04
};

/* The lighting features of the VU1 programs. Each is a bit of p2VertexArrayMask, the capabilities the
 * program variant search matches, and a slot of p2VariantSlots, which holds the variant selected. */
enum {
    P2_FEATURE_INFINITE_LIGHTS = 7,      /* at most four directional lights (INFINITE_4) */
    P2_FEATURE_LOCAL_OBJECT_LIGHTS = 8,  /* local lights lit in object space (LOCAL_OBJ) */
    P2_FEATURE_DIRECTIONAL_LIGHTS = 13,  /* more directional lights (LIGHT_N_..._DIRECTIONAL) */
    P2_FEATURE_LOCAL_LIGHTS = 14,        /* local lights lit in eye space (POSITIONAL, LOCAL) */
    P2_FEATURE_SPOT_LIGHTS = 15          /* spot lights (SPOT) */
};

/* p2VertexArrayMask: the bits of the five lighting features, the normal arrays only lighting reads. */
enum {
    P2_NORMAL_ARRAYS = 0xE180
};

void p2WriteLights(unsigned int *cursor, int linearAttenuation);

extern char p2LightingEnabled;
extern char p2LightsNeedTransform;
extern int p2LightsChanged;
extern int p2LightingMode;
extern float p2LightingColor[4];
extern int p2DirectionalLightCount;
extern unsigned char p2DirectionalLights[P2_LIGHT_SLOTS];
extern p2Light *p2Lights[P2_LIGHT_SLOTS];
extern p2Material *p2Materials[P2_MATERIAL_SLOTS];
extern int p2NormalArraySource;
extern int p2NormalArrayMask;
extern int p2LightSpecular;
extern float p2LightMatrix[16];
extern p2DmaTag p2LightingTag;
extern p2VifCode p2LightingFlush;
extern p2VifCode p2LightingUnpack;
extern p2VifCode p2LightingMark;
extern p2VifCode p2LightingNop;
extern unsigned short p2MatrixAddresses[8];
extern p2VifCode p2MatrixFlush;
extern p2DmaTag p2MatrixTag;
extern p2VifCode p2MatrixUnpack;
extern p2VifCode p2MatrixMark;
extern p2VifCode p2MatrixNop;
extern int p2MatricesChanged;
extern float DAT_00491090[16];
/* p2RefreshLightState's light classification: whether the four-infinite-light program lights the
 * draw, how many local (point and spot) lights there are, whether one of them has an ambient colour,
 * how many of them attenuate linearly only, and which local-light programs are selected (1 local,
 * 2 local with infinite lights, 3 spot, 4 spot with infinite lights). */
extern int p2UseInfiniteLightProgram;
extern int p2LocalLightCount;
extern int p2LocalLightAmbient;
extern int p2LinearAttenuationLightCount;
extern char p2UseLocalLightProgram[5];
/* The slots of the local lights, and whether the light records carry a spot cone and an attenuation:
 * some light has one, or the general program that takes both lights the draw. */
extern unsigned char p2LocalLights[P2_LIGHT_SLOTS];
extern int p2LightSpotCone;
extern int p2LightAttenuation;
/* The variant of each lighting feature, indexed by the colour-material mode (bits 0-2) and: for the
 * infinite lights, specular lighting (bit 3); for the local lights, more than one light (bit 3) and
 * linear attenuation only (bit 4); for the spot lights, one spot light alone (bit 3). */
extern int p2InfiniteLightVariants[16];
extern int p2LocalObjectLightVariants[32];
extern int p2LocalLightVariants[32];
extern int p2SpotLightVariants[16];
extern int p2SpotInfiniteLightVariants[8];

void p2InitLighting(void) {
    int i;

    for (i = 0; i < P2_LIGHT_SLOTS; i++) {
        p2Lights[i] = 0;
    }
    p2Materials[0] = 0;
    p2Materials[1] = 0;
    p2DirtyFlags |= P2_DIRTY_LIGHTING;
    p2DisableCapability(12);
    p2LightsChanged = 1;
    p2LightsNeedTransform = 0;
    p2LightingProgramBits = 0;
    p2NormalArraySource = 0;
    p2NormalArrayMask = 0;
    p2DisableLighting();
}

void p2EnableLight(int slot) {
    int *active;
    p2Light **light;

    light = &p2Lights[slot];
    active = &(*light)->active;
    if (*active == 0) {
        *active = 1;
        p2ActiveLightCount += 1;
        if ((*light)->type == P2_LIGHT_POINT) {
            p2ActivePointLightCount += 1;
        }
    }
    p2LightsChanged = 1;
    p2StatLightSwitches += 1;
    p2DirtyFlags |= P2_DIRTY_LIGHTING | 0x80;
}

void p2DisableLight(int slot) {
    p2Light **light;
    int *active;

    light = &p2Lights[slot];
    active = &(*light)->active;
    if (*active != 0) {
        *active = 0;
        p2ActiveLightCount -= 1;
        if ((*light)->type == P2_LIGHT_POINT) {
            p2ActivePointLightCount -= 1;
        }
    }
    *light = 0;
    p2LightsChanged = 1;
    p2StatLightSwitches += 1;
    p2DirtyFlags |= P2_DIRTY_LIGHTING | 0x80;
}

void p2EnableLighting(void) {
    if (p2LightingEnabled != 1) {
        p2LightingEnabled = 1;
        p2LightsChanged = 1;
        p2StatLightingSwitches += 1;
        p2DirtyFlags |= P2_DIRTY_LIGHTING | 0x93;
    }
}

void p2DisableLighting(void) {
    if (p2LightingEnabled != 0) {
        p2LightingEnabled = 0;
        p2StatLightingSwitches += 1;
        p2VertexArrayMask &= ~P2_NORMAL_ARRAYS;
        p2LightsChanged = 1;
        p2DirtyFlags |= P2_DIRTY_LIGHTING | 0x93;
    }
}

void p2SetLight(int slot, p2Light *light) {
    if (light->flags & P2_LIGHT_CHANGED) {
        p2LightsChanged = 1;
        light->flags &= ~P2_LIGHT_CHANGED;
    }
    p2StatLightSets += 1;
    p2Lights[slot] = light;
    p2DirtyFlags |= P2_DIRTY_LIGHTING;
}

void p2SetLightingColor(const float *color) {
    memcpy(p2LightingColor, color, sizeof(p2LightingColor));
    p2DirtyFlags |= P2_DIRTY_LIGHTING;
}

void p2SetMaterial(int slot, p2Material *material) {
    p2StatMaterialSets += 1;
    if (material->flags & P2_MATERIAL_CHANGED) {
        p2LightsChanged = 1;
        material->flags &= ~P2_MATERIAL_CHANGED;
    }
    p2Materials[slot] = material;
    p2DirtyFlags |= P2_DIRTY_LIGHTING;
}

static inline int p2IsMode51(void) {
    unsigned char r = 1;

    if (p2LightingMode != 1 && p2LightingMode != 5) {
        r = 0;
    }
    return r;
}

static inline int p2NoLocalAmbient(void) {
    return !p2LocalLightAmbient;
}

/* Every local light attenuates linearly only and none has an ambient colour: the LINEAR_ATT programs
 * take two records per light instead of four. */
static inline int p2AllLinearAttenuation(void) {
    unsigned char r = 0;

    if (p2LinearAttenuationLightCount == p2LocalLightCount && p2NoLocalAmbient()) {
        r = 1;
    }
    return r;
}

/* Rebuilds the light tables when a light, the material or the mode changed: the slots of the
 * directional and the local lights, what the lights need, and the lighting features and variants the
 * VU1 programs are chosen by. */
void p2RefreshLightState(void) {
    int cpuLightLoading;
    int colorMaterial;
    char fastSpotLight;
    p2Light *light;
    int found;
    int slot;
    int eyeLocalLight;
    int colorMode;
    int variant;
    unsigned char linearOnly;
    int oldSource;

    cpuLightLoading = (p2ProgramFlags[p2CurrentProgram] >> 21) & 1;
    colorMaterial = (p2ProgramFlags[p2CurrentProgram] >> 12) & 1;
    fastSpotLight = (p2ProgramFlags[p2CurrentProgram] >> 24) & 1;
    if (p2LightingEnabled == 0 || ((p2ProgramFlags[p2CurrentProgram] >> 22) & 1)) {
        p2NormalArraySource = 0;
        p2NormalArrayMask = 0;
        if (p2LightingProgramBits != 0 && cpuLightLoading == 0) {
            p2LightingProgramBits = 0;
            p2DirtyFlags |= 2;
        }
        p2DirtyFlags |= 1;
        p2DirtyFlags &= ~P2_DIRTY_LIGHTING;
        p2VertexArrayMask &= ~P2_NORMAL_ARRAYS;
        return;
    }
    if (p2LightsChanged == 0) {
        return;
    }
    p2LocalLightCount = 0;
    p2LightSpotCone = 0;
    p2LightSpecular = (unsigned char)(colorMaterial && p2LightingMode == 3 && p2MaterialSpecularState);
    p2LightAttenuation = 0;
    p2LinearAttenuationLightCount = 0;
    p2LocalLightAmbient = 0;
    p2DirectionalLightCount = 0;
    for (slot = 0, found = 0; slot < P2_LIGHT_SLOTS && found < p2ActiveLightCount; slot++) {
        light = p2Lights[slot];
        if (light != 0 && light->active != 0) {
            found++;
            switch (light->type) {
            case P2_LIGHT_DIRECTIONAL:
                if (p2DirectionalLightCount < 4) {
                    p2DirectionalLights[p2DirectionalLightCount] = slot;
                    p2DirectionalLightCount++;
                }
                break;
            case P2_LIGHT_SPOT:
                if (light->flags & P2_LIGHT_SPOT_CONE) {
                    p2LightSpotCone = 1;
                }
                /* fall through: a spot light is a local light */
            case P2_LIGHT_POINT:
                p2LocalLights[p2LocalLightCount] = slot;
                p2LocalLightCount++;
                if (light->flags & P2_LIGHT_LINEAR_ATTENUATION) {
                    p2LinearAttenuationLightCount++;
                }
                if (light->flags & P2_LIGHT_AMBIENT) {
                    p2LocalLightAmbient = 1;
                }
                break;
            }
            if (light->flags & P2_LIGHT_ATTENUATED) {
                p2LightAttenuation = 1;
            }
            if ((light->flags & P2_LIGHT_SPECULAR) && (p2Materials[0]->flags & P2_MATERIAL_SPECULAR) &&
                p2MaterialSpecularState != 0) {
                p2LightSpecular = 1;
            }
        }
    }
    p2LightingProgramBits = 0;
    p2UseInfiniteLightProgram = 0;
    p2UseLocalLightProgram[1] = 0;
    p2UseLocalLightProgram[2] = 0;
    p2UseLocalLightProgram[3] = 0;
    p2UseLocalLightProgram[4] = 0;
    p2UseLocalLightProgram[0] = 0;
    p2VertexArrayMask &= ~P2_NORMAL_ARRAYS;
    if (p2LocalLightCount != 0) {
        eyeLocalLight = (p2ProgramFlags[p2CurrentProgram] >> 20) & 1;
        if (found == 1 && p2LightSpecular == 0 && p2LightSpotCone == 0) {
            colorMode = colorMaterial != 0 ? p2LightingMode : 0;
            linearOnly = p2NoLocalAmbient() && p2LinearAttenuationLightCount == p2LocalLightCount;
            if (linearOnly) {
                variant = colorMode | 0x10;
            } else {
                variant = colorMode;
            }
            p2UseLocalLightProgram[1] = 1;
            if (eyeLocalLight == 0) {
                p2VertexArrayMask |= 1 << P2_FEATURE_LOCAL_OBJECT_LIGHTS;
                p2VariantSlots[P2_FEATURE_LOCAL_OBJECT_LIGHTS].index = p2LocalObjectLightVariants[variant];
                if (cpuLightLoading == 0) {
                    p2LightingProgramBits = linearOnly ? 0x1000 : 0xC00;
                    p2DirtyFlags |= 2;
                }
            } else {
                p2VertexArrayMask |= 1 << P2_FEATURE_LOCAL_LIGHTS;
                p2VariantSlots[P2_FEATURE_LOCAL_LIGHTS].index = p2LocalLightVariants[variant];
            }
        } else if (p2LocalLightCount < 9 && p2LightSpotCone == 0 && p2LightSpecular == 0) {
            colorMode = colorMaterial != 0 ? p2LightingMode : 0;
            linearOnly = p2NoLocalAmbient() && p2LinearAttenuationLightCount == p2LocalLightCount;
            if (linearOnly) {
                variant = colorMode | 0x18;
            } else {
                variant = colorMode | 8;
            }
            p2UseLocalLightProgram[1] = 1;
            p2UseLocalLightProgram[2] = 1;
            if (eyeLocalLight == 0) {
                p2VertexArrayMask |= 1 << P2_FEATURE_LOCAL_OBJECT_LIGHTS;
                p2VariantSlots[P2_FEATURE_LOCAL_OBJECT_LIGHTS].index = p2LocalObjectLightVariants[variant];
                if (cpuLightLoading == 0) {
                    p2LightingProgramBits = linearOnly ? 0x1800 : 0x1400;
                    p2DirtyFlags |= 2;
                }
            } else {
                p2VertexArrayMask |= 1 << P2_FEATURE_LOCAL_LIGHTS;
                p2VariantSlots[P2_FEATURE_LOCAL_LIGHTS].index = p2LocalLightVariants[variant];
            }
        } else if (fastSpotLight && p2LightSpotCone != 0) {
            p2VertexArrayMask |= 1 << P2_FEATURE_SPOT_LIGHTS;
            if (p2LocalLightCount == 1 && p2DirectionalLightCount == 0) {
                p2VariantSlots[P2_FEATURE_SPOT_LIGHTS].index = p2SpotLightVariants[p2LightingMode | 8];
            } else {
                p2VariantSlots[P2_FEATURE_SPOT_LIGHTS].index = p2SpotInfiniteLightVariants[p2LightingMode];
                p2UseLocalLightProgram[4] = 1;
            }
            p2LightSpecular = 0;
            p2UseLocalLightProgram[3] = 1;
            p2LightAttenuation = 0;
        } else if (colorMaterial != 0) {
            p2VertexArrayMask |= 1 << P2_FEATURE_SPOT_LIGHTS;
            p2VariantSlots[P2_FEATURE_SPOT_LIGHTS].index = p2SpotLightVariants[p2LightingMode];
            p2LightSpecular = 1;
            p2LightAttenuation = 1;
        } else if (p2LightSpotCone != 0) {
            p2VariantSlots[P2_FEATURE_SPOT_LIGHTS].index = 0;
            p2LightSpecular = 1;
            p2LightAttenuation = 1;
            p2VertexArrayMask |= 1 << P2_FEATURE_SPOT_LIGHTS;
        } else {
            p2VariantSlots[P2_FEATURE_LOCAL_LIGHTS].index = 0;
            p2LightSpecular = 1;
            p2LightAttenuation = 1;
            p2LightSpotCone = 1;
            p2VertexArrayMask |= 1 << P2_FEATURE_LOCAL_LIGHTS;
        }
    } else if (found < 5) {
        p2UseInfiniteLightProgram = 1;
        p2VertexArrayMask |= 1 << P2_FEATURE_INFINITE_LIGHTS;
        p2VariantSlots[P2_FEATURE_INFINITE_LIGHTS].index =
            p2InfiniteLightVariants[(p2LightSpecular << 3) | (colorMaterial != 0 ? p2LightingMode : 0)];
        if (cpuLightLoading == 0) {
            p2LightingProgramBits = p2LightSpecular != 0 ? 0x800 : 0x400;
            p2DirtyFlags |= 2;
        }
    } else {
        p2VertexArrayMask |= 1 << P2_FEATURE_DIRECTIONAL_LIGHTS;
        if (p2LightSpecular != 0) {
            p2VariantSlots[P2_FEATURE_DIRECTIONAL_LIGHTS].index = 1;
        } else {
            p2VariantSlots[P2_FEATURE_DIRECTIONAL_LIGHTS].index = 0;
        }
    }
    oldSource = p2NormalArraySource;
    p2NormalArrayMask = (int)(p2VertexArrayMask & P2_NORMAL_ARRAYS);
    if (p2VertexArrayMask & (1 << P2_FEATURE_INFINITE_LIGHTS)) {
        p2NormalArraySource = p2VariantSlots[P2_FEATURE_INFINITE_LIGHTS].index;
    } else if (p2VertexArrayMask & (1 << P2_FEATURE_DIRECTIONAL_LIGHTS)) {
        p2NormalArraySource = (p2VariantSlots[P2_FEATURE_DIRECTIONAL_LIGHTS].index << 4) | 0xF;
    } else if (p2VertexArrayMask & (1 << P2_FEATURE_LOCAL_LIGHTS)) {
        p2NormalArraySource = (p2VariantSlots[P2_FEATURE_LOCAL_LIGHTS].index << 9) | 0x1FF;
    } else if (p2VertexArrayMask & (1 << P2_FEATURE_SPOT_LIGHTS)) {
        p2NormalArraySource = (p2VariantSlots[P2_FEATURE_SPOT_LIGHTS].index << 10) | 0x3FF;
    } else if (p2VertexArrayMask & (1 << P2_FEATURE_LOCAL_OBJECT_LIGHTS)) {
        p2NormalArraySource = (p2VariantSlots[P2_FEATURE_LOCAL_OBJECT_LIGHTS].index << 15) | 0x7FFF;
    }
    if (oldSource != p2NormalArraySource) {
        p2DirtyFlags |= 0x81;
    }
    p2LightsChanged = 0;
}

void p2SetLightingMode(int mode) {
    p2LightingMode = mode;
    p2LightsChanged = 1;
    p2StatLightingModeSets += 1;
    p2DirtyFlags |= P2_DIRTY_LIGHTING | 0x01;
}

unsigned int *p2AppendLightingPacket(unsigned int *cursor) {
    unsigned char newPacket;
    int refresh;
    unsigned int *tag;
    int colorMaterial;
    int mode51;
    int linearAttenuation;
    int words;
    unsigned int *p;

    if (p2LightingEnabled != 0) {
        refresh = cursor == (unsigned int *)-1;
        newPacket = cursor == 0 || refresh;
        tag = 0;
        colorMaterial = (p2ProgramFlags[p2CurrentProgram] >> 12) & 1;
        mode51 = p2IsMode51();
        linearAttenuation = p2AllLinearAttenuation();
        if ((refresh && (p2DirtyFlags & P2_DIRTY_LIGHTING)) ||
            (p2UseInfiniteLightProgram == 0 && p2UseLocalLightProgram[1] == 0)) {
            return 0;
        }
        if (newPacket) {
            cursor = (unsigned int *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
            tag = cursor;
            cursor += 4;
        }
        if (p2UseLocalLightProgram[1] != 0) {
            p2LightingTag.qwc = p2LocalLightCount * (linearAttenuation ? 2 : 4) + 5;
            p2LightingUnpack.field.num = p2LocalLightCount * (linearAttenuation ? 2 : 4) + 4;
            words = p2LightingUnpack.field.num * 4;
            if (p2UseLocalLightProgram[2] != 0) {
                p2LightingTag.qwc += 7;
                p2LightingUnpack.field.num += 7;
                words += 28;
                if (colorMaterial && mode51) {
                    words += 4;
                    p2LightingTag.qwc += 1;
                    p2LightingUnpack.field.num += 1;
                }
            }
            p2LightingUnpack.field.immediate = p2VuBuffers.address7;
            /* matching construct: hand search — the word written through a copy of the cursor */
            p = cursor++;
            *p = p2LightingFlush.word;
            p = cursor++;
            *p = p2LightingMark.word;
            p = cursor++;
            *p = p2LightingNop.word;
            p = cursor++;
            *p = p2LightingUnpack.word;
            p2WriteLights(cursor, linearAttenuation);
            cursor += words;
        } else {
            if (p2LightSpecular != 0) {
                p2LightingUnpack.field.num = 6;
                p2LightingTag.qwc = 7;
                words = 24;
            } else {
                p2LightingUnpack.field.num = 3;
                p2LightingTag.qwc = 4;
                words = 12;
            }
            p2LightingUnpack.field.immediate = p2VuBuffers.address7;
            p = cursor++;
            *p = p2LightingFlush.word;
            p = cursor++;
            *p = p2LightingNop.word;
            p = cursor++;
            *p = p2LightingMark.word;
            p = cursor++;
            *p = p2LightingUnpack.word;
            p2WriteDirectionalLights((float (*)[4])cursor);
            cursor += words;
        }
        if (newPacket) {
            tag[0] = p2LightingTag.word[0];
            tag[1] = p2LightingTag.word[1];
            tag[2] = p2LightingTag.word[2];
            tag[3] = p2LightingTag.word[3];
            p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)cursor;
            if (p2DmaCurrentPacket[P2_DMA_VIF1]->cursor >= p2DmaCurrentPacket[P2_DMA_VIF1]->limit) {
                if (p2DisplayListMode != 0) {
                    p2GrowDisplayList();
                } else {
                    p2SubmitDmaPacket(P2_DMA_VIF1);
                }
            }
        }
    }
    return cursor;
}

/* Writes the first four directional lights' directions as three rows (x, y, z of each light),
 * and with specular lighting three more rows of their half vectors toward a viewer on +z. */
void p2WriteDirectionalLights(float rows[][4]) {
    int cpuLightLoading;
    float *m;
    float zero;
    float *column;
    int i;
    p2Light *light;

    cpuLightLoading = (p2ProgramFlags[p2CurrentProgram] >> 21) & 1;
    zero = 0.0f;
    m = p2LightMatrix;
    if (p2LightsNeedTransform != 0 && cpuLightLoading == 0) {
        p2LightCalcPending = 1;
    }
    for (i = 0; i < 4; i++) {
        light = p2Lights[p2DirectionalLights[i]];
        column = &rows[0][i];
        if (light != 0 && i < p2DirectionalLightCount) {
            if (p2LightsNeedTransform != 0 && cpuLightLoading != 0) {
                float x = light->direction[0], y = light->direction[1], z = light->direction[2];
                float tx = x * m[0] + y * m[1] + z * m[2];
                float ty = x * m[4] + y * m[5] + z * m[6];
                float tz = x * m[8] + y * m[9] + z * m[10];
                float scale = 1.0f / sqrtf(tx * tx + ty * ty + tz * tz);
                column[0] = tx * scale;
                column[4] = ty * scale;
                column[8] = tz * scale;
                if (p2LightSpecular != 0) {
                    float hx, hy, hz, length2, halfScale;
                    z = z + 1.0f;
                    hx = x * m[0] + y * m[1] + z * m[2];
                    hy = x * m[4] + y * m[5] + z * m[6];
                    hz = x * m[8] + y * m[9] + z * m[10];
                    length2 = hx * hx + hy * hy + hz * hz;
                    if (length2 != zero) halfScale = 1.0f / sqrtf(length2); else halfScale = zero;
                    column[12] = hx * halfScale;
                    column[16] = hy * halfScale;
                    column[20] = hz * halfScale;
                }
            } else {
                column[0] = light->direction[0];
                column[4] = light->direction[1];
                column[8] = light->direction[2];
                if (p2LightSpecular != 0) {
                    column[12] = light->direction[0];
                    column[16] = light->direction[1];
                    column[20] = 1.0f + light->direction[2];
                }
            }
        } else {
            column[0] = 0.0f;
            column[4] = 0.0f;
            column[8] = 0.0f;
            if (p2LightSpecular != 0) {
                column[12] = 0.0f;
                column[16] = 0.0f;
                column[20] = 0.0f;
            }
        }
    }
}

/* Copies a 4x4 matrix: four quadwords through a2 and a3 when both are 16-byte aligned, else word by word. */
static inline void p2CopyMatrix(float *dst, const float *src) {
    int i;

    if ((((unsigned int)dst | (unsigned int)src) & 0xF) == 0) {
        __asm__("lq $6, 0(%1)\n\tlq $7, 16(%1)\n\tsq $6, 0(%0)\n\tsq $7, 16(%0)\n\tlq $6, 32(%1)\n\tlq $7, 48(%1)\n\tsq $6, 32(%0)\n\tsq $7, 48(%0)" : : "r"(dst), "r"(src) : "$6", "$7", "memory");
    } else {
        for (i = 0; i < 16; i++) {
            *dst++ = *src++;
        }
    }
}

/* Uploads one matrix of the VU1 matrix stack: a packet that unpacks it to p2MatrixAddresses[slot] (the
 * projection, slot 3, scaled by the viewport), then marks the slot changed in p2MatricesChanged and keeps
 * the copies lighting reads (slot 0 in p2LightMatrix, slot 2 in DAT_00491090). */
void p2SetMatrix(int slot, const float *matrix) {
    unsigned __int128 *q;
    float scale;

    q = (unsigned __int128 *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
    p2MatrixUnpack.field.immediate = p2MatrixAddresses[slot];
    ((unsigned int *)q)[0] = p2MatrixTag.word[0];
    ((unsigned int *)q)[1] = p2MatrixTag.word[1];
    ((unsigned int *)q)[2] = p2MatrixTag.word[2];
    ((unsigned int *)q)[3] = p2MatrixTag.word[3];
    q++;
    ((unsigned int *)q)[0] = p2MatrixMark.word;
    ((unsigned int *)q)[1] = p2MatrixFlush.word;
    ((unsigned int *)q)[2] = p2MatrixNop.word;
    ((unsigned int *)q)[3] = p2MatrixUnpack.word;
    q++;
    p2CopyMatrix((float *)q, matrix);
    if (slot == 3) {
        scale = 1.0f / p2ViewportScale;
        ((float *)q)[0] *= scale;
        ((float *)q)[4] *= scale;
        ((float *)q)[8] *= scale;
        ((float *)q)[12] *= scale;
        ((float *)q)[1] *= scale;
        ((float *)q)[5] *= scale;
        ((float *)q)[9] *= scale;
        ((float *)q)[13] *= scale;
    }
    q += 4;
    p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)q;
    if (p2DmaCurrentPacket[P2_DMA_VIF1]->cursor >= p2DmaCurrentPacket[P2_DMA_VIF1]->limit) {
        if (p2DisplayListMode != 0) {
            p2GrowDisplayList();
        } else {
            p2SubmitDmaPacket(P2_DMA_VIF1);
        }
    }
    switch (slot) {
    case 0:
        p2MatricesChanged |= 0xF;
        p2CopyMatrix(p2LightMatrix, matrix);
        p2AppendLightingPacket((unsigned int *)-1);
        break;
    case 3:
        p2MatricesChanged |= 4;
        break;
    case 4:
        p2MatricesChanged |= 8;
        break;
    case 5:
        p2MatricesChanged |= 8;
        break;
    case 2:
        p2CopyMatrix(DAT_00491090, matrix);
        p2MatricesChanged &= ~3;
        break;
    }
    p2LightCalcPending = 1;
}

float p2AdjointMatrix(const float *m, float *adjoint) {
    /* matching construct: declaration-order search — MWCC hands out the float registers in this order */
    float m0;
    float m4;
    float m8;
    float m12;
    float m1;
    float m5;
    float m9;
    float m13;
    float m2;
    float m6;
    float m10;
    float m14;
    float m3;
    float m7;
    float m11;
    float m15;
    /* rRRcCC: the 2x2 determinant of rows RR and columns CC */
    float r13c01;
    float r12c23;
    float r12c03;
    float r13c12;
    float r13c23;
    float r13c13;
    float r23c23;
    float r12c02;
    float r23c03;
    float r13c03;
    float r23c13;
    float r12c13;
    float r13c02;
    float r23c02;
    float r12c12;
    float r12c01;
    float r23c12;
    float r23c01;
    m9 = m[9];
    m15 = m[15];
    m11 = m[11];
    m13 = m[13];
    m10 = m[10];
    m14 = m[14];
    m5 = m[5];
    m6 = m[6];
    m4 = m[4];
    m7 = m[7];
    m8 = m[8];
    m0 = m[0];
    m1 = m[1];
    m2 = m[2];
    m3 = m[3];
    m12 = m[12];
    r23c13 = m9*m15 - m13*m11;
    r23c23 = m10*m15 - m14*m11;
    r23c12 = m9*m14 - m13*m10;
    adjoint[0] = (((m5*r23c23) - (m6*r23c13)) + m7*r23c12);
    r23c03 = m8*m15 - m12*m11;
    r23c02 = m8*m14 - m12*m10;
    adjoint[4] = -(((m4*r23c23) - (m6*r23c03)) + m7*r23c02);
    r23c01 = m8*m13 - m12*m9;
    adjoint[8] = (((m4*r23c13) - (m5*r23c03)) + m7*r23c01);
    adjoint[12] = -(((m4*r23c12) - (m5*r23c02)) + m6*r23c01);
    adjoint[1] = -(((m1*r23c23) - (m2*r23c13)) + m3*r23c12);
    adjoint[5] = (((m0*r23c23) - (m2*r23c03)) + m3*r23c02);
    adjoint[9] = -(((m0*r23c13) - (m1*r23c03)) + m3*r23c01);
    adjoint[13] = (((m0*r23c12) - (m1*r23c02)) + m2*r23c01);
    r13c13 = m5*m15 - m13*m7;
    r13c23 = m6*m15 - m14*m7;
    r13c12 = m5*m14 - m13*m6;
    adjoint[2] = (((m1*r13c23) - (m2*r13c13)) + m3*r13c12);
    r13c03 = m4*m15 - m12*m7;
    r13c02 = m4*m14 - m12*m6;
    adjoint[6] = -(((m0*r13c23) - (m2*r13c03)) + m3*r13c02);
    r13c01 = m4*m13 - m12*m5;
    adjoint[10] = (((m0*r13c13) - (m1*r13c03)) + m3*r13c01);
    adjoint[14] = -(((m0*r13c12) - (m1*r13c02)) + m2*r13c01);
    r12c13 = m5*m11 - m9*m7;
    r12c23 = m6*m11 - m10*m7;
    r12c12 = m5*m10 - m9*m6;
    adjoint[3] = -(((m1*r12c23) - (m2*r12c13)) + m3*r12c12);
    r12c03 = m4*m11 - m8*m7;
    r12c02 = m4*m10 - m8*m6;
    adjoint[7] = (((m0*r12c23) - (m2*r12c03)) + m3*r12c02);
    r12c01 = m4*m9 - m8*m5;
    adjoint[11] = -(((m0*r12c13) - (m1*r12c03)) + m3*r12c01);
    adjoint[15] = (((m0*r12c12) - (m1*r12c02)) + m2*r12c01);
    return m0 * adjoint[0] - m1 * adjoint[4] + m2 * adjoint[8] - m3 * adjoint[12];
}

void p2InvertMatrix(const float *m, float *inverse) {
    float adjoint[16];
    int i;
    float scale = 1.0f / p2AdjointMatrix(m, adjoint);

    for (i = 0; i < 16; i++) {
        inverse[i] = scale * adjoint[i];
    }
}
