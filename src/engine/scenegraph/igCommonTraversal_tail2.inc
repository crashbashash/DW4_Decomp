namespace Gap {
namespace Sg {

long long igCommonTraversal::getTimeAsLong() {
    int top; igLongStack *stack = _timeStack.p; int n = stack->_count; top = n - 1;
    if (n == 0) {
        if (!_timeBuffered) {
            if (_userTimeState) {
                _timeLongBuf = _timeLong;
            } else {
                _timeLongBuf = ((igTimerSourceView *)DAT_005871d8[0])->getTime();
            }
            _timeBuffered = 1;
        }
        return _timeLongBuf;
    }
    return ((long long *)stack->_data)[top];
}
}
}

/* The transform source's matrix at a time (slot 21; the kit's igTransformSource::getMatrix). */
class TransformSourceMatrixView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20();
    virtual void getMatrix(float *matrix, long long time);
};
/* Alchemy's emboss bump-map shader (kit igSg/igBumpMapShader.h; the registry dump has no row for it). */
struct igBumpMapShader : public igGroup {
    igTextureBindAttr *_bumpTex;
    igTextureBindAttr *_invBumpTex;
    igTDataList<igModelViewMatrixAttr *> *_mats;
    igTDataList<igGeometry *> *_geoms;
    int _bumpTexCoordIndex;
    int _reservedTexCoordIndex;
    igTDataList<igVec3f> *_lightPositions;
    igTDataList<float> *_lightIntensities;
    unsigned char _lightMask;
    float _strength;
    unsigned char _ambient;
    float _diffuse;
    float _m[16];
    igTDataList<igLightAttr *> *_lights;
    igVec3f _diffuseMaterial;
    igImage *_bumpTexImage;
    igTextureBindAttr *_bumpTex1;
    igTextureBindAttr *_unused;
    igTextureBindAttr *_materialTex;
    igTextureCoordSourceAttr *_bumpTextureCoordSource;
    igTextureCoordSourceAttr *_shiftedTextureCoordSource;
    igBitMask *_geomHasTexture;
    igTextureBindAttr *_bumpTex2;
    igTextureBindAttr *_normalTexture;
    TransformSourceMatrixView *_ts;
};

/* igBumpMapShader's emboss pass: for each geometry, copies the bump texture coordinates into the reserved set and
 * fills the vertex colours with the ambient level, then for each enabled light (the light attrs, or the bare light
 * positions when there are none) shifts the reserved coordinates along the light's reflection in tangent space
 * and adds the diffuse colour scaled by the light's intensity. */
