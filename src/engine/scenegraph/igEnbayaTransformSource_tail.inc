int Gap__Sg__igEnbayaTransformSource__vfunc_23(S_1c1b50 *arg0, int arg1, int arg2) {
    arg0->obj->vX(arg1, arg2, arg0->f8);
    return 1;
}

int Gap__Sg__igEnbayaTransformSource__vfunc_24(void *arg0, int a1, int a2, int a3, int a4) {
    EB *p = (EB *)arg0;
    p->obj->vX(a1, a2, a3, a4, p->f8);
    return 1;
}

int Gap__Sg__igEnbayaTransformSource__vfunc_25(EnbayaTransformSourceView *o, int a, int b) {
    return o->_enbayaAnimationSource->f(a, b, o->_trackId);
}

int igEnbayaTransformSource_evaluateRotation(EnbayaTransformSourceView_1c1bd0 *o, int a, int b, int c, int d) {
    return o->_enbayaAnimationSource->f(a, b, c, d, o->_trackId);
}

int Gap__Sg__igEnbayaTransformSource__vfunc_27(EnbayaTransformSourceView_1c1bf0 *o, int a, int b, int c) {
    return o->_enbayaAnimationSource->f(a, b, c, o->_trackId);
}

int igEnbayaTransformSource_evaluateRotationAndTranslation(EnbayaTransformSourceView_1c1c10 *o, int a, int b, int c, int d, int e) {
    return o->_enbayaAnimationSource->f(a, b, c, d, e, o->_trackId);
}

int Gap__Sg__igEnbayaTransformSource__vfunc_31(void) {
    return 0;
}

void Gap__Sg__igEnbayaTransformSource__vfunc_32(int a0) {
    FUN_001c0ea0(*(EnbayaSourceView **)((char *)a0 + 12));
}

namespace Gap {
namespace Sg {

void igEnvironmentMapShader2::userConstruct(int flag) {
    igNode_userConstruct((void * *)(void * *)this, flag);
}

void igEnvironmentMapShader2::userDestruct() {
    List_1c1c60 *l;
    int n;
    int i;
    Ref_1c1c60 *r;
    l = ((T_1c1c60 *)this)->f64;
    n = l->count;
    for (i = 0; i < n; i++) {
        r = l->data[i];
        if (r != 0) {
            r->rc = r->rc - 1;
            if ((r->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((::igObject *)r);
            }
        }
    }
    n = l->count;
    for (i = 0; i < n; i++) {
        l->data[i] = 0;
    }
    l->count = 0;
    l = ((T_1c1c60 *)this)->f68;
    n = l->count;
    for (i = 0; i < n; i++) {
        r = l->data[i];
        if (r != 0) {
            r->rc = r->rc - 1;
            if ((r->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((::igObject *)r);
            }
        }
    }
    n = l->count;
    for (i = 0; i < n; i++) {
        l->data[i] = 0;
    }
    l->count = 0;
    if (igMetaObject_CountInstances((igMetaObject *)(((T_1c1c60 *)this)->vA()), 1) == 0) {
        ((T_1c1c60 *)this)->vB();
    }
    igGroup_userDestruct((T_1c5e20 *)this);
}

void igEnvironmentMapShader2::initStaticAttrs(igCapabilityManager *capabilityManager)
{
    int temp_s0;

    if (((void * * *)DAT_00562730)[0] == 0) {
        ((void * * *)DAT_00562730)[0] = (void **)(((void * *)Gap::Attrs::igTextureStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem))));
        ((DW4VC_128_1 *)(((void * * *)DAT_00562730)[0]))->vX((int)(1));
        ((DW4VC_100_1 *)(((void * * *)DAT_00562730)[0]))->vX((int)(0));
    }
    if (((void * * *)DAT_00562738)[0] == 0) {
        ((void * * *)DAT_00562738)[0] = (void **)(((void * *)Gap::Attrs::igBlendStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem))));
        ((DW4VC_128_1 *)(((void * * *)DAT_00562738)[0]))->vX((int)(1));
    }
    if (DAT_00562740[0] == 0) {
        DAT_00562740[0] = (void **)(((void * *)Gap::Attrs::igBlendStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem))));
        ((DW4VC_128_1 *)(DAT_00562740[0]))->vX((int)(0));
    }
    if (g_igAlphaStateAttr_instance.p == 0) {
        temp_s0 = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
        g_igAlphaStateAttr_instance.release();
        g_igAlphaStateAttr_instance.p = (::igAlphaStateAttr *)Gap::Attrs::igAlphaStateAttr::_instantiateFromPool((igMemoryPoolView *)temp_s0);
        ((DW4VC_128_1 *)g_igAlphaStateAttr_instance.p)->vX(0);
    }
}

