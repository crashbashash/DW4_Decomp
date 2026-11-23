void igPsx2VisualContext_ResetLight(p2Light *light) {
    light->slot = 0;
    light->position[0] = 0.0f;
    light->position[1] = 0.0f;
    light->position[2] = 0.0f;
    light->position[3] = 1.0f;
    light->localDirection[0] = 0.0f;
    light->localDirection[1] = 0.0f;
    light->localDirection[2] = 1.0f;
    light->diffuse[0] = 1.0f;
    light->diffuse[1] = 1.0f;
    light->diffuse[2] = 1.0f;
    light->diffuse[3] = 1.0f;
    light->ambient[0] = 0.600000024f;
    light->ambient[1] = 0.600000024f;
    light->ambient[2] = 0.600000024f;
    light->ambient[3] = 1.0f;
    light->specular[0] = 0.0f;
    light->specular[1] = 0.0f;
    light->specular[2] = 0.0f;
    light->specular[3] = 1.0f;
    light->cutoffAngle = 180.0f;
    light->attenuation[0] = 1.0f;
    light->attenuation[1] = 0.0f;
    light->attenuation[2] = 0.0f;
    light->falloff = 0.0f;
    light->enabled = 0;
    light->lightType = IG_GFX_LIGHT_TYPE_DIRECTIONAL;
    light->type = P2_LIGHT_DIRECTIONAL;
    light->direction[0] = 0.0f;
    light->direction[1] = 0.0f;
    light->direction[2] = 0.0f;
    light->eyePosition[0] = 0.0f;
    light->eyePosition[1] = 0.0f;
    light->eyePosition[2] = 0.0f;
    light->flags = P2_LIGHT_CHANGED;
}

void igPsx2VisualContext_InitializeLighting(Gap::Gfx::igPsx2VisualContext *vc) {
    int lightCount;
    igPsx2LightPool *pool;
    int i;
    lightCount = 0x20;
    igGetRegistryValue_Int(g_objectSystem->configRegistry, 4, "IG_GFX_VC_LIGHT_ARRAY_SIZE", &lightCount, 0x20, 0);
    pool = new ((igMemoryPoolView *)vc->getListMemoryPool()) igPsx2LightPool(lightCount, "IG_GFX_VC_LIGHT_ARRAY_SIZE");
    vc->_pLightList = (int)pool;
    p2Material *material = (p2Material *)Memory_AllocateAlignedWithAllocator(sizeof(p2Material), 0x10, (igMemoryPoolView *)vc->getInternalMemoryPool());
    if (material != 0) igPsx2VisualContext_ResetMaterial(material);
    vc->_currentMaterial = (int)material;
    igPsx2VisualContext_ResetMaterial((p2Material *)vc->_currentMaterial);
    DAT_00560850[0] = vc->getCapability(IG_GFX_CAPABILITY_MAX_LIGHTS);
    DAT_00560858[0] = (int *)((igMemoryPoolView *)vc->getInternalMemoryPool())->Allocate(DAT_00560850[0] * 4);
    for (i = 0; i < DAT_00560850[0]; i++) {
        DAT_00560858[0][i] = -1;
    }
    igMatrix44f_SetIdentity(g_gfxIdentityMatrix.m);
}

void igPsx2VisualContext_UninitializeLighting(Gap::Gfx::igPsx2VisualContext *vc, int keepStorage) {
    igPsx2LightPool *pool;
    int handle;
    handle = ((igPsx2LightPool *)vc->_pLightList)->capacity - 1;
    while (-1 < handle) {
        if (((igPsx2LightPool *)vc->_pLightList)->isIndexAllocated(handle)) {
            vc->deleteLight(handle);
        }
        handle--;
    }
    if (keepStorage == 0) {
        pool = (igPsx2LightPool *)vc->_pLightList;
        delete pool;
        vc->_pLightList = 0;
        Memory_FreeBuffer(DAT_00560858[0]);
        if (vc->_currentMaterial != 0) {
            Memory_FreeBufferAliasB((void *)vc->_currentMaterial);
        }
    }
}

/* The light a handle names: an element of the context's light pool. A macro, not an inline function: retail
 * reads the pool again at every use, and an inline call's result is held in a temporary instead. */
#define lightAt(vc, handle) (((igPsx2LightPool *)(vc)->_pLightList)->elements + (handle))

static inline bool colorEqual(const float *a, const float *b) {
    return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3];
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setLightingState(bool enb) {
    if (_bLightingEnabled == (enb & 0xFF)) {
        DAT_00560848[0] += 1;
    }
    if (g_igPsx2DisableExt_ext1Enabled != 0) {
        enb = 0;
    }
    _bLightingEnabled = enb;
    if (_bLightingEnabled == 1) {
        p2EnableCapability(8);
        return;
    }
    p2DisableCapability(8);
}

bool igPsx2VisualContext::getLightingState() const {
    return _bLightingEnabled;
}

int igPsx2VisualContext::createLight(IG_GFX_LIGHT_TYPE type) {
    igPsx2LightPool *pool;
    int handle;
    p2Light *light;
    pool = (igPsx2LightPool *)_pLightList;
    handle = pool->getFreeElement();
    light = lightAt(this, handle);
    igPsx2VisualContext_ResetLight(light);
    light->lightType = type;
    switch (type) {
    case IG_GFX_LIGHT_TYPE_DIRECTIONAL:
        light->type = P2_LIGHT_DIRECTIONAL;
        break;
    case IG_GFX_LIGHT_TYPE_POINT:
        light->type = P2_LIGHT_POINT;
        break;
    case IG_GFX_LIGHT_TYPE_SPOT:
        light->type = P2_LIGHT_SPOT;
        break;
    }
    return handle;
}

void igPsx2VisualContext::deleteLight(int lighthandle) {
    p2Light *light = lightAt(this, lighthandle);
    igPsx2LightPool *pool;
    /* matching construct: retail tests the element pointer twice (the pool's element accessor checks it too) */
    if (light != 0 && light != 0) {
        if (light->enabled != 0) {
            setLightState(lighthandle, 0);
        }
        pool = (igPsx2LightPool *)_pLightList;
        pool->freeElement(lighthandle);
    }
}

bool igPsx2VisualContext::setLightState(int lightHandle, bool enable) {
    int i;
    p2Light *light = lightAt(this, lightHandle);
    if (light == 0) {
        return 0;
    }
    if (light->enabled == enable) {
        DAT_005608cc[0] += 1;
    }
    if (light->enabled == enable) {
        return 1;
    }
    if (enable) {
        for (i = 0; i < DAT_00560850[0]; i++) {
            if (DAT_00560858[0][i] < 0) {
                light->slot = i;
                DAT_00560858[0][i] = (int)light;
                light->enabled = 1;
                igPsx2VisualContext_CommitLight(this, light);
                p2EnableLight(i);
                return 1;
            }
        }
        return 0;
    }
    p2DisableLight(light->slot);
    light->enabled = 0;
    DAT_00560858[0][light->slot] = -1;
    return 1;
}

bool igPsx2VisualContext::getLightState(int lightHandle) const {
    p2Light *light = lightAt(this, lightHandle);
    return light->enabled;
}

IG_GFX_LIGHT_TYPE igPsx2VisualContext::getLightType(int handle) const {
    p2Light *light = lightAt(this, handle);
    return (IG_GFX_LIGHT_TYPE)light->lightType;
}

void igPsx2VisualContext::setLightDiffuse(int handle, const igVec4f &d) {
    p2Light *light = lightAt(this, handle);
    if (light != 0) {
        if (colorEqual(light->diffuse, d.vec)) {
            DAT_005608d0[0] += 1;
        }
        light->diffuse[0] = d[0];
        light->diffuse[1] = d[1];
        light->diffuse[2] = d[2];
        light->diffuse[3] = d[3];
        igPsx2VisualContext_CommitLight(this, light);
    }
}

void igPsx2VisualContext::setLightSpecular(int handle, const igVec4f &s) {
    p2Light *light = lightAt(this, handle);
    unsigned int oldFlags;
    unsigned int newFlags;
    if (light != 0) {
        if (colorEqual(light->specular, s.vec)) {
            DAT_005608d4[0] += 1;
        }
        light->specular[0] = s[0];
        light->specular[1] = s[1];
        light->specular[2] = s[2];
        light->specular[3] = s[3];
        oldFlags = light->flags;
        if (s[0] != 0.0f || s[1] != 0.0f || s[2] != 0.0f) {
            light->flags = light->flags | P2_LIGHT_SPECULAR;
        } else {
            light->flags = oldFlags & ~P2_LIGHT_SPECULAR;
        }
        newFlags = light->flags;
        if (oldFlags != newFlags) {
            light->flags = newFlags | P2_LIGHT_CHANGED;
        }
        igPsx2VisualContext_CommitLight(this, light);
    }
}