void FUN_001b3030(igBumpMapShader *self, igCommonTraversal *traversal) {
    int lightCount;
    int g;
    float *tangent;
    float *binormal;
    int count;
    int l;
    int i;
    Gap::Gfx::igVertexArray *vertices;
    float shift;
    float intensity;
    float d;
    float r;
    float gr;
    float b;
    float a;
    float lx;
    float ly;
    float lz;
    int at;
    int type;
    int geometryCount;
    float *viewInverse;
    igGeometry *geometry;
    int attrCount;
    igVertexArrayLock shiftLock;
    igVertexArrayLock baseLock;
    igVertexArrayLock positionLock;
    igVertexArrayLock normalLock;
    igVertexArrayLock colorLock;
    igVertexArrayLock binormalLock;
    igVertexArrayLock tangentLock;
    float model[16];
    float normalMatrix[16];
    float ambient[4];
    float sourceMatrix[16];
    igVertexArrayLock_Init(&shiftLock);
    igVertexArrayLock_Init(&baseLock);
    igVertexArrayLock_Init(&positionLock);
    igVertexArrayLock_Init(&normalLock);
    igVertexArrayLock_Init(&colorLock);
    igVertexArrayLock_Init(&binormalLock);
    igVertexArrayLock_Init(&tangentLock);
    shiftLock.setType(IG_GFX_TEXTURE_COORD, self->_bumpTexCoordIndex);
    shiftLock.componentIndex = 0;
    baseLock.setType(IG_GFX_TEXTURE_COORD, self->_reservedTexCoordIndex);
    baseLock.componentIndex = 0;
    positionLock.setType(IG_GFX_POSITION);
    positionLock.componentIndex = 0;
    normalLock.setType(IG_GFX_NORMAL);
    normalLock.componentIndex = 0;
    colorLock.setType(IG_GFX_COLOR);
    colorLock.componentIndex = 0;
    binormalLock.setType(IG_GFX_BINORMAL);
    binormalLock.componentIndex = 0;
    tangentLock.setType(IG_GFX_TANGENT);
    tangentLock.componentIndex = 0;
    viewInverse = traversal->_viewMatInv;
    geometryCount = self->_geoms->_count;
    for (g = 0; g < geometryCount; g++) {
        geometry = self->_geoms->_data[g];
        attrCount = ((igTDataList<igObject *> *)geometry->_attributes)->_count;
        r = g_vec4One[0];
        gr = g_vec4One[1];
        b = g_vec4One[2];
        a = g_vec4One[3];
        if (!((1 << (g & 31)) & ((unsigned int *)self->_geomHasTexture->_data)[(unsigned int)g >> 5])) {
            r = self->_diffuseMaterial[0];
            gr = self->_diffuseMaterial[1];
            b = self->_diffuseMaterial[2];
            a = 1.0f;
        }
        igMatrix44f_SetIdentity(model);
        igMatrix44f_SetIdentity(normalMatrix);
        igMatrix44f_Multiply(model, self->_mats->_data[g]->_m, viewInverse);
        igMatrix44f_Invert(normalMatrix, model);
        FUN_001903d0(normalMatrix);
        for (at = 0; at < attrCount; at++) {
            igGeometryAttr *attr = (igGeometryAttr *)((igTDataList<igObject *> *)geometry->_attributes)->_data[at];
            if (((Gap::Core::igObject *)attr)->isOfType(Gap::Attrs::igGeometryAttr::getClassMeta()) == 0) {
                continue;
            }
            vertices = (Gap::Gfx::igVertexArray *)attr->_vertexArray;
            count = vertices->_numVerts;
            tangentLock.count = count;
            binormalLock.count = count;
            normalLock.count = count;
            positionLock.count = count;
            colorLock.count = count;
            baseLock.count = count;
            shiftLock.count = count;
            vertices->getEditableComponent(&shiftLock, 0);
            vertices->getEditableComponent(&baseLock, 1);
            vertices->getEditableComponent(&colorLock, 1);
            vertices->getEditableComponent(&positionLock, 0);
            vertices->getEditableComponent(&normalLock, 0);
            if (!vertices->getVertexFormat().hasBinormals() || !vertices->getVertexFormat().hasTangents()) {
                return;
            }
            vertices->getEditableComponent(&binormalLock, 0);
            vertices->getEditableComponent(&tangentLock, 0);
            float ambientLevel = (float)self->_ambient / 255.0f;
            ambient[3] = 1.0f;
            ambient[0] = ambientLevel;
            ambient[1] = ambientLevel;
            ambient[2] = ambientLevel;
            unsigned int ambientColor = (unsigned int)igVec4f_PackColor(ambient, 1);
            for (int v = 0; v < count; v++) {
                float *src = (float *)(shiftLock.data + v * shiftLock.stride);
                float *dst = (float *)(baseLock.data + v * baseLock.stride);
                unsigned int *color = (unsigned int *)(colorLock.data + v * colorLock.stride);
                dst[0] = src[0];
                dst[1] = src[1];
                *color = ambientColor;
            }
            if (self->_lights->_count == 0) {
                lightCount = self->_lightPositions->_count;
            } else {
                lightCount = self->_lights->_count;
            }
            if (lightCount > 8) {
                lightCount = 8;
            }
            shift = self->_strength / (float)(int)self->_bumpTexImage->_px;
            igMatrix44f_SetIdentity(sourceMatrix);
            if (self->_ts != 0) {
                self->_ts->getMatrix(sourceMatrix, ((TimeSourceView *)traversal)->getTime());
            }
            for (l = 0; l < lightCount; l++) {
                if (FUN_001b40f0(self, l) == 0) {
                    continue;
                }
                igVec3f lightPos;
                if (self->_lights->_count == 0) {
                    type = IG_GFX_LIGHT_TYPE_POINT;
                    igVec3f &position = self->_lightPositions->_data[l];
                    lightPos[0] = position[0];
                    lightPos[1] = position[1];
                    lightPos[2] = position[2];
                } else {
                    type = self->_lights->_data[l]->_lightType;
                    if (type != IG_GFX_LIGHT_TYPE_POINT) {
                        lx = self->_lights->_data[l]->_cachedDirection[0];
                        ly = self->_lights->_data[l]->_cachedDirection[1];
                        lz = self->_lights->_data[l]->_cachedDirection[2];
                        lx = -lx;
                        ly = -ly;
                        lz = -lz;
                        float inv = 1.0f / sqrtf(lx * lx + ly * ly + lz * lz);
                        lx *= inv;
                        ly *= inv;
                        lz *= inv;
                    }
                    float *position = self->_lights->_data[l]->_cachedPosition;
                    lightPos[0] = position[0];
                    lightPos[1] = position[1];
                    lightPos[2] = position[2];
                }
                intensity = self->_lightIntensities->_data[l];
                if (self->_ts != 0) {
                    Vec3f_TransformProjective(lightPos.vec, lightPos.vec, sourceMatrix);
                } else {
                    Vec3f_TransformProjective(lightPos.vec, lightPos.vec, self->_m);
                }
                for (i = 0; i < count; i++) {
                    float *uv = (float *)(baseLock.data + i * baseLock.stride);
                    float *normalIn = (float *)(normalLock.data + i * normalLock.stride);
                    unsigned int *color = (unsigned int *)(colorLock.data + i * colorLock.stride);
                    tangent = (float *)(tangentLock.data + i * tangentLock.stride);
                    binormal = (float *)(binormalLock.data + i * binormalLock.stride);
                    float world[3];
                    igVec3f n;
                    Vec3f_TransformProjective(world, (float *)(positionLock.data + i * positionLock.stride), model);
                    Vec3f_TransformDirection(n.vec, normalIn, normalMatrix);
                    n.normalize();
                    if (type == IG_GFX_LIGHT_TYPE_POINT) {
                        lx = lightPos[0] - world[0];
                        ly = lightPos[1] - world[1];
                        lz = lightPos[2] - world[2];
                        float li = 1.0f / sqrtf(lx * lx + ly * ly + lz * lz);
                        lx *= li;
                        ly *= li;
                        lz *= li;
                    }
                    /* matching construct: manual search — the reflection's x is read through the const operator[]
                     * ahead of the dot product: a second load of n's x (y and z are shared with the dot product),
                     * which the scheduler leaves last and the delay-slot filler moves under the `d < 0` test. The
                     * same read in the reflection itself is loaded after the test, and the y product goes first. */
                    float nx = ((const igVec3f &)n)[0];
                    d = lx * n[0] + ly * n[1] + lz * n[2];
                    if (d < 0.0f) {
                        continue;
                    }
                    float rx = lx - d * nx;
                    float ry = ly - d * n[1];
                    float rz = lz - d * n[2];
                    float du;
                    float dv;
                    if (d < 0.5f) {
                        float k = 2.0f * d * shift;
                        du = k * (rx * tangent[0] + ry * tangent[1] + rz * tangent[2]);
                        dv = k * (rx * binormal[0] + ry * binormal[1] + rz * binormal[2]);
                    } else {
                        du = shift * (rx * tangent[0] + ry * tangent[1] + rz * tangent[2]);
                        dv = shift * (rx * binormal[0] + ry * binormal[1] + rz * binormal[2]);
                    }
                    uv[0] = uv[0] + du;
                    uv[1] = uv[1] + dv;
                    igVec4f c;
                    Color4f_Unpack(&c, 1, *color);
                    float w = d * intensity;
                    c += igVec4f(r, gr, b, a) * w;
                    c.makeMin(g_vec4One);
                    *color = (unsigned int)igVec4f_PackColor(c.vec, 1);
                }
            }
            vertices->commitComponentEdits(shiftLock, 1);
            vertices->commitComponentEdits(baseLock, 0);
            vertices->commitComponentEdits(positionLock, 1);
            vertices->commitComponentEdits(normalLock, 1);
            vertices->commitComponentEdits(colorLock, 0);
            vertices->commitComponentEdits(binormalLock, 1);
            vertices->commitComponentEdits(tangentLock, 1);
        }
    }
}