void igEnvironmentMapShader2::destroyStaticAttrs() {
    S_ref *p;
    p = ((S_ref * *)DAT_00562730)[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((::igObject *)p);
        ((S_ref * *)DAT_00562730)[0] = 0;
    }
    p = ((S_ref * *)DAT_00562738)[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((::igObject *)p);
        ((S_ref * *)DAT_00562738)[0] = 0;
    }
    p = ((S_ref * *)DAT_00562740)[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((::igObject *)p);
        ((S_ref * *)DAT_00562740)[0] = 0;
    }
    g_igAlphaStateAttr_instance.clear();
}

void igEnvironmentMapShader2::initAttrs(igCapabilityManager *capabilityManager)
{
    Controller *self = (Controller *)this;
    unsigned char flag;
    Obj_1c20b0 *s1;
    int props = ((PropertySet *)g_objectSystem)->props;
    flag = 1;
    igGetRegistryValue_Bool((::igRegistry *)props, 7, "envMapDiscardUnusedImages", &flag, 1, 1);
    self->enabled = flag;
    assign(self->f76, igSmartPointer<Obj_1c20b0>(((Obj_1c20b0 *)Gap::Attrs::igTextureBindAttr::_instantiateFromPool(((Gap::Core::igObject *)self)->getMemoryPool()))));
    self->f76->setValue(self->a32);
    self->f76->configure(0);
    assign(self->f80, igSmartPointer<Obj_1c20b0>(((Obj_1c20b0 *)Gap::Attrs::igTextureCoordSourceAttr::_instantiateFromPool(((Gap::Core::igObject *)self)->getMemoryPool()))));
    self->f80->setKind(2);
    self->f80->configure(0);
    assign(self->f84, igSmartPointer<Obj_1c20b0>(((Obj_1c20b0 *)Gap::Attrs::igTextureFunctionAttr::_instantiateFromPool(((Gap::Core::igObject *)self)->getMemoryPool()))));
    self->f84->field12 = 2;
    self->f84->configure(0);
    if (self->p36 != 0) {
    self->p36->configure(0);
    assign(self->f88, igSmartPointer<Obj_1c20b0>(((Obj_1c20b0 *)Gap::Attrs::igTextureCoordSourceAttr::_instantiateFromPool(((Gap::Core::igObject *)self)->getMemoryPool()))));
    self->f88->setKind(0);
    self->f88->configure(0);
    self->f88->setValue(self->a40);
    assign(self->f92, igSmartPointer<Obj_1c20b0>(((Obj_1c20b0 *)Gap::Attrs::igTextureFunctionAttr::_instantiateFromPool(((Gap::Core::igObject *)self)->getMemoryPool()))));
    self->f92->field12 = 1;
    self->f92->configure(0);
    if (self->flag48) {
      s1 = ((Obj_1c20b0 * *)DAT_00562738)[0];
      assign(self->f96, s1);
    } else {
      s1 = ((Obj_1c20b0 * *)DAT_00562740)[0];
      assign(self->f96, s1);
    }
    }
    if (self->a52 != 0) {
    assign(self->f100, igSmartPointer<Obj_1c20b0>(((Obj_1c20b0 *)Gap::Attrs::igTextureBindAttr::_instantiateFromPool(((Gap::Core::igObject *)self)->getMemoryPool()))));
    self->f100->setValue(self->a52);
    self->f100->configure(0);
    s1 = self->f88;
    if (s1 != 0 && self->a56 == self->a40) {
      assign(self->f104, s1);
    } else {
      assign(self->f104, igSmartPointer<Obj_1c20b0>(((Obj_1c20b0 *)Gap::Attrs::igTextureCoordSourceAttr::_instantiateFromPool(((Gap::Core::igObject *)self)->getMemoryPool()))));
      self->f104->setKind(0);
      self->f104->configure(0);
      self->f104->setValue(self->a56);
    }
    assign(self->f108, igSmartPointer<Obj_1c20b0>(((Obj_1c20b0 *)Gap::Attrs::igTextureFunctionAttr::_instantiateFromPool(((Gap::Core::igObject *)self)->getMemoryPool()))));
    self->f108->field12 = 0;
    self->f108->configure(0);
    }
}