void igPsx2VisualContext::setLightAmbient(int handle, const igVec4f &a) {
    p2Light *light = lightAt(this, handle);
    unsigned int oldFlags;
    if (light != 0) {
        if (colorEqual(light->ambient, a.vec)) {
            DAT_005609c8[0] = DAT_005609c8[0] + 1;
        }
        light->ambient[0] = a[0];
        light->ambient[1] = a[1];
        light->ambient[2] = a[2];
        light->ambient[3] = a[3];
        oldFlags = light->flags;
        if (a[0] != 0.0f || a[1] != 0.0f || a[2] != 0.0f) {
            light->flags = light->flags | P2_LIGHT_AMBIENT;
        } else {
            light->flags = oldFlags & ~P2_LIGHT_AMBIENT;
        }
        if (oldFlags != light->flags) {
            light->flags = light->flags | P2_LIGHT_CHANGED;
        }
        igPsx2VisualContext_CommitLight(this, light);
    }
}

void igPsx2VisualContext::setLightPosition(int handle, const igVec3f &p) {
    float modelView[16];
    p2Light *light = lightAt(this, handle);
    if (light != 0) {
        int same = 1;
        if (light->position[0] != p[0]) same = 0;
        if (same != 0) { same = 1; if (light->position[1] != p[1]) same = 0; }
        if (same != 0) { same = 1; if (light->position[2] != p[2]) same = 0; }
        if (same != 0) DAT_005608dc[0] += 1;
        light->position[0] = p[0];
        light->position[1] = p[1];
        light->position[2] = p[2];
        if (light->lightType != IG_GFX_LIGHT_TYPE_DIRECTIONAL) {
            /* matching construct: igMatrix44f's constructor would write the identity first; retail leaves the slot raw */
            getMatrix(IG_GFX_MATRIX_STACK_MODELVIEW, *(igMatrix44f *)modelView);
            Vec3f_TransformProjective(light->eyePosition, p.vec, modelView);
        }
        igPsx2VisualContext_CommitLight(this, light);
    }
}

void igPsx2VisualContext::setLightCutoffAngle(int handle, float c) {
    p2Light *light = lightAt(this, handle);
    unsigned int oldFlags;

    if (light != 0) {
        oldFlags = light->flags;
        if (light->cutoffAngle == c) {
            DAT_005608e4[0] += 1;
        }
        light->cutoffAngle = c;
        if (light->lightType == IG_GFX_LIGHT_TYPE_SPOT && c != 180.0f) {
            light->flags = light->flags | P2_LIGHT_SPOT_CONE;
        } else {
            light->flags = light->flags & ~P2_LIGHT_SPOT_CONE;
        }
        if (oldFlags != light->flags) {
            light->flags = light->flags | P2_LIGHT_CHANGED;
        }
        igPsx2VisualContext_CommitLight(this, light);
    }
}

void igPsx2VisualContext::setLightFalloffRate(int handle, float e) {
    float scaled;
    p2Light *light;

    light = lightAt(this, handle);
    if (light != 0) {
        scaled = 128.0f * e;
        if (light->falloff == scaled) {
            DAT_005608e8[0] += 1;
        }
        light->falloff = scaled;
        igPsx2VisualContext_CommitLight(this, light);
    }
}

void igPsx2VisualContext::getLightDiffuse(int handle, igVec4f &d) const {
    const p2Light *light = lightAt(this, handle);
    d.vec[0] = light->diffuse[0];
    d.vec[1] = light->diffuse[1];
    d.vec[2] = light->diffuse[2];
    d.vec[3] = light->diffuse[3];
}

void igPsx2VisualContext::getLightAmbient(int handle, igVec4f &a) const {
    const p2Light *light = lightAt(this, handle);
    a.vec[0] = light->ambient[0];
    a.vec[1] = light->ambient[1];
    a.vec[2] = light->ambient[2];
    a.vec[3] = light->ambient[3];
}

void igPsx2VisualContext::getLightSpecular(int handle, igVec4f &s) const {
    const p2Light *light = lightAt(this, handle);
    s[0] = light->specular[0];
    s[1] = light->specular[1];
    s[2] = light->specular[2];
    s[3] = light->specular[3];
}

void igPsx2VisualContext::getLightPosition(int handle, igVec3f &p) const {
    const p2Light *light = lightAt(this, handle);
    p[0] = light->position[0];
    p[1] = light->position[1];
    p[2] = light->position[2];
}

void igPsx2VisualContext::getLightDirection(int handle, igVec3f &d) const {
    const p2Light *light = lightAt(this, handle);
    d[0] = light->localDirection[0];
    d[1] = light->localDirection[1];
    d[2] = light->localDirection[2];
}

float igPsx2VisualContext::getLightFalloffRate(int handle) const {
    return 0.0f;
}

void igPsx2VisualContext::getLightAttenuation(int handle, igVec3f &a) const {
    const p2Light *light = lightAt(this, handle);
    float x, y, z;
    z = light->attenuation[2];
    y = light->attenuation[1];
    x = light->attenuation[0];
    a.vec[0] = x;
    a.vec[1] = y;
    a.vec[2] = z;
}

float igPsx2VisualContext::getLightCutoffAngle(int handle) const {
    p2Light *light = lightAt(this, handle);
    return light->cutoffAngle;
}
}
}

void igPsx2VisualContext_CommitLight(Gap::Gfx::igPsx2VisualContext *vc, p2Light *light) {
    if (light->enabled != 0) {
        p2SetLight(light->slot, light);
    }
}

void igPsx2VisualContext_ResetMaterial(p2Material *material) {
    material->diffuse[0] = g_vec4Zero[0];
    material->diffuse[1] = g_vec4Zero[1];
    material->diffuse[2] = g_vec4Zero[2];
    material->diffuse[3] = g_vec4Zero[3];
    material->ambient[0] = g_vec4Zero[0];
    material->ambient[1] = g_vec4Zero[1];
    material->ambient[2] = g_vec4Zero[2];
    material->ambient[3] = g_vec4Zero[3];
    material->emission[0] = g_vec4Zero[0];
    material->emission[1] = g_vec4Zero[1];
    material->emission[2] = g_vec4Zero[2];
    material->emission[3] = g_vec4Zero[3];
    material->specular[0] = g_vec4Zero[0];
    material->specular[1] = g_vec4Zero[1];
    material->specular[2] = g_vec4Zero[2];
    material->specular[3] = g_vec4Zero[3];
    material->shininess = 0.0f;
    material->flags = P2_MATERIAL_CHANGED;
    material->colorMode = 0;
    material->slot = 0;
}

/* The material the context's setters edit: a record of its own, handed to p2SetMaterial. A macro for the
 * same reason as lightAt: retail loads _currentMaterial again at each use. */
#define currentMaterial(vc) ((p2Material *)(vc)->_currentMaterial)

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setMaterialDiffuse(const igVec4f &d) {
    float *cur = currentMaterial(this)->diffuse;
    p2Material *material;
    if (colorEqual(cur, d.vec)) {
        DAT_005608f8[0] += 1;
    }
    material = currentMaterial(this);
    material->diffuse[0] = d[0];
    material->diffuse[1] = d[1];
    material->diffuse[2] = d[2];
    material->diffuse[3] = d[3];
    igPsx2VisualContext_CommitMaterial(this, currentMaterial(this));
}

void igPsx2VisualContext::getMaterialDiffuse(igVec4f &d) const {
    const p2Material *material = currentMaterial(this);
    d.vec[0] = material->diffuse[0];
    d.vec[1] = material->diffuse[1];
    d.vec[2] = material->diffuse[2];
    d.vec[3] = material->diffuse[3];
}

void igPsx2VisualContext::setMaterialAmbient(const igVec4f &a) {
    p2Material *material;
    unsigned old, *f;
    bool eq;
    material = currentMaterial(this);
    /* matching construct: C++ conversion trial — the four equality tests are one bool && chain */
    eq = material->ambient[0] == a.vec[0] && material->ambient[1] == a.vec[1] && material->ambient[2] == a.vec[2] && material->ambient[3] == a.vec[3];
    if (eq) DAT_005608fc[0]++;
    material = currentMaterial(this);
    material->ambient[0] = a.vec[0]; material->ambient[1] = a.vec[1]; material->ambient[2] = a.vec[2]; material->ambient[3] = a.vec[3];
    material = currentMaterial(this);
    f = &material->flags;
    old = material->flags;
    if (a.vec[0] != 0.0f || a.vec[1] != 0.0f || a.vec[2] != 0.0f) *f |= P2_MATERIAL_AMBIENT;
    else *f = old & ~(unsigned)P2_MATERIAL_AMBIENT;
    material = currentMaterial(this);
    f = &material->flags;
    if (old != material->flags) *f = material->flags | P2_MATERIAL_CHANGED;
    igPsx2VisualContext_CommitMaterial(this, currentMaterial(this));
}

