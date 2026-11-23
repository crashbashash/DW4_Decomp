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

/* p2Light.flags, kept by the visual context's light setters */
enum {
    P2_LIGHT_SPECULAR = 0x01,           /* a specular colour */
    P2_LIGHT_ATTENUATED = 0x02,         /* an attenuation other than (1, 0, 0) */
    P2_LIGHT_SPOT_CONE = 0x04,          /* a spot light's cutoff other than 180 degrees */
    P2_LIGHT_CHANGED = 0x08,
    P2_LIGHT_AMBIENT = 0x10,            /* an ambient colour */
    P2_LIGHT_LINEAR_ATTENUATION = 0x20  /* linear attenuation only, (0, l, 0) */
};

/* p2Material.flags */
enum {
    P2_MATERIAL_SPECULAR = 0x01,        /* a specular colour */
    P2_MATERIAL_CHANGED = 0x02,
    P2_MATERIAL_AMBIENT = 0x04          /* an ambient colour */
};

/* A light as the visual context keeps it: one 160-byte entry of its light array. The context fills the
 * colours, position, direction, falloff, attenuation and cutoff from its light setters and the p2 renderer
 * reads the eye-space copies and the flags. */
typedef struct p2Light {
    float position[4];       /* w is 1 */
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float localDirection[3]; /* as the caller set it; (0, 0, 1) by default */
    float falloff;           /* the falloff rate times 128 */
    float attenuation[3];    /* constant, linear, quadratic; (1, 0, 0) by default */
    float cutoffAngle;       /* degrees; 180 by default */
    float direction[3];      /* eye-space, normalised */
    unsigned int flags;
    float eyePosition[3];    /* position transformed by the model-view matrix, kept for point and spot lights */
    int type;                /* enum p2LightType */
    int active;              /* counted in p2ActiveLightCount */
    char f132[12];
    int slot;                /* the p2 light slot while the light is enabled in the context */
#ifdef __cplusplus
    bool enabled;            /* the context's per-light state (setLightState) */
#else
    unsigned char enabled;
#endif
    int lightType;           /* IG_GFX_LIGHT_TYPE the light was created with */
    char f156[4];
} p2Light;

/* The visual context's current material: one 112-byte record. */
typedef struct p2Material {
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float emission[4];
    float shininess;
    unsigned int flags;
    char f72[8];
    int slot;
    int colorMode;           /* the mode setMaterialColorMode set (IG color material mode) */
    float color[4];          /* the scene ambient, handed to p2SetLightingColor */
    char f104[8];
} p2Material;

#ifdef __cplusplus
extern "C" {
#endif

/* Statistics: how often each lighting state was set or switched. */
extern long long p2StatLightSets;
extern long long p2StatLightSwitches;
extern long long p2StatLightingModeSets;
extern long long p2StatLightingSwitches;
extern long long p2StatMaterialSets;
/* The lights enabled, and how many of them are point lights. */
extern int p2ActiveLightCount;
extern int p2ActivePointLightCount;
/* The material's specular state (p2SetMaterialSpecularState): specular lighting needs it on. */
extern int p2MaterialSpecularState;

void p2InitLighting(void);
void p2EnableLight(int slot);
void p2DisableLight(int slot);
void p2EnableLighting(void);
void p2DisableLighting(void);
/* Classifies the active lights and selects the lighting program when a light, the material or the
 * mode changed. */
void p2RefreshLightState(void);
void p2SetLight(int slot, p2Light *light);
void p2SetLightingColor(const float *color);
void p2SetMaterial(int slot, p2Material *material);
void p2SetLightingMode(int mode);
void p2WriteDirectionalLights(float rows[][4]);
/* Uploads a matrix to the renderer's VU1 matrix `slot` (3 projection, 0 model-view, 4 texture, 5 texture
 * generation, 2 the one lighting keeps in DAT_00491090). */
void p2SetMatrix(int slot, const float *matrix);
float p2AdjointMatrix(const float *m, float *adjoint);
void p2InvertMatrix(const float *m, float *inverse);
extern int p2NormalArrayMask;

#ifdef __cplusplus
}
#endif

#endif