void igEnvironmentMapShader2::destroyAttrs() {
    _attrPushLists->removeAll();
    _attrPopLists->removeAll();
    _useRenderPackage = false;
    _envMapTextureBind = 0;
    _envMapCoordSource = 0;
    _envMapTextureFunc = 0;
    _diffuseCoordSource = 0;
    _diffuseTextureFunc = 0;
    _diffuseBlendState = 0;
    _glossMapTextureBind = 0;
    _glossMapCoordSource = 0;
    _glossMapTextureFunc = 0;
}

void igEnvironmentMapShader2::shade(igCommonTraversal *ct) {
    EnvTraversalView *t = (EnvTraversalView *)ct;
    EnvAttrStack *s = t->_attrStack;
    int n;
    int i;
    if (!_configured) configure((igCapabilityManager *)t->_arg32);
    vfunc_45(ct);
    n = ((EnvListList *)_attrPushLists.get())->_count;
    if (n == 0) {
        igTraversal_TraverseChildren((::igTraversal *)t, (::igNode *)this);
        return;
    }
    if (_useRenderPackage) FUN_001dc500(t->_context, _isTransparent, 0);
    for (i = 0; i < n; i++) {
        EnvAttrList *p = ((EnvListList *)_attrPushLists.get())->_data[i];
        int m = p->_count;
        int j;
        for (j = 0; j < m; j++) pushEnvAttr(s, p->_data[j]);
        igTraversal_TraverseChildren((::igTraversal *)t, (::igNode *)this);
        {
            EnvAttrList *q = ((EnvListList *)_attrPopLists.get())->_data[i];
            for (j = q->_count - 1; j >= 0; j--) popEnvAttr(s, q->_data[j]);
        }
    }
    if (_useRenderPackage) FUN_001dc610((igSorter *)t->_context);
}

void igEnvironmentMapShader2::setEnvironmentMapTexture(igTextureCubeAttr *envMapTexture) {
    _envMapTexture = envMapTexture;
    _envMapTexture->_applyType = igTextureCubeAttr::NOT_SET;
    bool b = ((Gap::Attrs::igTextureAttr *)_envMapTexture.get())->getImage(0) != 0;
    if (!b) {
        FUN_001c31e0((::igTextureAttr *)_envMapTexture.get());
    }
    _configured = 0;
}

void igEnvironmentMapShader2::setDiffuseTexture(igTextureBindAttr *tex) {
    _diffuseTextureBind = tex;
    _configured = 0;
}

/* Setter for `_diffuseTextureCoordIndex` (diffuse texture-coordinate set index). It also clears
 * `_configured`, so the shader's render state is rebuilt on its next use (`_configured` is the
 * shader's built-once flag). */

void igEnvironmentMapShader2::setDiffuseTextureCoordIndex(int coordIndex) {
    _diffuseTextureCoordIndex = coordIndex;
    _configured = 0;
}

void igEnvironmentMapShader2::setGlossMapTexture(igTextureAttr *glossMapTexture) {
    _glossMapTexture = glossMapTexture;
    _configured = 0;
}