void igPsx2VisualContext::getMaterialAmbient(igVec4f &a) const {
    const p2Material *material = currentMaterial(this);
    a.vec[0] = material->ambient[0];
    a.vec[1] = material->ambient[1];
    a.vec[2] = material->ambient[2];
    a.vec[3] = material->ambient[3];
}

void igPsx2VisualContext::setMaterialEmissive(const igVec4f &e) {
    p2Material *material;

    if (colorEqual(currentMaterial(this)->emission, e.vec)) {
        DAT_00560900[0] += 1;
    }
    material = currentMaterial(this);
    material->emission[0] = e[0];
    material->emission[1] = e[1];
    material->emission[2] = e[2];
    material->emission[3] = e[3];
    igPsx2VisualContext_CommitMaterial(this, currentMaterial(this));
}

void igPsx2VisualContext::getMaterialEmissive(igVec4f &d) const {
    const p2Material *material = currentMaterial(this);
    d.vec[0] = material->emission[0];
    d.vec[1] = material->emission[1];
    d.vec[2] = material->emission[2];
    d.vec[3] = material->emission[3];
}

void igPsx2VisualContext::setMaterialSpecular(const igVec4f &s) {
    p2Material *material;
    unsigned old;
    unsigned *fp;
    float *current;
    bool same;

    material = currentMaterial(this);
    current = material->specular;
    same = current[0] == s.vec[0] && current[1] == s.vec[1] && current[2] == s.vec[2] && current[3] == s.vec[3];
    if (same) {
        DAT_00560904[0] += 1;
    }
    material = currentMaterial(this);
    material->specular[0] = s.vec[0];
    material->specular[1] = s.vec[1];
    material->specular[2] = s.vec[2];
    material->specular[3] = s.vec[3];
    material = currentMaterial(this);
    fp = &material->flags;
    old = *fp;
    if (s.vec[0] != 0.0f || s.vec[1] != 0.0f || s.vec[2] != 0.0f) {
        *fp = *fp | P2_MATERIAL_SPECULAR;
    } else {
        *fp = old & ~P2_MATERIAL_SPECULAR;
    }
    material = currentMaterial(this);
    fp = &material->flags;
    if (old != *fp) {
        *fp = *fp | P2_MATERIAL_CHANGED;
    }
    igPsx2VisualContext_CommitMaterial(this, currentMaterial(this));
}

void igPsx2VisualContext::getMaterialSpecular(igVec4f &s) const {
    const p2Material *material = currentMaterial(this);
    s.vec[0] = material->specular[0];
    s.vec[1] = material->specular[1];
    s.vec[2] = material->specular[2];
    s.vec[3] = material->specular[3];
}

void igPsx2VisualContext::setMaterialShininess(float sh) {
    if (currentMaterial(this)->shininess == sh) {
        DAT_00560908[0] += 1;
    }
    currentMaterial(this)->shininess = sh;
    igPsx2VisualContext_CommitMaterial(this, currentMaterial(this));
}

float igPsx2VisualContext::getMaterialShininess() const {
    return currentMaterial(this)->shininess;
}

void igPsx2VisualContext::setMaterial(const igVec4f &ambient, const igVec4f &diffuse, const igVec4f &specular, const igVec4f &emission, const float shininess) {
    if (colorEqual(currentMaterial(this)->diffuse, diffuse.vec)) DAT_005608f8[0] += 1;
    if (colorEqual(currentMaterial(this)->ambient, ambient.vec)) DAT_005608fc[0] += 1;
    if (colorEqual(currentMaterial(this)->emission, emission.vec)) DAT_00560900[0] += 1;
    if (colorEqual(currentMaterial(this)->specular, specular.vec)) DAT_00560904[0] += 1;
    if (currentMaterial(this)->shininess == shininess) {
        DAT_00560908[0] += 1;
    }
    { p2Material *m = currentMaterial(this); m->diffuse[0] = diffuse[0]; m->diffuse[1] = diffuse[1]; m->diffuse[2] = diffuse[2]; m->diffuse[3] = diffuse[3]; }
    { p2Material *m = currentMaterial(this); m->ambient[0] = ambient[0]; m->ambient[1] = ambient[1]; m->ambient[2] = ambient[2]; m->ambient[3] = ambient[3]; }
    { p2Material *m = currentMaterial(this); m->emission[0] = emission[0]; m->emission[1] = emission[1]; m->emission[2] = emission[2]; m->emission[3] = emission[3]; }
    { p2Material *m = currentMaterial(this); m->specular[0] = specular[0]; m->specular[1] = specular[1]; m->specular[2] = specular[2]; m->specular[3] = specular[3]; }
    currentMaterial(this)->shininess = shininess;
    {
        unsigned oldFlags = currentMaterial(this)->flags;
        if (specular[0] != 0.0f || specular[1] != 0.0f || specular[2] != 0.0f) {
            currentMaterial(this)->flags = currentMaterial(this)->flags | P2_MATERIAL_SPECULAR;
        } else {
            currentMaterial(this)->flags = oldFlags & ~P2_MATERIAL_SPECULAR;
        }
        if (ambient[0] != 0.0f || ambient[1] != 0.0f || ambient[2] != 0.0f) {
            currentMaterial(this)->flags = currentMaterial(this)->flags | P2_MATERIAL_AMBIENT;
        } else {
            currentMaterial(this)->flags = currentMaterial(this)->flags & ~P2_MATERIAL_AMBIENT;
        }
        if (oldFlags != currentMaterial(this)->flags) {
            currentMaterial(this)->flags = currentMaterial(this)->flags | P2_MATERIAL_CHANGED;
        }
    }
    igPsx2VisualContext_CommitMaterial(this, currentMaterial(this));
}
}
}

void igPsx2VisualContext_SetMaterialSlot(Gap::Gfx::igPsx2VisualContext *vc, int slot) {
    if (currentMaterial(vc)->slot == slot) {
        DAT_0056090c[0] += 1;
    }
    currentMaterial(vc)->slot = slot;
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setMaterialSpecularState(bool enable)
{
    if (_materialSpecularState == (enable & 0xFF))
        DAT_00560910 += 1;
    _materialSpecularState = enable;
    p2SetMaterialSpecularState((unsigned char)enable);
}

void igPsx2VisualContext::setMaterialColorMode(int mode) {
    if (currentMaterial(this)->colorMode == mode) {
        DAT_00560914[0] += 1;
    }
    currentMaterial(this)->colorMode = mode;
    switch (mode) {
    case 0:
        p2DisableCapability(12);
        p2SetLightingMode(0);
        return;
    case 1:
        p2EnableCapability(12);
        p2SetLightingMode(1);
        break;
    case 2:
        p2EnableCapability(12);
        p2SetLightingMode(4);
        break;
    case 3:
        p2EnableCapability(12);
        p2SetLightingMode(5);
        break;
    case 4:
        p2EnableCapability(12);
        p2SetLightingMode(3);
        break;
    case 5:
        p2EnableCapability(12);
        p2SetLightingMode(2);
        break;
    }
}

int igPsx2VisualContext::getMaterialColorMode() const {
    return currentMaterial(this)->colorMode;
}

void igPsx2VisualContext::setSceneAmbient(const igVec4f &sceneAmbient) {
    p2Material *material;
    if (colorEqual(currentMaterial(this)->color, sceneAmbient.vec)) {
        DAT_00560918[0] += 1;
    }
    material = currentMaterial(this);
    material->color[0] = sceneAmbient[0];
    material->color[1] = sceneAmbient[1];
    material->color[2] = sceneAmbient[2];
    material->color[3] = sceneAmbient[3];
    p2SetLightingColor(sceneAmbient.vec);
}

void igPsx2VisualContext::getSceneAmbient(igVec4f &sceneAmbient) const {
    const p2Material *material = currentMaterial(this);
    sceneAmbient.vec[0] = material->color[0];
    sceneAmbient.vec[1] = material->color[1];
    sceneAmbient.vec[2] = material->color[2];
    sceneAmbient.vec[3] = material->color[3];
}
}
}

