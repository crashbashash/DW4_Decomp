#include "dw4/p2lighting.h"

/* p2DirtyFlags: the renderer state the next draw must send again. */
enum {
    P2_DIRTY_LIGHTING = 0x04
};

/* p2VertexArrayMask: the bits of the normal arrays, which only lighting reads. */
enum {
    P2_NORMAL_ARRAYS = 0xE180
};

void *memcpy(void *dst, const void *src, unsigned int size);
float sqrtf(float x);
void p2DisableCapability(int capability);

extern int p2DirtyFlags;
extern unsigned int p2ProgramFlags[];
extern int p2CurrentProgram;
extern long long p2VertexArrayMask;
extern int p2LightCalcPending;

extern char p2LightingEnabled;
extern char p2LightsNeedTransform;
extern int p2LightsChanged;
extern int p2LightingMode;
extern float p2LightingColor[4];
extern int p2ActiveLightCount;
extern int p2ActivePointLightCount;
extern int p2DirectionalLightCount;
extern unsigned char p2DirectionalLights[P2_LIGHT_SLOTS];
extern p2Light *p2Lights[P2_LIGHT_SLOTS];
extern p2Material *p2Materials[P2_MATERIAL_SLOTS];
extern int p2NormalArraySource;
extern int p2NormalArrayMask;
extern int p2LightSpecular;
extern float p2LightMatrix[16];
extern int p2LightingProgramBits;

extern long long p2StatLightingSwitches;
extern long long p2StatMaterialSets;
extern long long p2StatLightingModeSets;
extern long long p2StatLightSets;
extern long long p2StatLightSwitches;

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

void p2SetLightingMode(int mode) {
    p2LightingMode = mode;
    p2LightsChanged = 1;
    p2StatLightingModeSets += 1;
    p2DirtyFlags |= P2_DIRTY_LIGHTING | 0x01;
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

/* Stores the adjoint (the transposed cofactors) of the row-major 4x4 matrix m. The value returned
 * takes the first row against the adjoint's first column with alternating signs, which is the
 * determinant only when m[1] * adjoint[4] + m[3] * adjoint[12] is zero. */
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