/* Setter for `_glossTextureCoordIndex` (gloss-map texture-coordinate set index). It also clears
 * `_configured`, so the shader's render state is rebuilt on its next use (`_configured` is the
 * shader's built-once flag). */

void igEnvironmentMapShader2::setGlossTextureCoordIndex(int coordIndex) {
    _glossTextureCoordIndex = coordIndex;
    _configured = 0;
}

/* IgPsx2EnvironmentMapShader slot 42: store the reflection amount and clear _configured so the
 * shader is set up again before its next use. */

void igEnvironmentMapShader2::setReflectionAmount(float reflectionAmount) {
    _reflectionAmount = reflectionAmount;
    _configured = 0;
}

/* Setter for `_isTransparent` (transparency flag). It also clears `_configured`, so the shader's
 * render state is rebuilt on its next use (`_configured` is the shader's built-once flag). */

void igEnvironmentMapShader2::setTransparencyState(bool isTransparent) {
    _isTransparent = isTransparent;
    _configured = 0;
}

void igEnvironmentMapShader2::configure(igCapabilityManager *capabilityManager) {
    destroyAttrs();
    initStaticAttrs(capabilityManager);
    initAttrs(capabilityManager);
    _configured = 1;
    if (_envMapTexture != 0) {
        Gap::Attrs::igAttrList *attrs = Gap::Attrs::igAttrList::_instantiateFromPool(getMemoryPool());
        ((Gap::Core::igObjectList *)_attrPushLists.get())->append(attrs);
        ((Gap::Core::igObjectList *)_attrPopLists.get())->append(attrs);
        attrs->release();
        _envMapTexture->_applyType = igTextureCubeAttr::SPHERE_MAP;
        if ((_envMapTexture->getImage(0) != 0) == 0) {
            FUN_001c31e0((::igTextureAttr *)_envMapTexture.get());
            if (_discardUnusedImages != 0) {
                _envMapTexture->releaseImage(igTextureCubeAttr::CUBE_MAP);
            }
        }
        ((Gap::Core::igObjectList *)attrs)->append((Gap::Core::igObject *)_envMapCoordSource.get());
        ((Gap::Core::igObjectList *)attrs)->append((Gap::Core::igObject *)(((int *)DAT_00562730)[0]));
        ((Gap::Core::igObjectList *)attrs)->append((Gap::Core::igObject *)_envMapTextureBind.get());
        ((Gap::Core::igObjectList *)attrs)->append((Gap::Core::igObject *)_envMapTextureFunc.get());
    }
}

void igEnvironmentMapShader2::update(igCommonTraversal *ct)
{
}
}
}

/* The pool for scratch buffers: the current pool when objects allocate from their owner's pool, else the
 * temporary pool. */
static inline igMemoryPoolView *temporaryPool(void) {
    if (g_useOwnerAllocator != 0) {
        return Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent);
    }
    return Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary);
}

/* Builds a sphere map from the six faces of a cube texture and makes it the texture's image. When the faces
 * have a palette, each is converted to RGBA 8888 first; if the first face cannot be converted, the faces are
 * used as they are. */