void igPsx2VisualContext_CommitMaterial(Gap::Gfx::igPsx2VisualContext *vc, p2Material *material) {
    p2SetMaterial(material->slot, material);
    p2SetLightingColor(currentMaterial(vc)->color);
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setStackSize(IG_GFX_MATRIX_STACK which, int depth) {
    switch (which) {
    case 0:
        if (depth >= _projMat->_count) ((Gap::Core::igDataList *)_projMat.p)->setCapacity(depth, 64);
        break;
    case 1:
        if (depth >= _mvMat->_count) ((Gap::Core::igDataList *)_mvMat.p)->setCapacity(depth, 64);
        break;
    case 2:
        if (depth >= _texMat->_count) ((Gap::Core::igDataList *)_texMat.p)->setCapacity(depth, 64);
        break;
    case 10:
        if (depth >= _blendMat0->_count) ((Gap::Core::igDataList *)_blendMat0.p)->setCapacity(depth, 64);
        if (depth >= _invTransBlendMat0->_count) ((Gap::Core::igDataList *)_invTransBlendMat0.p)->setCapacity(depth, 64);
        break;
    case 11:
        if (depth >= _blendMat1->_count) ((Gap::Core::igDataList *)_blendMat1.p)->setCapacity(depth, 64);
        if (depth >= _invTransBlendMat1->_count) ((Gap::Core::igDataList *)_invTransBlendMat1.p)->setCapacity(depth, 64);
        break;
    case 12:
        if (depth >= _blendMat2->_count) ((Gap::Core::igDataList *)_blendMat2.p)->setCapacity(depth, 64);
        if (depth >= _invTransBlendMat2->_count) ((Gap::Core::igDataList *)_invTransBlendMat2.p)->setCapacity(depth, 64);
        break;
    case 13:
        if (depth >= _blendMat3->_count) ((Gap::Core::igDataList *)_blendMat3.p)->setCapacity(depth, 64);
        if (depth >= _invTransBlendMat3->_count) ((Gap::Core::igDataList *)_invTransBlendMat3.p)->setCapacity(depth, 64);
        break;
    }
}

int igPsx2VisualContext::getStackSize(IG_GFX_MATRIX_STACK which) const {
    switch (which) {
    case IG_GFX_MATRIX_STACK_PROJECTION: return _projMat->_capacity;
    case IG_GFX_MATRIX_STACK_MODELVIEW: return _mvMat->_capacity;
    case IG_GFX_MATRIX_STACK_TEXTURE_0: return _texMat->_capacity;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_0: return _blendMat0->_capacity;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_1: return _blendMat1->_capacity;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_2: return _blendMat2->_capacity;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_3: return _blendMat3->_capacity;
    default: return 0;
    }
}
}
}

/* A matrix stack read as the list of matrices it is (kit igUtils/igMatrixStack.h: an igTDataStack<igMatrix44f>). */
typedef igTDataList<igMatrix44f> MatrixList;

static inline const float *topMatrix(const MatrixList *stack) {
    return stack->_data[stack->_count - 1].m;
}

/* igMatrixStack::push() (kit): duplicates the top matrix. matching construct: a macro, since an inline function
 * gives its list the other callee-saved register in all seven expansions. */
#define pushTop(stackExpr) do { \
        int count; \
        MatrixList *list; \
        int top; \
        list = (stackExpr); \
        top = list->getCount(); \
        if (top != 0) { \
            count = list->_count; \
            if (count < list->_capacity) { \
                list->_count = top + 1; \
            } else { \
                ((Gap::Core::igDataList *)list)->resizeAndSetCount(count + 1, 64); \
            } \
            igMatrix44f_Copy(list->_data[count].m, list->_data[count - 1].m); \
        } \
    } while (0)

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::pushMatrix(IG_GFX_MATRIX_STACK which) {
    switch (which) {
    case IG_GFX_MATRIX_STACK_PROJECTION:
        pushTop((MatrixList *)_projMat.p);
        break;
    case IG_GFX_MATRIX_STACK_MODELVIEW:
        pushTop((MatrixList *)_mvMat.p);
        break;
    case IG_GFX_MATRIX_STACK_TEXTURE_0:
        pushTop((MatrixList *)_texMat.p);
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_0:
        pushTop((MatrixList *)_blendMat0.p);
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_1:
        pushTop((MatrixList *)_blendMat1.p);
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_2:
        pushTop((MatrixList *)_blendMat2.p);
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_3:
        pushTop((MatrixList *)_blendMat3.p);
        break;
    }
}

void igPsx2VisualContext::popMatrix(IG_GFX_MATRIX_STACK which) {
    /* matching construct: each pop copies the matrix it discards into a local of its own */
    float popped0[16], popped1[16], popped2[16], popped3[16], popped4[16];
    MatrixList *stack;
    switch (which) {
    case IG_GFX_MATRIX_STACK_PROJECTION:
        ((MatrixList *)_projMat.p)->_count--;
        p2SetMatrix(3, topMatrix((MatrixList *)_projMat.p));
        break;
    case IG_GFX_MATRIX_STACK_MODELVIEW:
        ((MatrixList *)_mvMat.p)->_count--;
        p2SetMatrix(0, topMatrix((MatrixList *)_mvMat.p));
        break;
    case IG_GFX_MATRIX_STACK_TEXTURE_0:
        stack = (MatrixList *)_texMat.p;
        stack->_count--;
        igMatrix44f_Copy(popped0, stack->_data[stack->_count].m);
        p2SetMatrix(4, topMatrix((MatrixList *)_texMat.p));
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_0:
        stack = (MatrixList *)_blendMat0.p;
        stack->_count--;
        igMatrix44f_Copy(popped1, stack->_data[stack->_count].m);
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_1:
        stack = (MatrixList *)_blendMat1.p;
        stack->_count--;
        igMatrix44f_Copy(popped2, stack->_data[stack->_count].m);
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_2:
        stack = (MatrixList *)_blendMat2.p;
        stack->_count--;
        igMatrix44f_Copy(popped3, stack->_data[stack->_count].m);
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_3:
        stack = (MatrixList *)_blendMat3.p;
        stack->_count--;
        igMatrix44f_Copy(popped4, stack->_data[stack->_count].m);
        break;
    }
}
}
}

/* igTDataStack::set (kit igUtils/igTDataStack.h) on the top matrix: an empty stack gains one. Two macros that
 * differ only in the order of their locals; matching construct: the register allocator follows it. */
#define setTop(stackExpr, matrix) { \
    MatrixList *list = (stackExpr); \
    int count = list->_count; \
    int next; \
    if (count == 0) { \
        next = count + 1; \
        if (count < list->_capacity) list->_count = list->getCount() + 1; \
        else ((Gap::Core::igDataList *)list)->resizeAndSetCount(next, 0x40); \
        igMatrix44f_Copy(list->_data[count].m, (const float *)(matrix)); \
    } else { \
        igMatrix44f_Copy(list->_data[list->getCount() - 1].m, (const float *)(matrix)); \
    } }
#define setTopB(stackExpr, matrix) { \
    int count; \
    MatrixList *list = (stackExpr); \
    int next; \
    count = list->_count; \
    if (count == 0) { \
        next = count + 1; \
        if (count < list->_capacity) list->_count = list->getCount() + 1; \
        else ((Gap::Core::igDataList *)list)->resizeAndSetCount(next, 0x40); \
        igMatrix44f_Copy(list->_data[count].m, (const float *)(matrix)); \
    } else { \
        igMatrix44f_Copy(list->_data[list->getCount() - 1].m, (const float *)(matrix)); \
    } }

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setMatrix(IG_GFX_MATRIX_STACK which, const igMatrix44f &mat) {
    float inverse0[16];
    float inverse1[16];
    float inverse2[16];
    float inverse3[16];
    MatrixList *t;
    switch (which) {
    case IG_GFX_MATRIX_STACK_PROJECTION:
        setTop((MatrixList *)_projMat.p, mat.m)
        t = (MatrixList *)_projMat.p;
        p2SetMatrix(3, topMatrix(t));
        break;
    case IG_GFX_MATRIX_STACK_MODELVIEW:
        setTop((MatrixList *)_mvMat.p, mat.m)
        t = (MatrixList *)_mvMat.p;
        p2SetMatrix(0, topMatrix(t));
        break;
    case IG_GFX_MATRIX_STACK_TEXTURE_0:
        setTop((MatrixList *)_texMat.p, mat.m)
        t = (MatrixList *)_texMat.p;
        p2SetMatrix(4, topMatrix(t));
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_0:
        igMatrix44f_SetIdentity(inverse0);
        setTopB((MatrixList *)_blendMat0.p, mat.m)
        igMatrix44f_Invert(inverse0, mat.m);
        FUN_001903d0(inverse0);
        setTop((MatrixList *)_invTransBlendMat0.p, inverse0)
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_1:
        igMatrix44f_SetIdentity(inverse1);
        setTopB((MatrixList *)_blendMat1.p, mat.m)
        igMatrix44f_Invert(inverse1, mat.m);
        FUN_001903d0(inverse1);
        setTop((MatrixList *)_invTransBlendMat1.p, inverse1)
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_2:
        igMatrix44f_SetIdentity(inverse2);
        setTopB((MatrixList *)_blendMat2.p, mat.m)
        igMatrix44f_Invert(inverse2, mat.m);
        FUN_001903d0(inverse2);
        setTop((MatrixList *)_invTransBlendMat2.p, inverse2)
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_3:
        igMatrix44f_SetIdentity(inverse3);
        setTopB((MatrixList *)_blendMat3.p, mat.m)
        igMatrix44f_Invert(inverse3, mat.m);
        FUN_001903d0(inverse3);
        setTop((MatrixList *)_invTransBlendMat3.p, inverse3)
        break;
    }
}

