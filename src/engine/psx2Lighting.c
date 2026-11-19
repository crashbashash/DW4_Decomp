#include <string.h>
#include "dw4/p2/p2core.h"
#include "dw4/p2/p2dma.h"
#include "dw4/p2/dmaChannel.h"
#include "dw4/p2/p2draw.h"
#include "dw4/p2/p2lighting.h"
#include "dw4/p2/renderState.h"
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

/* p2VertexArrayMask: the bits of the normal arrays, which only lighting reads. */
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
/* p2RefreshLightState's light classification: whether the four-infinite-light program lights the
 * draw, how many local (point and spot) lights there are, whether one of them has an ambient colour,
 * how many of them attenuate linearly only, and which local-light programs are selected (1 local,
 * 2 local with infinite lights, 3 spot, 4 spot with infinite lights). */
extern int p2UseInfiniteLightProgram;
extern int p2LocalLightCount;
extern int p2LocalLightAmbient;
extern int p2LinearAttenuationLightCount;
extern char p2UseLocalLightProgram[5];

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

/* the lighting mode lights with the texgen variant */
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
    int texgen;
    int mode51;
    int linearAttenuation;
    int words;
    unsigned int *p;

    if (p2LightingEnabled != 0) {
        refresh = cursor == (unsigned int *)-1;
        newPacket = cursor == 0 || refresh;
        tag = 0;
        texgen = (p2ProgramFlags[p2CurrentProgram] >> 12) & 1;
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
                if (texgen && mode51) {
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
    int objectSpace;
    float *m;
    float zero;
    float *column;
    int i;
    p2Light *light;

    objectSpace = (p2ProgramFlags[p2CurrentProgram] >> 21) & 1;
    zero = 0.0f;
    m = p2LightMatrix;
    if (p2LightsNeedTransform != 0 && objectSpace == 0) {
        p2LightCalcPending = 1;
    }
    for (i = 0; i < 4; i++) {
        light = p2Lights[p2DirectionalLights[i]];
        column = &rows[0][i];
        if (light != 0 && i < p2DirectionalLightCount) {
            if (p2LightsNeedTransform != 0 && objectSpace != 0) {
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

static inline void p2CopyMatrix(float *dst, const float *src) {
    int i;

    if ((((unsigned int)dst | (unsigned int)src) & 0xF) == 0) {
        ((__int128 *)dst)[0] = ((const __int128 *)src)[0];
        ((__int128 *)dst)[1] = ((const __int128 *)src)[1];
        ((__int128 *)dst)[2] = ((const __int128 *)src)[2];
        ((__int128 *)dst)[3] = ((const __int128 *)src)[3];
    } else {
        for (i = 0; i < 16; i++) {
            *dst++ = *src++;
        }
    }
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