void FUN_001c31e0(igTextureAttr *texture) {
    igTextureCubeAttr *cube = (igTextureCubeAttr *)texture;
    igSmartPointer<Gap::Gfx::igImage> faces[6];
    int i;
    int bytesPerPixel;
    int size;
    Gap::Gfx::igImage *first;
    int width;
    int height;
    unsigned char *pixels;

    for (i = 0; i < 6; i++) {
        faces[i] = (Gap::Gfx::igImage *)igTextureCubeAttr_GetCubeImage(cube, (CubeFaceID)i);
        if (faces[i].p == 0) {
            return;
        }
    }
    if (faces[0].p->_pClut != 0) {
        for (i = 0; i < 6; i++) {
            igSmartPointer<Gap::Gfx::igImage> converted(Gap::Gfx::igImage::_instantiateFromPool(((Gap::Core::igObject *)texture)->getMemoryPool()));
            if (!converted->convert(IG_GFX_TEXTURE_FORMAT_RGBA_8888_32, faces[i].p)) {
                if (i > 0) {
                    return;
                }
                break;
            }
            faces[i] = converted;
        }
    }
    first = faces[0].p;
    width = first->_px;
    height = first->_py;
    bytesPerPixel = first->getTotalBitsPerPixel() / 8;
    size = bytesPerPixel * (width * height);
    pixels = (unsigned char *)temporaryPool()->Allocate(size);
    memset(pixels, 0, size);
    FUN_001c3ab0(width, height, bytesPerPixel, faces[1].p, faces[0].p, faces[3].p, faces[2].p, faces[5].p, faces[4].p, pixels);
    igSmartPointer<Gap::Gfx::igImage> image(Gap::Gfx::igImage::_instantiateFromPool(((Gap::Core::igObject *)texture)->getMemoryPool()));
    image->setName("SphereImage");
    image->load(pixels, (IG_GFX_TEXTURE_FORMAT)faces[0].p->_pfmt, width, height);
    temporaryPool()->Free(pixels);
    ((Gap::Attrs::igTextureAttr *)texture)->setImage(image.p, 0);
    texture->_source = 0;
}

void FUN_001c3ab0(int width, int height, int bpp, void *face1, void *face0, void *face3, void *face2, void *face5, void *face4, unsigned char *out) {
    SphereMapAllocator *a;
    unsigned char *mask;
    int total;
    int y;
    int x;
    int row;
    int face;
    float n[3];
    float dir[3];
    int nb[4];
    float acc[4];
    total = bpp * (width * height);
    if (g_useOwnerAllocator != 0) {
        a = ((SphereMapAllocator *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent));
    } else {
        a = ((SphereMapAllocator *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary));
    }
    mask = a->alloc(width * height);
    memset(mask, 0, width * height);
    for (y = 0; y < height; y++) {
        float fy = 2.0f * ((float)y / (float)(height - 1) - 0.5f);
        float fy2 = fy * fy;
        row = y * width;
        for (x = 0; x < width; x++) {
            float fx = 2.0f * ((float)x / (float)(width - 1) - 0.5f);
            float fx2 = fx * fx;
            if (fx2 + fy2 <= 1.0f) {
                int i;
                void *color;
                unsigned char *dst;
                n[0] = fx;
                n[1] = fy;
                n[2] = sqrtf(1.0f - fx2 - fy2);
                for (i = 0; i < 3; i++) {
                    dir[i] = 2.0f * (n[2] * n[i]);
                }
                dir[2] -= 1.0f;
                dst = out + bpp * (x + row);
                face = FUN_001c3fd0(dir);
                color = 0;
                if (face == 1) {
                    color = face1;
                } else if (face == 0) {
                    color = face0;
                } else if (face == 3) {
                    color = face3;
                } else if (face == 2) {
                    color = face2;
                } else if (face == 5) {
                    color = face5;
                } else if (face == 4) {
                    color = face4;
                }
                if (color == 0) {
                    mask[x + row] = 1;
                } else {
                    FUN_001c4140(dir, (igImage *)color, &face, dst);
                }
            }
        }
    }
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            int at = x + y * width;
            int dstOffset = bpp * at;
            if (mask[y * width + x] == 1) {
                int count;
                int i;
                nb[0] = bpp * (x + (y - 1) * width);
                nb[1] = bpp * (x + (y + 1) * width);
                nb[2] = bpp * (at - 1);
                nb[3] = bpp * (at + 1);
                memset(acc, 0, 16);
                count = 0;
                for (i = 0; i < 4; i++) {
                    if (nb[i] >= 0 && nb[i] <= total - bpp && mask[nb[i] % bpp] == 0) {
                        int k;
                        count++;
                        for (k = 0; k < bpp; k++) {
                            acc[k] += (float)(unsigned int)out[nb[i] + k];
                        }
                    }
                }
                if (count != 0) {
                    int k;
                    unsigned char *dst;
                    for (i = 0; i < 4; i++) {
                        acc[i] /= (float)count;
                    }
                    dst = out + dstOffset;
                    for (k = 0; k < bpp; k++) {
                        dst[k] = (unsigned int)acc[k];
                    }
                }
            }
        }
    }
    if (g_useOwnerAllocator != 0) {
        a = ((SphereMapAllocator *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleCurrent));
    } else {
        a = ((SphereMapAllocator *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary));
    }
    a->release(mask);
}