void igPsx2VisualContext::pushPreMultiply(IG_GFX_MATRIX_STACK which, const igMatrix44f &mat) {
    float inverse0[16];
    float inverse1[16];
    float inverse2[16];
    float inverse3[16];
    MatrixList *t;
    switch (which) {
    case IG_GFX_MATRIX_STACK_PROJECTION:
        igMatrixStack_PushPreMultiply((igMatrixStack *)_projMat, mat.m);
        t = (MatrixList *)_projMat.p;
        p2SetMatrix(3, topMatrix(t));
        break;
    case IG_GFX_MATRIX_STACK_MODELVIEW:
        igMatrixStack_PushPreMultiply((igMatrixStack *)_mvMat, mat.m);
        t = (MatrixList *)_mvMat.p;
        p2SetMatrix(0, topMatrix(t));
        break;
    case IG_GFX_MATRIX_STACK_TEXTURE_0:
        igMatrixStack_PushPreMultiply((igMatrixStack *)_texMat, mat.m);
        t = (MatrixList *)_texMat.p;
        p2SetMatrix(4, topMatrix(t));
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_0:
        igMatrix44f_SetIdentity(inverse0);
        igMatrixStack_PushPreMultiply((igMatrixStack *)_blendMat0, mat.m);
        igMatrix44f_Invert(inverse0, mat.m);
        FUN_001903d0(inverse0);
        setTop((MatrixList *)_invTransBlendMat0.p, inverse0)
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_1:
        igMatrix44f_SetIdentity(inverse1);
        igMatrixStack_PushPreMultiply((igMatrixStack *)_blendMat1, mat.m);
        igMatrix44f_Invert(inverse1, mat.m);
        FUN_001903d0(inverse1);
        setTop((MatrixList *)_invTransBlendMat1.p, inverse1)
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_2:
        igMatrix44f_SetIdentity(inverse2);
        igMatrixStack_PushPreMultiply((igMatrixStack *)_blendMat2, mat.m);
        igMatrix44f_Invert(inverse2, mat.m);
        FUN_001903d0(inverse2);
        setTop((MatrixList *)_invTransBlendMat2.p, inverse2)
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_3:
        igMatrix44f_SetIdentity(inverse3);
        igMatrixStack_PushPreMultiply((igMatrixStack *)_blendMat3, mat.m);
        igMatrix44f_Invert(inverse3, mat.m);
        FUN_001903d0(inverse3);
        setTop((MatrixList *)_invTransBlendMat3.p, inverse3)
        break;
    }
}

void igPsx2VisualContext::pushPostMultiply(IG_GFX_MATRIX_STACK which, const igMatrix44f &mat) {
    float inverse0[16];
    float inverse1[16];
    float inverse2[16];
    float inverse3[16];
    MatrixList *t;
    switch (which) {
    case IG_GFX_MATRIX_STACK_PROJECTION:
        igMatrixStack_PushPostMultiply((igMatrixStack *)_projMat, mat.m);
        t = (MatrixList *)_projMat.p;
        p2SetMatrix(3, topMatrix(t));
        break;
    case IG_GFX_MATRIX_STACK_MODELVIEW:
        igMatrixStack_PushPostMultiply((igMatrixStack *)_mvMat, mat.m);
        t = (MatrixList *)_mvMat.p;
        p2SetMatrix(0, topMatrix(t));
        break;
    case IG_GFX_MATRIX_STACK_TEXTURE_0:
        igMatrixStack_PushPostMultiply((igMatrixStack *)_texMat, mat.m);
        t = (MatrixList *)_texMat.p;
        p2SetMatrix(4, topMatrix(t));
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_0:
        igMatrix44f_SetIdentity(inverse0);
        igMatrixStack_PushPostMultiply((igMatrixStack *)_blendMat0, mat.m);
        igMatrix44f_Invert(inverse0, mat.m);
        FUN_001903d0(inverse0);
        setTop((MatrixList *)_invTransBlendMat0.p, inverse0)
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_1:
        igMatrix44f_SetIdentity(inverse1);
        igMatrixStack_PushPostMultiply((igMatrixStack *)_blendMat1, mat.m);
        igMatrix44f_Invert(inverse1, mat.m);
        FUN_001903d0(inverse1);
        setTop((MatrixList *)_invTransBlendMat1.p, inverse1)
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_2:
        igMatrix44f_SetIdentity(inverse2);
        igMatrixStack_PushPostMultiply((igMatrixStack *)_blendMat2, mat.m);
        igMatrix44f_Invert(inverse2, mat.m);
        FUN_001903d0(inverse2);
        setTop((MatrixList *)_invTransBlendMat2.p, inverse2)
        break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_3:
        igMatrix44f_SetIdentity(inverse3);
        igMatrixStack_PushPostMultiply((igMatrixStack *)_blendMat3, mat.m);
        igMatrix44f_Invert(inverse3, mat.m);
        FUN_001903d0(inverse3);
        setTop((MatrixList *)_invTransBlendMat3.p, inverse3)
        break;
    }
}
}
}

/* The matrix on top of a matrix stack, which a multiply hands back to the context's setMatrix. */
static inline igMatrix44f &stackTop(igMatrixStack *stack) {
    return ((MatrixList *)stack)->_data[stack->_count - 1];
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::preMultiply(IG_GFX_MATRIX_STACK which, const igMatrix44f &mat) {
    switch (which) {
    case 0:
        igMatrixStack_PreMultiply((igMatrixStack *)_projMat, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_projMat));
        break;
    case 1:
        igMatrixStack_PreMultiply((igMatrixStack *)_mvMat, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_mvMat));
        break;
    case 2:
        igMatrixStack_PreMultiply((igMatrixStack *)_texMat, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_texMat));
        break;
    case 10:
        igMatrixStack_PreMultiply((igMatrixStack *)_blendMat0, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_blendMat0));
        break;
    case 11:
        igMatrixStack_PreMultiply((igMatrixStack *)_blendMat1, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_blendMat1));
        break;
    case 12:
        igMatrixStack_PreMultiply((igMatrixStack *)_blendMat2, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_blendMat2));
        break;
    case 13:
        igMatrixStack_PreMultiply((igMatrixStack *)_blendMat3, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_blendMat3));
        break;
    }
}

void igPsx2VisualContext::postMultiply(IG_GFX_MATRIX_STACK which, const igMatrix44f &mat) {
    switch (which) {
    case 0:
        igMatrixStack_PostMultiply((igMatrixStack *)_projMat, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_projMat));
        break;
    case 1:
        igMatrixStack_PostMultiply((igMatrixStack *)_mvMat, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_mvMat));
        break;
    case 2:
        igMatrixStack_PostMultiply((igMatrixStack *)_texMat, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_texMat));
        break;
    case 10:
        igMatrixStack_PostMultiply((igMatrixStack *)_blendMat0, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_blendMat0));
        break;
    case 11:
        igMatrixStack_PostMultiply((igMatrixStack *)_blendMat1, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_blendMat1));
        break;
    case 12:
        igMatrixStack_PostMultiply((igMatrixStack *)_blendMat2, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_blendMat2));
        break;
    case 13:
        igMatrixStack_PostMultiply((igMatrixStack *)_blendMat3, mat.m);
        ((Gap::Gfx::igVisualContext *)this)->setMatrix(which, stackTop((igMatrixStack *)_blendMat3));
        break;
    }
}

void igPsx2VisualContext::getMatrix(IG_GFX_MATRIX_STACK which, igMatrix44f &mat) const {
    MatrixList *s;
    switch (which) {
    case IG_GFX_MATRIX_STACK_PROJECTION:  s = (MatrixList *)_projMat.p; igMatrix44f_Copy(mat.m, s->_data[s->_count - 1].m); break;
    case IG_GFX_MATRIX_STACK_MODELVIEW:  s = (MatrixList *)_mvMat.p; igMatrix44f_Copy(mat.m, s->_data[s->_count - 1].m); break;
    case IG_GFX_MATRIX_STACK_TEXTURE_0:  s = (MatrixList *)_texMat.p; igMatrix44f_Copy(mat.m, s->_data[s->_count - 1].m); break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_0: s = (MatrixList *)_blendMat0.p; igMatrix44f_Copy(mat.m, s->_data[s->_count - 1].m); break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_1: s = (MatrixList *)_blendMat1.p; igMatrix44f_Copy(mat.m, s->_data[s->_count - 1].m); break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_2: s = (MatrixList *)_blendMat2.p; igMatrix44f_Copy(mat.m, s->_data[s->_count - 1].m); break;
    case IG_GFX_MATRIX_STACK_VERTEX_BLEND_3: s = (MatrixList *)_blendMat3.p; igMatrix44f_Copy(mat.m, s->_data[s->_count - 1].m); break;
    }
}