int FUN_001b3ad0(igCommonTraversal *arg0, int arg1) {
    igAttrStackManager *p;
    igMetaObject *mo;
    igAttrStack *a0;
    igAttrStack *l;
    int a2;
    int km;
    int k;
    unsigned s2;
    bool flag;
    igBitMask *b;
    igBitMask *b2;
    unsigned idx;
    int n;
    unsigned *d;
    unsigned w;
    unsigned idx2;
    unsigned w2;

    p = (igAttrStackManager *)arg0->_attrStack;
    a0 = ((igAttrStack **)((igAttrStackList *)p->_attrStacks)->_data)[((int *)p->_attrStackIndexTable)[Gap::Attrs::igModelViewMatrixAttr::getClassMeta()->_id]];
    k = a0->_count;
    km = k - 1;
    if (k == 0) {
        a2 = 0;
    } else {
        a2 = ((int *)a0->_data)[km];
    }
    ((H_1b2fa0 *)DAT_005625f0)->vX(arg1, a2);
    mo = Gap::Attrs::igTextureBindAttr::getClassTypeSafe();
    p = (igAttrStackManager *)arg0->_attrStack;
    l = ((igAttrStack **)((igAttrStackList *)p->_attrStacks)->_data)[((int *)p->_attrStackIndexTable)[mo->_id]];
    if (l != 0) {
        flag = !(l->_count == 0);
    } else {
        flag = 0;
    }
    b = ((H_1b2fa0 *)DAT_005625f0)->f184;
    s2 = b->_bitCount;
    ((Gap::Core::igBitMask *)b)->setBitCount(s2 + 1);
    b2 = ((H_1b2fa0 *)DAT_005625f0)->f184;
    if (flag) {
        idx = s2 >> 5;
        w = ((unsigned *)b2->_data)[idx] | (1 << (s2 & 31));
        if (b2->_count != 0 && (int)idx >= 0 && (int)idx < b2->_count) {
            ((unsigned *)b2->_data)[idx] = w;
        }
    } else {
        idx2 = s2 >> 5;
        w2 = ((unsigned *)b2->_data)[idx2] & ~(1 << (s2 & 31));
        if (b2->_count != 0 && (int)idx2 >= 0 && (int)idx2 < b2->_count) {
            ((unsigned *)b2->_data)[idx2] = w2;
        }
    }
    FUN_001c5660((Z_1c5660 *)arg1, 4, 1);
    return 0;
}

