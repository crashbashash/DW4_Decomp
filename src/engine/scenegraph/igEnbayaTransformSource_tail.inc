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

void FUN_001c1c50(void **self, int flag) {
    igNode_userConstruct((void * *)self, flag);
}

void FUN_001c1c60(T_1c1c60 *arg0) {
    List_1c1c60 *l;
    int n;
    int i;
    Ref_1c1c60 *r;
    l = arg0->f64;
    n = l->count;
    for (i = 0; i < n; i++) {
        r = l->data[i];
        if (r != 0) {
            r->rc = r->rc - 1;
            if ((r->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)r);
            }
        }
    }
    n = l->count;
    for (i = 0; i < n; i++) {
        l->data[i] = 0;
    }
    l->count = 0;
    l = arg0->f68;
    n = l->count;
    for (i = 0; i < n; i++) {
        r = l->data[i];
        if (r != 0) {
            r->rc = r->rc - 1;
            if ((r->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)r);
            }
        }
    }
    n = l->count;
    for (i = 0; i < n; i++) {
        l->data[i] = 0;
    }
    l->count = 0;
    if (igMetaObject_CountInstances((igMetaObject *)(arg0->vA()), 1) == 0) {
        arg0->vB();
    }
    igGroup_userDestruct((T_1c5e20 *)arg0);
}

int FUN_001c1e00(void) {
    return ((int)g_igEnvironmentMapShader2_metaObject);
}

void FUN_001c1e10(void) {
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
        g_igAlphaStateAttr_instance.p = (igAlphaStateAttr *)Gap::Attrs::igAlphaStateAttr::_instantiateFromPool((igMemoryPoolView *)temp_s0);
        ((DW4VC_128_1 *)g_igAlphaStateAttr_instance.p)->vX(0);
    }
}

void FUN_001c1f90(int) {
    S_ref *p;
    p = ((S_ref * *)DAT_00562730)[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)p);
        ((S_ref * *)DAT_00562730)[0] = 0;
    }
    p = ((S_ref * *)DAT_00562738)[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)p);
        ((S_ref * *)DAT_00562738)[0] = 0;
    }
    p = ((S_ref * *)DAT_00562740)[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)p);
        ((S_ref * *)DAT_00562740)[0] = 0;
    }
    g_igAlphaStateAttr_instance.clear();
}

void FUN_001c20b0(Controller *self) {
  unsigned char flag;
  Obj_1c20b0 *s1;
  int props = ((PropertySet *)g_objectSystem)->props;
  flag = 1;
  igGetRegistryValue_Bool((igRegistry *)props, 7, "envMapDiscardUnusedImages", &flag, 1, 1);
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

void FUN_001c2880(S_1c2880 *arg0) {
    OL *l;
    int n;
    int i;
    int n2;
    int i2;
    R_1c2880 *p;
    R_1c2880 *q;
    l = arg0->l64;
    n = l->count;
    for (i = 0; i < n; i++) {
        p = l->data[i];
        if (p != 0) {
            p->refs = p->refs - 1;
            if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)p);
        }
    }
    n2 = l->count;
    for (i2 = 0; i2 < n2; i2++) {
        l->data[i2] = 0;
    }
    l->count = 0;
    l = arg0->l68;
    n = l->count;
    for (i = 0; i < n; i++) {
        p = l->data[i];
        if (p != 0) {
            p->refs = p->refs - 1;
            if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)p);
        }
    }
    n2 = l->count;
    for (i2 = 0; i2 < n2; i2++) {
        l->data[i2] = 0;
    }
    l->count = 0;
    arg0->b72 = 0;
    q = arg0->f76;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)q);
    }
    arg0->f76 = 0;
    q = arg0->f80;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)q);
    }
    arg0->f80 = 0;
    q = arg0->f84;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)q);
    }
    arg0->f84 = 0;
    q = arg0->f88;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)q);
    }
    arg0->f88 = 0;
    q = arg0->f92;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)q);
    }
    arg0->f92 = 0;
    q = arg0->f96;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)q);
    }
    arg0->f96 = 0;
    q = arg0->f100;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)q);
    }
    arg0->f100 = 0;
    q = arg0->f104;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)q);
    }
    arg0->f104 = 0;
    q = arg0->f108;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)q);
    }
    arg0->f108 = 0;
}