void igPsx2VisualContext::setMatrixPsx2(int stack, const float *matrix) {
    igTDataList<igMatrix44f> *texGen;
    int n;
    switch (stack) {
    case 14:
        texGen = (igTDataList<igMatrix44f> *)_texgenMat.p;
        n = texGen->getCount();
        if (n == 0) {
            if (n < texGen->_capacity) texGen->_count = texGen->_count + 1;
            else ((Gap::Core::igDataList *)texGen)->resizeAndSetCount(n + 1, 64);
            igMatrix44f_Copy(texGen->_data[n].m, matrix);
        } else {
            igMatrix44f_Copy(texGen->_data[texGen->_count - 1].m, matrix);
        }
        texGen = (igTDataList<igMatrix44f> *)_texgenMat.p;
        p2SetMatrix(5, texGen->_data[texGen->_count - 1].m);
        break;
    default:
        setMatrix((IG_GFX_MATRIX_STACK)stack, *(const igMatrix44f *)matrix);
        break;
    }
}

void igPsx2VisualContext::getMatrixPsx2(int stack, float *matrix) {
    igTDataList<igMatrix44f> *texGen;
    switch (stack) {
    case 14:
        texGen = (igTDataList<igMatrix44f> *)_texgenMat.p;
        igMatrix44f_Copy(matrix, texGen->_data[texGen->_count - 1].m);
        break;
    default:
        getMatrix((IG_GFX_MATRIX_STACK)stack, *(igMatrix44f *)matrix);
        break;
    }
}

void igPsx2VisualContext::setTextureMatrixState(int stage, bool enable) {
    if (_textureMatrixState == enable) {
        DAT_0056091c[0] += 1;
    }
    _textureMatrixState = enable;
    if (enable) {
        p2EnableCapability(0xD);
        return;
    }
    p2DisableCapability(0xD);
}
}
}

void FUN_00174090(Gap::Gfx::igPsx2VisualContext *vc) {
    vc->setStackSize(IG_GFX_MATRIX_STACK_PROJECTION, 4);
    vc->setStackSize(IG_GFX_MATRIX_STACK_MODELVIEW, 4);
    vc->setStackSize(IG_GFX_MATRIX_STACK_TEXTURE_0, 4);
    vc->setViewport(0, 0, vc->_iDisplayWidth, vc->_iDisplayHeight, 0.0f, 1.0f);
    vc->resetToDefault(-1);
    vc->setMatrixOptimizationState(1);
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::resetToDefault(int which) {
    float m[16];
    float colorScale[4];
    igContextExt *decalExt;
    igVisualContext::resetToDefault(which);
    if (which & 4) {
        FUN_0017c880((::igPsx2VisualContext *)this, getTextureStageFunc(0), 1);
    }
    if (which & 0x40) {
        decalExt = getExt("igDecalExt");
        if (decalExt != 0) {
            ((igDecalExtDispatchView *)decalExt)->setDecalOffset(0);
        }
    }
    if (which & 2) {
        igPsx2VisualContext_SetMaterialSlot(this, 0);
    }
    if (which & 0x20) {
        igPsx2VisualContext_SetRenderSides(this, 2);
    }
    igMatrix44f_SetIdentity(m);
    igMatrix44f_SetIdentity(m);
    setMatrixPsx2(14, m);
    FUN_0016cc50(this, 0);
    colorScale[3] = 1.0f;
    colorScale[0] = 0.501960754f;
    colorScale[1] = 0.501960754f;
    colorScale[2] = 0.501960754f;
    igPsx2VisualContext_SetColorScalerValue(this, colorScale);
    igPsx2VisualContext_SetColorScalerState(this, 1);
    igPsx2VisualContext_SetColorClampState(this, 1);
    FUN_001757c0((::igPsx2VisualContext *)this, 0);
    p2DisableCapability(23);
    igPsx2VisualContext_SetAlphaBlendingControl(this, 0);
    igPsx2VisualContext_SetAlphaBlendingCorrection(this, 0);
    setTextureMatrixProjectiveState(0, 0);
    igPsx2VisualContext_SetDitherMatrix(this, 0x71603524 | (0x40712635LL << 32));
    FUN_00174950(this, 0);
    FUN_00169be0(this, 1);
    endDraw();
}

void igPsx2VisualContext::setNormalizeNormalsState(bool bEnable) {
    int state;

    state = bEnable & 0xFF;
    if (_bNormalizeNormalsState == state) {
        DAT_00560920[0] += 1;
    }
    _bNormalizeNormalsState = bEnable;
    if (state == 1) {
        p2EnableCapability(0x12);
        return;
    }
    p2DisableCapability(0x12);
}

bool igPsx2VisualContext::getNormalizeNormalsState() const {
    return _bNormalizeNormalsState;
}

void igPsx2VisualContext::setVertexBlendingState(bool enable) {
    if (g_igPsx2DisableExt_ext6Enabled != 0) {
        enable = false;
    }
    if (_bVertexBlendingEnabled == enable) {
        DAT_005608a8[0] += 1;
    }
    _bVertexBlendingEnabled = enable;
}

bool igPsx2VisualContext::getVertexBlendingState() const {
    return _bVertexBlendingEnabled;
}

void igPsx2VisualContext::setBlendingState(bool enable) {
    if (g_igPsx2DisableExt_ext2Enabled != 0) {
        enable = 0;
    }
    if (_bBlendingEnabled == (enable & 0xFF)) {
        DAT_00560924[0] += 1;
    }
    _bBlendingEnabled = enable;
    if (_bBlendingEnabled != 0) {
        p2EnableCapability(2);
        return;
    }
    p2DisableCapability(2);
}

bool igPsx2VisualContext::getBlendingState() const {
    return _bBlendingEnabled;
}

void igPsx2VisualContext::setBlendingSource(IG_GFX_BLENDING_FUNCTION srcMode) {
    if (_blendSrcMode[0] == srcMode) {
        DAT_00560928[0] += 1;
    }
    _blendSrcMode[0] = srcMode;
    igPsx2VisualContext_ApplyBlendEquation(this, 0);
}

void igPsx2VisualContext::setBlendingDestination(IG_GFX_BLENDING_FUNCTION destMode) {
    if (_blendDestMode[0] == destMode) {
        DAT_00560968[0] += 1;
    }
    _blendDestMode[0] = destMode;
    igPsx2VisualContext_ApplyBlendEquation(this, 0);
}

IG_GFX_BLENDING_FUNCTION igPsx2VisualContext::getBlendingSource() const {
    return _blendSrcMode[0];
}

IG_GFX_BLENDING_FUNCTION igPsx2VisualContext::getBlendingDestination() const {
    return _blendDestMode[0];
}

void igPsx2VisualContext::setBlendingSourceDestination(IG_GFX_BLENDING_FUNCTION srcMode, IG_GFX_BLENDING_FUNCTION destMode) {
    if (_blendSrcMode[0] == srcMode) {
        DAT_00560928[0] += 1;
    }
    if (_blendDestMode[0] == destMode) {
        DAT_00560968[0] += 1;
    }
    _blendSrcMode[0] = srcMode;
    _blendDestMode[0] = destMode;
    igPsx2VisualContext_ApplyBlendEquation(this, 0);
}
}
}

void FUN_00174510(igPsx2VisualContext *self, IG_GFX_BLENDING_FUNCTION source, IG_GFX_BLENDING_FUNCTION destination, unsigned char blendConstant, int stage) {
    int n;
    int j;
    if (stage < 15) {
        n = stage;
    } else {
        n = 15;
    }
    if (n < 8) {
        if (self->_blendSrcMode[n] == source) {
            DAT_00560928[n] += 1;
        }
        if (self->_blendDestMode[n] == destination) {
            DAT_00560968[n] += 1;
        }
        if (self->_blendConst[n] == (blendConstant & 0xFF)) {
            DAT_00560948[n] += 1;
        }
    }
    self->_blendSrcMode[n] = source;
    self->_blendDestMode[n] = destination;
    self->_blendConst[n] = blendConstant & 0xFF;
    if (n > 1) {
        j = n - 1;
    } else {
        j = 0;
    }
    p2CurrentProgram = n;
    p2CurrentGsRegisters = p2GsRegisterSets + j;
    igPsx2VisualContext_ApplyBlendEquation((Gap::Gfx::igPsx2VisualContext *)self, n);
    p2CurrentProgram = 0;
    p2CurrentGsRegisters = p2GsRegisterSets;
}