int FUN_001c3fd0(float *v) {
    float a[3];
    int r = -1;
    int i;
    a[0] = *(float *)&v[0];
    a[1] = *(float *)&v[1];
    a[2] = *(float *)&v[2];
    for (i = 0; i < 3; i++) {
        if (a[i] < 0.0f) {
            a[i] = a[i] * -1.0f;
        }
    }
    if (a[0] > a[1] && a[0] > a[2]) {
        if (v[0] < 0.0f) {
            r = 0;
        } else if (v[0] > 0.0f) {
            r = 1;
        }
    } else if (a[1] > a[0] && a[1] > a[2]) {
        if (v[1] < 0.0f) {
            r = 2;
        } else if (v[1] > 0.0f) {
            r = 3;
        }
    } else if (a[2] > a[0] && a[2] > a[1]) {
        if (v[2] < 0.0f) {
            r = 4;
        } else if (v[2] > 0.0f) {
            r = 5;
        }
    }
    return r;
}

static inline void scale3(float *v, const float &s) {
    v[0] *= s;
    v[1] *= s;
    v[2] *= s;
}

/* Texel of the cube-map face `*face` that direction `dir` points at, copied to dst (one byte per
 * channel). dir is projected onto the face in place. */
void FUN_001c4140(float *dir, igImage *image, int *face, unsigned char *dst) {
    unsigned char *pixels;
    int x;
    int width;
    int bpp;
    int height;
    int y;
    pixels = (unsigned char *)image->_pImage;
    x = 0;
    width = image->_px;
    height = image->_py;
    bpp = image->_pz;
    y = 0;
    if (*face == 0 || *face == 1) {
        if (dir[0] != 0.0f) {
            scale3(dir, -1.0f / dir[0]);
        }
        dir[1] *= -1.0f;
        dir[1] += 1.0f;
        dir[2] += 1.0f;
        scale3(dir, 0.5f);
        if (*face == 1) {
            y = (int)((1.0f - dir[1]) * (float)height);
        } else {
            y = (int)(dir[1] * (float)height);
        }
        x = (int)(dir[2] * (float)width);
    } else if (*face == 4 || *face == 5) {
        if (dir[2] != 0.0f) {
            scale3(dir, -1.0f / dir[2]);
        }
        dir[1] *= -1.0f;
        dir[1] += 1.0f;
        if (*face == 5) {
            dir[0] *= -1.0f;
        }
        dir[0] += 1.0f;
        scale3(dir, 0.5f);
        if (*face == 4) {
            x = (int)((1.0f - dir[0]) * (float)width);
        } else {
            x = (int)(dir[0] * (float)width);
        }
        if (*face == 5) {
            y = (int)((1.0f - dir[1]) * (float)height);
        } else {
            y = (int)(dir[1] * (float)height);
        }
    } else if (*face == 2 || *face == 3) {
        if (dir[1] != 0.0f) {
            scale3(dir, -1.0f / dir[1]);
        }
        dir[2] *= -1.0f;
        dir[2] += 1.0f;
        dir[0] += 1.0f;
        scale3(dir, 0.5f);
        if (*face == 3) {
            x = (int)((1.0f - dir[0]) * (float)width);
        } else {
            x = (int)(dir[0] * (float)width);
        }
        y = (int)(dir[2] * (float)height);
    }
    unsigned char *src = pixels + bpp * (x + y * width);
    for (int i = 0; i < bpp; i++) {
        dst[i] = src[i];
    }
}