void FUN_001c2be0(EnvPassShaderView *self, EnvTraversalView *t) {
    EnvAttrStack *s = t->_attrStack;
    int n;
    int i;
    if (!self->_configured) self->configure(t->_arg32);
    self->prepare(t);
    n = self->_pushLists->_count;
    if (n == 0) {
        igTraversal_TraverseChildren((igTraversal *)t, (igNode *)self);
        return;
    }
    if (self->_useContext) FUN_001dc500(t->_context, self->_unit, 0);
    for (i = 0; i < n; i++) {
        EnvAttrList *p = self->_pushLists->_data[i];
        int m = p->_count;
        int j;
        for (j = 0; j < m; j++) pushEnvAttr(s, p->_data[j]);
        igTraversal_TraverseChildren((igTraversal *)t, (igNode *)self);
        {
            EnvAttrList *q = self->_popLists->_data[i];
            for (j = q->_count - 1; j >= 0; j--) popEnvAttr(s, q->_data[j]);
        }
    }
    if (self->_useContext) FUN_001dc610((igSorter *)t->_context);
}

void igPsx2EnvironmentMapShader_SetEnvironmentMapTexture(S0_1c2eb0 *arg0, Rc *arg1) {
    Rc *temp_a0;

    if (arg1 != 0) {
        arg1->rc = arg1->rc + 1;
    }
    temp_a0 = (Rc *)arg0->f32;
    if (temp_a0 != 0) {
        temp_a0->rc = temp_a0->rc - 1;
        if ((temp_a0->rc & 0x7FFFFF) == 0) {
            igObject_Destroy((igObject *)temp_a0);
        }
    }
    arg0->f32 = (E_1c2eb0 *)arg1;
    arg0->f32->f96 = 0;
    bool b = ((Gap::Attrs::igTextureAttr *)arg0->f32)->getImage(0) != 0;
    if (!b) {
        FUN_001c31e0((igTextureAttr *)arg0->f32);
    }
    arg0->f60 = 0;
}

void igPsx2EnvironmentMapShader_SetDiffuseTexture(igPsx2EnvironmentMapShader *self, igObject *value) {
    igObject *previous;
    igObject::ref(value);
    previous = (igObject *)(self->_diffuseTextureBind);
    igObject::release(previous);
    self->_diffuseTextureBind = (int)(value);
    self->_configured = 0;
}

/* Setter for `_diffuseTextureCoordIndex` (diffuse texture-coordinate set index). It also clears
 * `_configured`, so the shader's render state is rebuilt on its next use (`_configured` is the
 * shader's built-once flag). */

void igPsx2EnvironmentMapShader_SetDiffuseTextureCoordIndex(igPsx2EnvironmentMapShader *self, int coordIndex) {
    self->_diffuseTextureCoordIndex = coordIndex;
    self->_configured = 0;
}

void igPsx2EnvironmentMapShader_SetGlossMapTexture(igPsx2EnvironmentMapShader *self, igObject *value) {
    igObject *previous;
    igObject::ref(value);
    previous = (igObject *)(self->_glossMapTexture);
    igObject::release(previous);
    self->_glossMapTexture = (int)(value);
    self->_configured = 0;
}

/* Setter for `_glossTextureCoordIndex` (gloss-map texture-coordinate set index). It also clears
 * `_configured`, so the shader's render state is rebuilt on its next use (`_configured` is the
 * shader's built-once flag). */

void igPsx2EnvironmentMapShader_SetGlossTextureCoordIndex(igPsx2EnvironmentMapShader *self, int coordIndex) {
    self->_glossTextureCoordIndex = coordIndex;
    self->_configured = 0;
}