/* Sets the GS blend equation of a stage from the stage's blend functions and constant. */
void igPsx2VisualContext_ApplyBlendEquation(Gap::Gfx::igPsx2VisualContext *vc, int stage) {
    Psx2BlendEquation *table;
    int a = 2, b = 2, c = 2, d = 0, fix = -1;
    Psx2BlendEquation *equation;

    table = DAT_0048ac00[vc->_blendSrcMode[stage]];
    if (table != 0) {
        equation = table + vc->_blendDestMode[stage];
        fix = equation->fix;
        a = equation->a;
        b = equation->b;
        c = equation->c;
        d = equation->d;
        if (fix == -2) {
            fix = vc->_blendConst[stage];
        }
    }
    if (fix == -1) {
        a = 2;
        d = 0;
        b = 2;
        c = 2;
        fix = 0x80;
    }
    p2SetBlendEquation(a, b, c, d, fix);
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setAlphaTestState(bool enb)
{
    if (g_igPsx2DisableExt_ext7Enabled != 0)
        enb = 0;
    if (_alphaEnable == enb)
        DAT_0056098c += 1;
    _alphaEnable = enb;
    if (enb) {
        p2EnableCapability(3);
        FUN_001747f0(this);
    } else {
        p2DisableCapability(3);
    }
}

bool igPsx2VisualContext::getAlphaTestState() const {
    return _alphaEnable;
}

void igPsx2VisualContext::setAlphaFunc(IG_GFX_ALPHA_FUNCTION afunc) {
    if (_alphaFunc == afunc) {
        DAT_00560998[0] += 1;
    }
    _alphaFunc = afunc;
    FUN_001747f0(this);
}

IG_GFX_ALPHA_FUNCTION igPsx2VisualContext::getAlphaFunc() const {
    return _alphaFunc;
}

void igPsx2VisualContext::setAlphaRefValue(float val) {
    if (_alphaVal == val) {
        DAT_0056099c[0] += 1;
    }
    _alphaVal = val;
    FUN_001747f0(this);
}

float igPsx2VisualContext::getAlphaRefValue() const {
    return _alphaVal;
}
}
}

void FUN_001747f0(Gap::Gfx::igPsx2VisualContext *vc) {
    if (vc->_alphaEnable == 1) {
        int reference = (int)(128.0f * (float)vc->_alphaVal);
        p2SetAlphaTest(DAT_0048a500[vc->_alphaFunc], reference, 0);
    }
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setMatrixOptimizationState(bool enable) {
    int state;
    if (g_igPsx2DisableExt_ext11Enabled != 0) {
        enable = 0;
    }
    state = enable & 0xFF;
    if (_matrixOptimizationEnable == state) {
        DAT_005609a0[0] += 1;
    }
    _matrixOptimizationEnable = enable;
    if (state == 1) {
        p2DisableCapability(0x13);
        return;
    }
    p2EnableCapability(0x13);
}

bool igPsx2VisualContext::getMatrixOptimizationState()
{
    return _matrixOptimizationEnable;
}

void igPsx2VisualContext::setViewportClippingState(bool enable) {
    if (g_igPsx2DisableExt_ext8Enabled != 0) enable = 0;
    if (_clippingEnable == enable) DAT_005608b8[0] += 1;
    _clippingEnable = enable;
    if (enable == 1) p2EnableCapability(6);
    else p2DisableCapability(6);
}

bool igPsx2VisualContext::getViewportClippingState() const {
    return _clippingEnable;
}
}
}

void FUN_00174950(Gap::Gfx::igPsx2VisualContext *vc, int enable) {
    if (enable == 1) {
        p2EnableCapability(0x19);
        return;
    }
    p2DisableCapability(0x19);
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setColorMask(bool r, bool g, bool b, bool a) {
    _colorMaskR = r;
    _colorMaskG = g;
    _colorMaskB = b;
    _colorMaskA = a;
    p2SetColourMask(r, g, b, a);
}

void igPsx2VisualContext::getColorMask(bool &r, bool &g, bool &b, bool &a) const {
    r = _colorMaskR;
    g = _colorMaskG;
    b = _colorMaskB;
    a = _colorMaskA;
}

void igPsx2VisualContext::setShadingMode(IG_GFX_SHADING_MODE mode) {
    if (_shadingMode == mode) {
        DAT_005608b0[0] += 1;
    }
    _shadingMode = mode;
    if (DAT_0048a530[mode] == 1) {
        p2DisableCapability(0x11);
        return;
    }
    p2EnableCapability(0x11);
}

IG_GFX_SHADING_MODE igPsx2VisualContext::getShadingMode() const {
    return _shadingMode;
}

void igPsx2VisualContext::setCullFaceState(bool enable) {

    if (g_igPsx2DisableExt_ext9Enabled != 0) {
        enable = false;
    }
    if (_cullFaceEnable == enable) {
        DAT_005609a4[0] += 1;
    }
    _cullFaceEnable = enable;
    if (enable) {
        p2EnableCapability(DAT_0048a538[_cullFaceMode]);
        return;
    }
    p2DisableCapability(DAT_0048a538[_cullFaceMode]);
}

bool igPsx2VisualContext::getCullFaceState() const {
    return _cullFaceEnable;
}

void igPsx2VisualContext::setCullFaceMode(IG_GFX_CULL_FACE_MODE m) {
    int previousMode;

    previousMode = _cullFaceMode;
    if ((previousMode != m) && (_cullFaceEnable != 0)) {
        p2DisableCapability(DAT_0048a538[previousMode]);
        p2EnableCapability(DAT_0048a538[m]);
    }
    if (_cullFaceMode == m) {
        DAT_005609a8[0] += 1;
    }
    _cullFaceMode = m;
}

IG_GFX_CULL_FACE_MODE igPsx2VisualContext::getCullFaceMode() const {
    return _cullFaceMode;
}

void igPsx2VisualContext::setDepthTestState(bool enable) {
    if (g_igPsx2DisableExt_ext5Enabled != 0) {
        enable = false;
    }
    if (_depthTestEnable == enable) {
        DAT_005609ac[0] += 1;
    }
    if (_depthTestEnable != enable) {
        _depthTestEnable = enable;
        if (enable) {
            p2EnableCapability(0);
            FUN_00174db0(this);
            return;
        }
        p2DisableCapability(0);
    }
}

bool igPsx2VisualContext::getDepthTestState() const {
    return _depthTestEnable;
}

void igPsx2VisualContext::setDepthTestFunction(int func) {
    if (_depthTestFunc == func) {
        DAT_005609b0[0] += 1;
    }
    _depthTestFunc = func;
    FUN_00174db0(this);
    if (_depthTestFunc & 4) {
        _uiClearDepth = (unsigned)(2147483648.0f * _clearDepth);
    } else {
        _uiClearDepth = (unsigned)(2147483648.0f * (1.0f - _clearDepth));
    }
}

int igPsx2VisualContext::getDepthTestFunction() const {
    return _depthTestFunc;
}

void igPsx2VisualContext::setDepthWriteState(bool enable) {
    if (_bDepthWrite == (enable & 0xFF)) {
        DAT_005609b4[0] += 1;
    }
    _bDepthWrite = enable;
    FUN_00174db0(this);
}

bool igPsx2VisualContext::getDepthWriteState() const {
    return _bDepthWrite;
}
}
}

void FUN_00174db0(Gap::Gfx::igPsx2VisualContext *vc) {
    if (vc->_bDepthWrite == 1) {
        p2SetDepthFunction(DAT_0048a540[vc->_depthTestFunc], 0);
        return;
    }
    p2SetDepthFunction(DAT_0048a540[vc->_depthTestFunc], 1);
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setStencilState(bool enable) {
    if (_stencilState == enable) {
        DAT_005609b8[0] += 1;
    }
    _stencilState = enable;
    if (enable && (_stencilFunc != 7)) {
        p2EnableCapability(4);
    } else {
        p2DisableCapability(4);
    }
}

bool igPsx2VisualContext::getStencilState() const {
    return _stencilState != 0;
}

void igPsx2VisualContext::setStencilRefVal(unsigned int stenRef) {
    if (_stencilRefVal == stenRef) {
        DAT_005609bc[0] += 1;
    }
    _stencilRefVal = stenRef;
    p2SetDestinationAlphaMode(_stencilRefVal & 1);
}

unsigned igPsx2VisualContext::getStencilRefVal() const {
    return _stencilRefVal;
}

void igPsx2VisualContext::setStencilFunc(IG_GFX_STENCIL_FUNCTION stenFunc) {
    switch (stenFunc) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        if ((_stencilState != 0) && (p2IsCapabilityEnabled(4) == 0)) {
            p2EnableCapability(4);
        }
        break;
    case 7:
        p2DisableCapability(4);
        break;
    }
    if (_stencilFunc == stenFunc) {
        DAT_005609c0[0] += 1;
    }
    _stencilFunc = stenFunc;
}

IG_GFX_STENCIL_FUNCTION igPsx2VisualContext::getStencilFunc() const {
    return _stencilFunc;
}

void igPsx2VisualContext::setStencilOps(IG_GFX_STENCIL_OPERATION sfail, IG_GFX_STENCIL_OPERATION zpass, IG_GFX_STENCIL_OPERATION zfail) {
}

void igPsx2VisualContext::getStencilOps(IG_GFX_STENCIL_OPERATION &sfail, IG_GFX_STENCIL_OPERATION &zpass, IG_GFX_STENCIL_OPERATION &zfail) const {

}

void igPsx2VisualContext::setStencilReadMask(unsigned int stenRef) {
}

unsigned igPsx2VisualContext::getStencilReadMask() const {
    return -1;
}

void igPsx2VisualContext::setStencilWriteMask(unsigned int stenRef) {
}