void FUN_001b3c90(A0 *arg0, A1 *arg1) {
    int temp_a0;
    int temp_s0;

    FUN_001b3030((igBumpMapShader *)arg0, (igCommonTraversal *)arg1);
    temp_a0 = arg0->f160;
    ((Gap::Gfx::igImage *)temp_a0)->convert(IG_GFX_TEXTURE_FORMAT_A_8, (Gap::Gfx::igImage *)temp_a0);
    temp_s0 = arg1->f52;
    FUN_001dc500((A_1dc500 *)arg1->f68, 0, 0);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625e0[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625e8[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625b8[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625c8[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625c0[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625d0[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)arg0->f176);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)arg0->f32);
    igTraversal_TraverseChildren((igTraversal *)arg1, (igNode *)arg0);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)arg0->f32);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)arg0->f176);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625d0[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625c0[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625c8[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625b8[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_00562598[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625d0[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625c8[0]);
    igTraversal_TraverseChildren((igTraversal *)arg1, (igNode *)arg0);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625c8[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625d0[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_00562598[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625b0[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625c8[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625c0[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625d0[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)arg0->f180);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)arg0->f32);
    igTraversal_TraverseChildren((igTraversal *)arg1, (igNode *)arg0);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)arg0->f32);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)arg0->f180);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625d0[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625c0[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625c8[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625b0[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625a8[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625d0[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625c8[0]);
    igTraversal_TraverseChildren((igTraversal *)arg1, (igNode *)arg0);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625c8[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625d0[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625a8[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625d8[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625c8[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005625a0[0]);
    igTraversal_TraverseChildren((igTraversal *)arg1, (igNode *)arg0);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625a0[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625c8[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625d8[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625e8[0]);
    ((Gap::Sg::igAttrStackManager *)temp_s0)->popOverride((Gap::Attrs::igAttr *)DAT_005625e0[0]);
    FUN_001dc610((igSorter *)arg1->f68);
}

void FUN_001b3ff0(void *arg0, int arg1) {
    void **temp_a0;
    void **temp_a0_2;

    if (FUN_001b4130((struct O4130 *)arg0) == 0) {
        igTraversal_TraverseChildren((igTraversal *)arg1, (igNode *)arg0);
        return;
    }
    FUN_001b4220((struct A4220 *)arg0, (struct B4220 *)arg1);
    FUN_001b42c0((TravFlattenView *)arg0, arg1);
    temp_a0 = (void **)(*(int *)((char *)(arg0) + 176));
    ((DW4VC_132_1 *)(temp_a0))->vX((int)(*(int *)((char *)(arg0) + 48)));
    temp_a0_2 = (void **)(*(int *)((char *)(arg0) + 180));
    ((DW4VC_132_1 *)(temp_a0_2))->vX((int)(*(int *)((char *)(arg0) + 52)));
    FUN_001b3c90((A0 *)arg0, (A1 *)arg1);
}

void FUN_001b4090(T_1b2fa0 *arg0, int arg1, bool arg2) {
    if (arg1 < 8) {
        if (arg2) {
            arg0->flags |= (1 << arg1);
        } else {
            arg0->flags &= ~(1 << arg1);
        }
    }
}

int FUN_001b40f0(void *arg0, int arg1) {
    if (arg1 >= 8) {
        return 0;
    }
    return *(unsigned char *)((char *)(arg0) + 64) & (1 << arg1) & 0xFF;
}

int FUN_001b4120(int *p)
{
    return *(unsigned char *)((char *)p + 64);
}

int FUN_001b4130(struct O4130 *arg0) {
    struct Rc_1b2fa0 *temp_a0;
    struct Rc_1b2fa0 *temp_v0;

    if ((arg0->f32 == 0) || (FUN_001b4120((int *)arg0) == 0) || (arg0->f56->f8 == 0)) {
        return 0;
    }
    if (arg0->f160 == 0) {
        temp_v0 = ((struct Rc_1b2fa0 *)((Gap::Attrs::igTextureAttr *)arg0->f32->f12)->getImage(0));
        if (temp_v0 != 0) {
            temp_v0->rc = temp_v0->rc + 1;
        }
        temp_a0 = arg0->f160;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        arg0->f160 = temp_v0;
        if (arg0->f160 == 0) {
            return 0;
        }
    }
    if (arg0->f160->f16 != 1) {
        return 0;
    }
    return 1;
}

void FUN_001b4220(struct A4220 *arg0, struct B4220 *arg1) {
    int temp_s2;
    int n;
    int i;
    struct Q_1b2fa0 *q;

    q = arg0->f144;
    temp_s2 = arg1->f52;
    n = 0;
    if (q != 0) {
        n = q->count;
    }
    if (n > 8) {
        n = 8;
    }
    for (i = 0; i < n; i++) {
        FUN_001b4090((T_1b2fa0 *)arg0, i, ((Gap::Sg::igAttrStackManager *)temp_s2)->getLightState((Gap::Attrs::igLightAttr *)arg0->f144->data[i]));
    }
}

void FUN_001b42c0(TravFlattenView *self, int root) {
    int saved[32];
    Gap::Sg::igTraversalFunctionList *table = Gap::Sg::igCommonTraversal::_getTraversalFunctions();
    int meta = (int)Gap::Sg::igGeometry::getClassMeta();
    int n = igMetaObject_CountTree((igMetaObject *)meta);
    int i;
    for (i = 0; i < n; i++) {
        TravObject *m = ((TravObject *)igMetaObject_GetTreeNode((igMetaObject *)meta, i));
        saved[i] = (int)table->get(m->_id);
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)table, (igMetaObject *)m, (igTraversalFunction *)FUN_001b3ad0);
    }
    DAT_005625f0 = self;
    clearRetained(self->_a);
    clearRetained(self->_b);
    igTraversal_TraverseChildren((igTraversal *)root, (igNode *)self);
    for (i = 0; i < n; i++) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)table, (igMetaObject *)(((TravObject *)igMetaObject_GetTreeNode((igMetaObject *)meta, i))), (igTraversalFunction *)saved[i]);
    }
}

void FUN_001b4500(struct O4500 *o, struct S4500 *s, int b) {
    s = o->s;
    if (s != 0) {
        if (s->k == 1) { o->x = s->firstX; o->y = s->firstY; o->z = s->firstZ; o->w = 0x3F800000; return; }
        o->x = s->secondX; o->y = s->secondY; o->z = s->secondZ; o->w = 0;
    }
}

int FUN_001b4bb0(igCommonTraversal *traversal, int node) {
    igAttrStackManager *manager;
    igAttrStack *l;
    int v;

    manager = (igAttrStackManager *)traversal->_attrStack;
    l = ((igAttrStack **)((igAttrStackList *)manager->_attrStacks)->_data)[((int *)manager->_attrStackIndexTable)[Gap::Attrs::igModelViewMatrixAttr::getClassMeta()->_id]];
    if (l->_count == 0) {
        v = 0;
    } else {
        v = *(int *)(l->_data + ((l->_count - 1) * 4));
    }
    DAT_00562638[0]->vX(node, v);
    return 0;
}

/* The attribute objects igCommonTraversal_DrawCartoonShader drives through their virtual slots. */
class ShaderAttrView_1b4c40 : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10();
    virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual int query(int what);
    virtual void d22();
    virtual void setEnabled(int enabled);
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void d29();
    virtual void set30(int value);
    virtual void set31(int value);
    virtual void set32(int value);
    virtual void set33(int value);
    short _cachedAttrIndex;
    short _cachedUnitID;
    ShaderAttrView_1b4c40 *_texture;
};
struct igCartoonShader {
    char _pad0[32];
    ShaderAttrView_1b4c40 *_oTex;
    ShaderAttrView_1b4c40 *_sTex;
    int _mats;
    int _geoms;
    int _oTexCoordIndex;
    int _sTexCoordIndex;
    char _pad56[92];
    ShaderAttrView_1b4c40 *_tcs0;
    ShaderAttrView_1b4c40 *_tcs1;
};
struct ImageView_1b4c40 { char _pad0[16]; int _format; char _pad20[24]; int _levels; };
extern "C" ShaderAttrView_1b4c40 *DAT_005625f8;
extern "C" ShaderAttrView_1b4c40 *DAT_00562600;
extern "C" ShaderAttrView_1b4c40 *DAT_00562608;
extern "C" ShaderAttrView_1b4c40 *DAT_00562610;
extern "C" ShaderAttrView_1b4c40 *DAT_00562618;
extern "C" ShaderAttrView_1b4c40 *DAT_00562620;
extern "C" ShaderAttrView_1b4c40 *DAT_00562628;
extern "C" ShaderAttrView_1b4c40 *DAT_00562630;
static inline void pushAttr_1b4c40(igAttrStackManager *manager, ShaderAttrView_1b4c40 *attr) {
    /* matching construct: declaration order n, stack, slot, pushed (slot s2, count s5) */
    int n;
    AttrObjectStack *stack;
    int slot;
    igObject *pushed;
    slot = attr->_cachedUnitID + ((int *)manager->_attrStackIndexTable)[attr->_cachedAttrIndex];
    stack = ((AttrObjectStackList *)manager->_attrStacks)->_data[slot];
    if (stack->_cachedOverride < 0) {
        stack->_cachedOverride = stack->_count;
    }
    pushed = (igObject *)attr;
    n = stack->getCount();
    if (n < stack->_capacity) {
        stack->_count = stack->_count + 1;
    } else {
        ((Gap::Core::igDataList *)stack)->resizeAndSetCount(n + 1, 4);
    }
    stack->set(n, &pushed);
    igAttrStackManager_MarkStackChanged(manager, (igAttrStack *)stack, slot);
}
static inline void popAttr_1b4c40(igAttrStackManager *manager, ShaderAttrView_1b4c40 *attr_) {
    /* matching construct: the attribute held as an igObject copy takes a3, the pop proc a2 */
    igObject *attr = (igObject *)attr_;
    int slot = attr_->_cachedUnitID + ((int *)manager->_attrStackIndexTable)[attr_->_cachedAttrIndex];
    AttrObjectStack *stack = ((AttrObjectStackList *)manager->_attrStacks)->_data[slot];
    igObject *top = stack->get(stack->_count - 1);
    void (*pop)(igObject *, int) = stack->_popProc;
    if (pop != 0 && top == attr) {
        pop(top, manager->_popProcData);
    }
    stack->_count = stack->_count - 1;
    if (stack->_count == stack->_cachedOverride) {
        stack->_cachedOverride = -1;
    }
    igAttrStackManager_MarkStackChanged(manager, (igAttrStack *)stack, slot);
}

void igCommonTraversal_DrawCartoonShader(igCartoonShader *self, igCommonTraversal *traversal) {
    int saved[32];
    /* matching construct: declaration order (count s6, procs s5, meta s4, manager s3), from a 120-order search */
    int i;
    int count;
    Gap::Sg::igTraversalFunctionList *procs;
    igMetaObject *meta;
    igAttrStackManager *manager;
    ImageView_1b4c40 *image;
    if (self->_oTex == 0 || self->_sTex == 0) {
        return;
    }
    self->_oTex->setEnabled(0);
    if (((ImageView_1b4c40 *)((Gap::Attrs::igTextureAttr *)self->_oTex->_texture)->getImage(0))->_format != 1) {
        return;
    }
    image = (ImageView_1b4c40 *)((Gap::Attrs::igTextureAttr *)self->_oTex->_texture)->getImage(0);
    if (image->_levels != 1) {
        ((Gap::Gfx::igImage *)image)->convert(IG_GFX_TEXTURE_FORMAT_A_8, (Gap::Gfx::igImage *)image);
    }
    self->_oTex->_texture->set32(0);
    self->_oTex->_texture->set33(0);
    self->_sTex->_texture->set32(0);
    self->_sTex->_texture->set33(0);
    self->_sTex->_texture->set30(0);
    self->_oTex->_texture->set31(0);
    self->_tcs0->set31(self->_sTexCoordIndex);
    self->_tcs1->set31(self->_oTexCoordIndex);
    manager = (igAttrStackManager *)traversal->_attrStack;
    procs = Gap::Sg::igCommonTraversal::_getTraversalFunctions();
    meta = Gap::Sg::igGeometry::getClassMeta();
    count = igMetaObject_CountTree(meta);
    for (i = 0; i < count; i++) {
        igMetaObject *node = (igMetaObject *)igMetaObject_GetTreeNode(meta, i);
        saved[i] = (int)procs->get(node->_id);
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)procs, node, (igTraversalFunction *)FUN_001b4bb0);
    }
    DAT_00562638[0] = (VC_1b2fa0 *)self;
    ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)self->_mats))->setCount(0);
    ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)self->_geoms))->setCount(0);
    igTraversal_TraverseChildren((igTraversal *)traversal, (igNode *)self);
    for (i = 0; i < count; i++) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)procs, (igMetaObject *)igMetaObject_GetTreeNode(meta, i), (igTraversalFunction *)saved[i]);
    }
    FUN_001dc500((A_1dc500 *)traversal->_sorter, 0, 0);
    FUN_001b4570((LightingTexGenView *)self, traversal);
    if (((ShaderAttrView_1b4c40 *)traversal->_capabilityManager)->query(8) >= 2) {
        if (DAT_00562620 == 0) {
            DAT_00562620 = (ShaderAttrView_1b4c40 *)Gap::Attrs::igTextureStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
            DAT_00562620->set30(1);
            DAT_00562620->setEnabled(1);
        }
        self->_oTex->setEnabled(1);
        self->_tcs1->setEnabled(1);
        pushAttr_1b4c40(manager, DAT_00562630);
        pushAttr_1b4c40(manager, DAT_00562628);
        pushAttr_1b4c40(manager, DAT_00562600);
        pushAttr_1b4c40(manager, self->_sTex);
        pushAttr_1b4c40(manager, DAT_00562610);
        pushAttr_1b4c40(manager, self->_tcs0);
        pushAttr_1b4c40(manager, DAT_00562620);
        pushAttr_1b4c40(manager, self->_oTex);
        pushAttr_1b4c40(manager, DAT_00562618);
        pushAttr_1b4c40(manager, self->_tcs1);
        igTraversal_TraverseChildren((igTraversal *)traversal, (igNode *)self);
        popAttr_1b4c40(manager, self->_tcs1);
        popAttr_1b4c40(manager, DAT_00562618);
        popAttr_1b4c40(manager, self->_oTex);
        popAttr_1b4c40(manager, DAT_00562620);
        popAttr_1b4c40(manager, self->_tcs0);
        popAttr_1b4c40(manager, DAT_00562610);
        popAttr_1b4c40(manager, self->_sTex);
        popAttr_1b4c40(manager, DAT_00562600);
        popAttr_1b4c40(manager, DAT_00562628);
        popAttr_1b4c40(manager, DAT_00562630);
    } else {
        pushAttr_1b4c40(manager, DAT_00562630);
        pushAttr_1b4c40(manager, DAT_00562628);
        pushAttr_1b4c40(manager, DAT_00562600);
        pushAttr_1b4c40(manager, DAT_00562610);
        pushAttr_1b4c40(manager, self->_sTex);
        pushAttr_1b4c40(manager, self->_tcs0);
        igTraversal_TraverseChildren((igTraversal *)traversal, (igNode *)self);
        popAttr_1b4c40(manager, self->_tcs0);
        popAttr_1b4c40(manager, self->_sTex);
        pushAttr_1b4c40(manager, self->_oTex);
        pushAttr_1b4c40(manager, self->_tcs1);
        pushAttr_1b4c40(manager, DAT_00562608);
        pushAttr_1b4c40(manager, DAT_005625f8);
        igTraversal_TraverseChildren((igTraversal *)traversal, (igNode *)self);
        popAttr_1b4c40(manager, DAT_005625f8);
        popAttr_1b4c40(manager, DAT_00562608);
        popAttr_1b4c40(manager, self->_tcs1);
        popAttr_1b4c40(manager, self->_oTex);
        popAttr_1b4c40(manager, DAT_00562610);
        popAttr_1b4c40(manager, DAT_00562600);
        popAttr_1b4c40(manager, DAT_00562628);
        popAttr_1b4c40(manager, DAT_00562630);
    }
    FUN_001dc610((igSorter *)traversal->_sorter);
}