/* IgPsx2EnvironmentMapShader slot 42: store the reflection amount and clear _configured so the
 * shader is set up again before its next use. */

void igPsx2EnvironmentMapShader_SetReflectionAmount(igPsx2EnvironmentMapShader *self, float reflectionAmount) {
    self->_reflectionAmount = reflectionAmount;
    self->_configured = 0;
}

/* Setter for `_isTransparent` (transparency flag). It also clears `_configured`, so the shader's
 * render state is rebuilt on its next use (`_configured` is the shader's built-once flag). */

void igPsx2EnvironmentMapShader_SetTransparencyState(igPsx2EnvironmentMapShader *self, char isTransparent) {
    self->_isTransparent = isTransparent;
    self->_configured = 0;
}

void FUN_001c3090(V_1c3090 *arg0, int arg1) {
    Obj_1c3090 *o;
    arg0->c();
    arg0->a(arg1);
    arg0->b(arg1);
    arg0->f60 = 1;
    if (arg0->f32 != 0) {
        o = ((Obj_1c3090 *)Gap::Attrs::igAttrList::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
        ((Gap::Core::igObjectList *)arg0->f64)->append((Gap::Core::igObject *)o);
        ((Gap::Core::igObjectList *)arg0->f68)->append((Gap::Core::igObject *)o);
        o->refs = o->refs - 1;
        if ((o->refs & 0x7FFFFF) == 0) {
            igObject_Destroy((igObject *)o);
        }
        arg0->f32->f96 = 2;
        if ((((Gap::Attrs::igTextureAttr *)arg0->f32)->getImage(0) != 0) == 0) {
            FUN_001c31e0((igTextureAttr *)arg0->f32);
            if (arg0->f73 != 0) {
                ((Gap::Attrs::igTextureCubeAttr *)arg0->f32)->releaseImage(Gap::Attrs::igTextureCubeAttr::CUBE_MAP);
            }
        }
        ((Gap::Core::igObjectList *)o)->append((Gap::Core::igObject *)arg0->f80);
        ((Gap::Core::igObjectList *)o)->append((Gap::Core::igObject *)(((int *)DAT_00562730)[0]));
        ((Gap::Core::igObjectList *)o)->append((Gap::Core::igObject *)arg0->f76);
        ((Gap::Core::igObjectList *)o)->append((Gap::Core::igObject *)arg0->f84);
    }
}

void FUN_001c31d0(void) {

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
    igSmartPointer<igImage> faces[6];
    int i;
    int bytesPerPixel;
    int size;
    igImage *first;
    int width;
    int height;
    unsigned char *pixels;

    for (i = 0; i < 6; i++) {
        faces[i] = igTextureCubeAttr_GetCubeImage(cube, (CubeFaceID)i);
        if (faces[i].p == 0) {
            return;
        }
    }
    if (faces[0].p->_pClut != 0) {
        for (i = 0; i < 6; i++) {
            igSmartPointer<igImage> converted(igImage_CreateInstance(((Gap::Core::igObject *)texture)->getMemoryPool()));
            if (!FUN_00157200(converted.p, IG_GFX_TEXTURE_FORMAT_RGBA_8888_32, faces[i].p)) {
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
    bytesPerPixel = (int)(first->_bitsDepth + (first->_bitsInt + (first->_bitsIdx + (first->_bitsAlpha + (first->_bitsBlu + (first->_bitsRed + first->_bitsGrn)))))) / 8;
    size = bytesPerPixel * (width * height);
    pixels = (unsigned char *)temporaryPool()->Allocate(size);
    memset(pixels, 0, size);
    FUN_001c3ab0(width, height, bytesPerPixel, faces[1].p, faces[0].p, faces[3].p, faces[2].p, faces[5].p, faces[4].p, pixels);
    igSmartPointer<igImage> image(igImage_CreateInstance(((Gap::Core::igObject *)texture)->getMemoryPool()));
    FUN_00156340(image.p, &igStringRef("SphereImage"));
    igImage_SetPixels(image.p, pixels, faces[0].p->_pfmt, width, height);
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