unsigned igPsx2VisualContext::getStencilWriteMask() const {
    return -1;
}

void igPsx2VisualContext::setRenderMode(IG_GFX_RENDER_MODE mode) {
    if (_renderMode == mode) {
        DAT_005609c4[0] += 1;
    }
    _renderMode = mode;
    if (mode == 0) {
        p2SetPolygonMode(2);
    } else if (mode == 1) {
        p2SetPolygonMode(1);
    } else if (mode == 2) {
        p2SetPolygonMode(0);
    }
}

IG_GFX_RENDER_MODE igPsx2VisualContext::getRenderMode() const {
    return _renderMode;
}
}
}

void igPsx2VisualContext_SetRenderSides(Gap::Gfx::igPsx2VisualContext *vc, int renderSides) {
    if (vc->_renderSides == renderSides) {
        DAT_005609c8[0] += 1;
    }
    vc->_renderSides = renderSides;
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setFogState(bool enable) {
    if (g_igPsx2DisableExt_ext4Enabled != 0) {
        enable = false;
    }
    if (_fogEnable == enable) {
        DAT_005609cc[0] += 1;
    }
    _fogEnable = enable;
    if (enable) {
        p2EnableCapability(7);
        return;
    }
    p2DisableCapability(7);
}

bool igPsx2VisualContext::getFogState() const {
    return _fogEnable;
}

void igPsx2VisualContext::setFogDensity(float density) {
    int mode;
    if (_fogDensity == density) {
        DAT_005609d0[0] += 1;
    }
    _fogDensity = density;
    mode = _fogMode;
    p2SetFog(DAT_0048a560[mode], mode, _fogNear, _fogFar, _fogDensity, 1.0f, 0.0f, 0.0f);
}

float igPsx2VisualContext::getFogDensity() const {
    return _fogDensity;
}

void igPsx2VisualContext::setFogMode(IG_GFX_FOG_MODE mode) {
    if (_fogMode == mode) {
        DAT_005609d4[0] += 1;
    }
    _fogMode = mode;
    p2SetFog(DAT_0048a560[_fogMode], _fogMode, _fogNear, _fogFar, _fogDensity, 1.0f, 0.0f, 0.0f);
}

IG_GFX_FOG_MODE igPsx2VisualContext::getFogMode() const {
    return _fogMode;
}

void igPsx2VisualContext::setFogColor(const igVec4f &color) {
    if (_fogColor == color) {
        DAT_005609d8[0] += 1;
    }
    _fogColor = color;
    p2SetFogColour((color)[0], (color)[1], (color)[2]);
}

void igPsx2VisualContext::getFogColor(igVec4f &color) const {
    color.vec[0] = (float) _fogColor[0];
    color.vec[1] = (float) _fogColor[1];
    color.vec[2] = (float) _fogColor[2];
    color.vec[3] = (float) _fogColor[3];
}

void igPsx2VisualContext::setFogNear(float fogNear) {
    int mode;

    if (_fogNear == fogNear) {
        DAT_005609dc[0] += 1;
    }
    _fogNear = fogNear;
    mode = _fogMode;
    p2SetFog(DAT_0048a560[mode], mode, _fogNear, _fogFar, _fogDensity, 1.0f, 0.0f, 0.0f);
}

float igPsx2VisualContext::getFogNear() const {
    return _fogNear;
}

void igPsx2VisualContext::setFogFar(float fogFar) {
    int mode;

    if (_fogFar == fogFar) {
        DAT_005609e0[0] += 1;
    }
    _fogFar = fogFar;
    mode = _fogMode;
    p2SetFog(DAT_0048a560[mode], mode, _fogNear, _fogFar, _fogDensity, 1.0f, 0.0f, 0.0f);
}

float igPsx2VisualContext::getFogFar() const {
    return _fogFar;
}

igResult igPsx2VisualContext::setVideoMode(igVideoFormat &pFormat) {
    if (_iContextOpen == 1) {
        return g_resultFailure;
    } else if (&pFormat == 0) {
        return g_resultFailure;
    } else {
        _videoMode._bFullScreen = pFormat._bFullScreen;
        _videoMode._bInterlaced = pFormat._bInterlaced;
        _videoMode._iFieldCount = pFormat._iFieldCount;
        _videoMode._iFieldSize = pFormat._iFieldSize;
        _videoMode._fRefreshRate = pFormat._fRefreshRate;
        _videoMode._iSwapInterval = pFormat._iSwapInterval;
        _videoMode._iVideoType = pFormat._iVideoType;
        return g_resultSuccess;
    }
}

void igPsx2VisualContext::getVideoMode(igVideoFormat &pMode) {
    igVideoFormat *videoMode = &_videoMode;
    pMode._bFullScreen = videoMode->_bFullScreen;
    pMode._bInterlaced = videoMode->_bInterlaced;
    pMode._iFieldCount = videoMode->_iFieldCount;
    pMode._iFieldSize = videoMode->_iFieldSize;
    pMode._fRefreshRate = videoMode->_fRefreshRate;
    pMode._iSwapInterval = videoMode->_iSwapInterval;
    pMode._iVideoType = videoMode->_iVideoType;
}
}
}

int igPsx2VisualContext_SetColorScalerState(Gap::Gfx::igPsx2VisualContext *vc, int state) {
    if (vc->_colorScalerState == state) {
        DAT_005609e4[0] += 1;
    }
    vc->_colorScalerState = state;
    return p2SetColorScaler(DAT_0048a520[state], vc->_colorScalerValue.vec) != 0;
}

void igPsx2VisualContext_SetColorScalerValue(Gap::Gfx::igPsx2VisualContext *vc, const float *value) {
    if (colorEqual(vc->_colorScalerValue.vec, value)) {
        DAT_005609e8[0] += 1;
    }
    vc->_colorScalerValue.vec[0] = value[0];
    vc->_colorScalerValue.vec[1] = value[1];
    vc->_colorScalerValue.vec[2] = value[2];
    vc->_colorScalerValue.vec[3] = value[3];
    p2SetColorScaler(DAT_0048a520[vc->_colorScalerState], vc->_colorScalerValue.vec);
}

void igPsx2VisualContext_SetColorClampState(Gap::Gfx::igPsx2VisualContext *vc, int state) {
    if (vc->_colorClampState == (state & 0xFF)) {
        DAT_005609ec[0] += 1;
    }
    vc->_colorClampState = state;
    if (state != 0) {
        p2SetColourClamp(1);
        return;
    }
    p2SetColourClamp(0);
}

void igPsx2VisualContext_SetAlphaBlendingControl(Gap::Gfx::igPsx2VisualContext *vc, int state) {
    if (vc->_alphaBlendingControl == (unsigned char)state) {
        DAT_005609f0[0] += 1;
    }
    vc->_alphaBlendingControl = state;
    p2SetPixelAlphaBlend(state);
}

void igPsx2VisualContext_SetAlphaBlendingCorrection(Gap::Gfx::igPsx2VisualContext *vc, int state) {
    if (vc->_alphaBlendingCorrection == (unsigned char)state) {
        DAT_005609f4[0] += 1;
    }
    vc->_alphaBlendingCorrection = state;
    p2SetFrameBufferAlpha(state);
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setPixelPipelineMode(IG_GFX_PIXEL_PIPELINE_MODE mode) {
    if (_pixelPipelineMode == mode) {
        DAT_005609f8++;
    }
    _pixelPipelineMode = mode;
    if (_bMultiPassNum > 1 && _pixelPipelineMode == 3) {
        if (p2IsCapabilityEnabled(23) == 0) {
            p2EnableCapability(23);
        }
    } else {
        if (p2IsCapabilityEnabled(23) != 0) {
            p2DisableCapability(23);
        }
    }
}

void igPsx2VisualContext::setDitherState(bool enable) {
    if (_ditherState == enable) {
        DAT_005609fc[0] += 1;
    }
    _ditherState = enable;
    if (enable) {
        p2EnableCapability(0xB);
    } else {
        p2DisableCapability(0xB);
    }
}
}
}

void igPsx2VisualContext_SetDitherMatrix(Gap::Gfx::igPsx2VisualContext *vc, long long matrix) {
    if (vc->_ditherMatrix == matrix) {
        DAT_00560a00[0] += 1;
    }
    vc->_ditherMatrix = matrix;
    p2SetDitherMatrix(matrix);
}

void FUN_001757c0(igPsx2VisualContext *vc, int passCount) {
    if (vc->_bMultiPassNum == passCount) {
        DAT_00560a04[0] += 1;
    }
    vc->_bMultiPassNum = passCount;
    p2SetPassCount(vc->_bMultiPassNum);
    if (vc->_bMultiPassNum > 1 && vc->_pixelPipelineMode == 3) {
        if (p2IsCapabilityEnabled(0x17) == 0) {
            p2EnableCapability(0x17);
        }
    } else if (p2IsCapabilityEnabled(0x17) != 0) {
        p2DisableCapability(0x17);
    }
}