namespace Gap {
namespace Sg {

void igCommonTraversal::registerClass(igMetaObject *meta) {
    _registerClass(travProcs, meta);
}

void igCommonTraversal::_registerClass(igTraversalFunctionList *tpl, igMetaObject *meta) {
    igTraversal::_registerClass(tpl, meta);
    if (igMetaObject_IsOfType((igMetaObject *)meta, (igMetaObject *)(((int)Gap::Sg::igNode::getClassTypeSafe()))) != 0) {
        NodeProcTable t = DAT_0048d8f0;
        int i;
        t.e[0].meta = (int)g_igActor_metaObject;
        t.e[1].meta = (int)Gap::Sg::igProjectiveShadowShader::getClassMeta();
        t.e[2].meta = g_igSelfShadowShader_metaObject;
        t.e[3].meta = g_igDOFShader_metaObject[0];
        t.e[4].meta = (int)Gap::Sg::igSegment::getClassMeta();
        t.e[5].meta = (int)Gap::Sg::igEnvironmentMapShader2::getClassMeta();
        t.e[6].meta = g_igInverseKinematicsHandle_metaObject;
        t.e[7].meta = g_igInverseKinematicsSolver_metaObject;
        t.e[8].meta = g_igInverseKinematicsJoint_metaObject;
        t.e[9].meta = g_igMultiTextureShader_metaObject[0];
        t.e[10].meta = g_igMultiResolutionMeshInstance_metaObject;
        t.e[11].meta = g_igCartoonShader_metaObject[0];
        t.e[12].meta = g_igBumpMapShader_metaObject[0];
        t.e[13].meta = (int)g_unlinkedTransformClass_metaObject;
        t.e[14].meta = g_igMorphInstance_metaObject;
        t.e[15].meta = g_igMorphInstance2_metaObject;
        t.e[16].meta = (int)Gap::Sg::igLod::getClassMeta();
        t.e[17].meta = (int)Gap::Sg::igLightStateSet::getClassMeta();
        t.e[18].meta = (int)Gap::Sg::igLightSet::getClassMeta();
        t.e[19].meta = (int)Gap::Sg::igGeometry::getClassMeta();
        t.e[20].meta = (int)Gap::Sg::igPlanarShadowShader::getClassMeta();
        t.e[21].meta = g_igShader_metaObject[0];
        t.e[22].meta = g_igShader2_metaObject;
        t.e[23].meta = (int)Gap::Sg::igBlendMatrixSelect::getClassMeta();
        t.e[24].meta = (int)Gap::Sg::igOverrideAttrSet::getClassMeta();
        t.e[25].meta = (int)Gap::Sg::igAttrSet::getClassMeta();
        t.e[26].meta = (int)Gap::Sg::igTransform::getClassMeta();
        t.e[27].meta = (int)Gap::Sg::igBillboard::getClassMeta();
        t.e[28].meta = (int)Gap::Sg::igSwitch::getClassMeta();
        t.e[29].meta = (int)Gap::Sg::igTransformRecorder::getClassMeta();
        t.e[30].meta = g_igTimeTransform_metaObject[0];
        t.e[31].meta = g_igCompiledGraph_metaObject[0];
        t.e[32].meta = (int)Gap::Sg::igModelViewMatrixBoneSelect::getClassMeta();
        t.e[33].meta = g_igTimeSwitch_metaObject;
        for (i = 0; i < 34; i++) {
            NodeProcEntry *e = &t.e[i];
            if (e->meta != 0 && igMetaObject_IsOfType((igMetaObject *)meta, (igMetaObject *)e->meta) != 0) {
                igTraversal::_setFunction(tpl, (igMetaObject *)meta, (igTraversalFunction *)e->proc);
                return;
            }
        }
    }
}

void igCommonTraversal::userConstruct(int flag) {
    igTraversal::userConstruct(flag);
    if (flag == 0) {
        cacheTravProcs();
        _matrixOptimization->setState(false);
        _normalizeNormalsEnable->setState(true);
    }
}

void igCommonTraversal::userRegister() {
    travProcs = igTraversalFunctionList::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    Gap::Attrs::igAttr::arkRegister();
    Gap::Attrs::igTextureBindAttr::arkRegister();
    Gap::Attrs::igModelViewMatrixAttr::arkRegister();
    Gap::Attrs::igVertexBlendMatrixAttr::arkRegister();
    Gap::Attrs::igTextureMatrixAttr::arkRegister();
    Gap::Attrs::igVertexBlendStateAttr::arkRegister();
    igVertexBlendMatrixListAttr_EnsureRegistered();
}

void igCommonTraversal::userUnregister() {
    igObject::release(travProcs);
}
}
}

