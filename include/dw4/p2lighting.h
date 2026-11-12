/* p2lighting.h - the p2 renderer's light and material registry.
 *
 * The graphics visual context owns the lights and the material; the renderer keeps pointers to
 * them in eight light slots and two material slots. Registering or switching one marks the
 * lighting dirty, and the next draw rebuilds the light tables and the constant block the VU1
 * light programs read. */
#ifndef DW4_P2LIGHTING_H
#define DW4_P2LIGHTING_H

#define P2_LIGHT_SLOTS 8
#define P2_MATERIAL_SLOTS 2

enum p2LightType {
    P2_LIGHT_DIRECTIONAL,
    P2_LIGHT_POINT,
    P2_LIGHT_SPOT
};

/* p2Light.flags */
enum {
    P2_LIGHT_CHANGED = 0x08
};

/* p2Material.flags */
enum {
    P2_MATERIAL_CHANGED = 0x02
};

/* A light as the visual context keeps it: one 160-byte entry of its light array. */
typedef struct p2Light {
    char f0[96];
    float direction[3];      /* eye-space, normalised */
    unsigned int flags;
    char f112[12];
    int type;                /* enum p2LightType */
    int active;              /* counted in p2ActiveLightCount */
    char f132[28];
} p2Light;

/* The visual context's current material. */
typedef struct p2Material {
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float emission[4];
    float shininess;
    unsigned int flags;
    char f72[8];
    int slot;
    char f84[4];
    float color[4];
} p2Material;

void p2InitLighting(void);
void p2EnableLight(int slot);
void p2DisableLight(int slot);
void p2EnableLighting(void);
void p2DisableLighting(void);
void p2SetLight(int slot, p2Light *light);
void p2SetLightingColor(const float *color);
void p2SetMaterial(int slot, p2Material *material);
void p2SetLightingMode(int mode);
void p2WriteDirectionalLights(float rows[][4]);
float p2AdjointMatrix(const float *m, float *adjoint);
void p2InvertMatrix(const float *m, float *inverse);

#endif
