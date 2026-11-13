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

int Gap__Sg__igEnbayaTransformSource__vfunc_26(EnbayaTransformSourceView_1c1bd0 *o, int a, int b, int c, int d) {
    return o->_enbayaAnimationSource->f(a, b, c, d, o->_trackId);
}

int Gap__Sg__igEnbayaTransformSource__vfunc_27(EnbayaTransformSourceView_1c1bf0 *o, int a, int b, int c) {
    return o->_enbayaAnimationSource->f(a, b, c, o->_trackId);
}

int Gap__Sg__igEnbayaTransformSource__vfunc_28(EnbayaTransformSourceView_1c1c10 *o, int a, int b, int c, int d, int e) {
    return o->_enbayaAnimationSource->f(a, b, c, d, e, o->_trackId);
}

int Gap__Sg__igEnbayaTransformSource__vfunc_31(void) {
    return 0;
}

void Gap__Sg__igEnbayaTransformSource__vfunc_32(int a0) {
    FUN_001c0ea0(*(EnbayaSourceView **)((char *)a0 + 12));
}

void FUN_001c1c50(void **self, int flag) {
    Gap__Sg__igNode__vfunc_09((void * *)self, flag);
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
                igObject_Destroy((void *)r);
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
                igObject_Destroy((void *)r);
            }
        }
    }
    n = l->count;
    for (i = 0; i < n; i++) {
        l->data[i] = 0;
    }
    l->count = 0;
    if (igMetaObject_CountInstances(arg0->vA(), 1) == 0) {
        arg0->vB();
    }
    FUN_001c5e20((T_1c5e20 *)arg0);
}

int FUN_001c1e00(void) {
    return ((int *)g_igEnvironmentMapShader2_metaObject)[0];
}

void FUN_001c1e10(void) {
    int temp_s0;

    if (((void * * *)DAT_00562730)[0] == 0) {
        ((void * * *)DAT_00562730)[0] = (void **)(((void * *)igTextureStateAttr_CreateInstance(Memory_GetAllocatorBySelector(DAT_00587038[0]))));
        ((DW4VC_128_1 *)(((void * * *)DAT_00562730)[0]))->vX((int)(1));
        ((DW4VC_100_1 *)(((void * * *)DAT_00562730)[0]))->vX((int)(0));
    }
    if (((void * * *)DAT_00562738)[0] == 0) {
        ((void * * *)DAT_00562738)[0] = (void **)(((void * *)igBlendStateAttr_CreateInstance(Memory_GetAllocatorBySelector(DAT_00587038[0]))));
        ((DW4VC_128_1 *)(((void * * *)DAT_00562738)[0]))->vX((int)(1));
    }
    if (DAT_00562740[0] == 0) {
        DAT_00562740[0] = (void **)(((void * *)igBlendStateAttr_CreateInstance(Memory_GetAllocatorBySelector(DAT_00587038[0]))));
        ((DW4VC_128_1 *)(DAT_00562740[0]))->vX((int)(0));
    }
    if (((T_1c1e10 * *)DAT_00562758)[0] == 0) {
        T_1c1e10 *p;
        temp_s0 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
        p = ((T_1c1e10 * *)DAT_00562758)[0];
        if (p != 0) {
            p->refs = p->refs - 1;
            if (((unsigned long long) ((long long) p->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)p);
            }
        }
        ((T_1c1e10 * *)DAT_00562758)[0] = (T_1c1e10 *)(((void *)FUN_0013b270(temp_s0)));
        ((DW4VC_128_1 *)(((T_1c1e10 * *)DAT_00562758)[0]))->vX((int)(0));
    }
}

void FUN_001c1f90(int) {
    S_ref *p;
    p = ((S_ref * *)DAT_00562730)[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((void *)p);
        ((S_ref * *)DAT_00562730)[0] = 0;
    }
    p = ((S_ref * *)DAT_00562738)[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((void *)p);
        ((S_ref * *)DAT_00562738)[0] = 0;
    }
    p = ((S_ref * *)DAT_00562740)[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((void *)p);
        ((S_ref * *)DAT_00562740)[0] = 0;
    }
    p = ((S_ref * *)DAT_00562758)[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) igObject_Destroy((void *)p);
    }
    ((S_ref * *)DAT_00562758)[0] = 0;
}

void FUN_001c20b0(Controller *self) {
  unsigned char flag;
  Obj_1c20b0 *s1;
  int props = ((PropertySet * *)g_objectSystem)[0]->props;
  flag = 1;
  thunk_FUN_00306e50(props, 7, DAT_004e4600, &flag, 1, 1);
  self->enabled = flag;
  assign(self->f76, igSmartPointer<Obj_1c20b0>(((Obj_1c20b0 *)FUN_00132810(igObject_GetAllocator(self)))));
  self->f76->setValue(self->a32);
  self->f76->configure(0);
  assign(self->f80, igSmartPointer<Obj_1c20b0>(((Obj_1c20b0 *)FUN_001325a0(igObject_GetAllocator(self)))));
  self->f80->setKind(2);
  self->f80->configure(0);
  assign(self->f84, igSmartPointer<Obj_1c20b0>(((Obj_1c20b0 *)FUN_00131c60(igObject_GetAllocator(self)))));
  self->f84->field12 = 2;
  self->f84->configure(0);
  if (self->p36 != 0) {
    self->p36->configure(0);
    assign(self->f88, igSmartPointer<Obj_1c20b0>(((Obj_1c20b0 *)FUN_001325a0(igObject_GetAllocator(self)))));
    self->f88->setKind(0);
    self->f88->configure(0);
    self->f88->setValue(self->a40);
    assign(self->f92, igSmartPointer<Obj_1c20b0>(((Obj_1c20b0 *)FUN_00131c60(igObject_GetAllocator(self)))));
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
    assign(self->f100, igSmartPointer<Obj_1c20b0>(((Obj_1c20b0 *)FUN_00132810(igObject_GetAllocator(self)))));
    self->f100->setValue(self->a52);
    self->f100->configure(0);
    s1 = self->f88;
    if (s1 != 0 && self->a56 == self->a40) {
      assign(self->f104, s1);
    } else {
      assign(self->f104, igSmartPointer<Obj_1c20b0>(((Obj_1c20b0 *)FUN_001325a0(igObject_GetAllocator(self)))));
      self->f104->setKind(0);
      self->f104->configure(0);
      self->f104->setValue(self->a56);
    }
    assign(self->f108, igSmartPointer<Obj_1c20b0>(((Obj_1c20b0 *)FUN_00131c60(igObject_GetAllocator(self)))));
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
            if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) igObject_Destroy((void *)p);
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
            if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) igObject_Destroy((void *)p);
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
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((void *)q);
    }
    arg0->f76 = 0;
    q = arg0->f80;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((void *)q);
    }
    arg0->f80 = 0;
    q = arg0->f84;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((void *)q);
    }
    arg0->f84 = 0;
    q = arg0->f88;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((void *)q);
    }
    arg0->f88 = 0;
    q = arg0->f92;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((void *)q);
    }
    arg0->f92 = 0;
    q = arg0->f96;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((void *)q);
    }
    arg0->f96 = 0;
    q = arg0->f100;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((void *)q);
    }
    arg0->f100 = 0;
    q = arg0->f104;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((void *)q);
    }
    arg0->f104 = 0;
    q = arg0->f108;
    if (q != 0) {
        q->refs = q->refs - 1;
        if (((unsigned long long)((long long)q->refs << 0x29) >> 0x29) == 0) igObject_Destroy((void *)q);
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
        igTraversal_TraverseChildren((int)t, (S_1e07a0 *)self);
        return;
    }
    if (self->_useContext) FUN_001dc500(t->_context, self->_unit, 0);
    for (i = 0; i < n; i++) {
        EnvAttrList *p = self->_pushLists->_data[i];
        int m = p->_count;
        int j;
        for (j = 0; j < m; j++) pushEnvAttr(s, p->_data[j]);
        igTraversal_TraverseChildren((int)t, (S_1e07a0 *)self);
        {
            EnvAttrList *q = self->_popLists->_data[i];
            for (j = q->_count - 1; j >= 0; j--) popEnvAttr(s, q->_data[j]);
        }
    }
    if (self->_useContext) FUN_001dc610(t->_context);
}

void FUN_001c2eb0(S0_1c2eb0 *arg0, Rc *arg1) {
    Rc *temp_a0;

    if (arg1 != 0) {
        arg1->rc = arg1->rc + 1;
    }
    temp_a0 = (Rc *)arg0->f32;
    if (temp_a0 != 0) {
        temp_a0->rc = temp_a0->rc - 1;
        if ((temp_a0->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f32 = (E_1c2eb0 *)arg1;
    arg0->f32->f96 = 0;
    bool b = FUN_00140c00(arg0->f32, 0) != 0;
    if (!b) {
        FUN_001c31e0(arg0->f32);
    }
    arg0->f60 = 0;
}

void FUN_001c2f50(igPsx2EnvironmentMapShader *self, igObject *value) {
    igObject *previous;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    previous = (igObject *)(self->_diffuseTextureBind);
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->_diffuseTextureBind = (int)(value);
    self->_configured = 0;
}

/* Setter for `_diffuseTextureCoordIndex` (diffuse texture-coordinate set index). It also clears
 * `_configured`, so the shader's render state is rebuilt on its next use (`_configured` is the
 * shader's built-once flag). */

void FUN_001c2fd0(igPsx2EnvironmentMapShader *self, int coordIndex) {
    self->_diffuseTextureCoordIndex = coordIndex;
    self->_configured = 0;
}

void FUN_001c2fe0(igPsx2EnvironmentMapShader *self, igObject *value) {
    igObject *previous;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    previous = (igObject *)(self->_glossMapTexture);
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->_glossMapTexture = (int)(value);
    self->_configured = 0;
}

/* Setter for `_glossTextureCoordIndex` (gloss-map texture-coordinate set index). It also clears
 * `_configured`, so the shader's render state is rebuilt on its next use (`_configured` is the
 * shader's built-once flag). */

void FUN_001c3060(igPsx2EnvironmentMapShader *self, int coordIndex) {
    self->_glossTextureCoordIndex = coordIndex;
    self->_configured = 0;
}

/* IgPsx2EnvironmentMapShader slot 42: store the reflection amount and clear _configured so the
 * shader is set up again before its next use. */

void FUN_001c3070(igPsx2EnvironmentMapShader *self, float reflectionAmount) {
    self->_reflectionAmount = reflectionAmount;
    self->_configured = 0;
}

/* Setter for `_isTransparent` (transparency flag). It also clears `_configured`, so the shader's
 * render state is rebuilt on its next use (`_configured` is the shader's built-once flag). */

void FUN_001c3080(igPsx2EnvironmentMapShader *self, char isTransparent) {
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
        o = ((Obj_1c3090 *)FUN_0013aec0(igObject_GetAllocator(arg0)));
        ObjectList_AppendRetained(arg0->f64, o);
        ObjectList_AppendRetained(arg0->f68, o);
        o->refs = o->refs - 1;
        if ((o->refs & 0x7FFFFF) == 0) {
            igObject_Destroy((void *)o);
        }
        arg0->f32->f96 = 2;
        if ((FUN_00140c00(arg0->f32, 0) != 0) == 0) {
            FUN_001c31e0(arg0->f32);
            if (arg0->f73 != 0) {
                FUN_00141190(arg0->f32, 1);
            }
        }
        ObjectList_AppendRetained(o, arg0->f80);
        ObjectList_AppendRetained(o, ((int *)DAT_00562730)[0]);
        ObjectList_AppendRetained(o, arg0->f76);
        ObjectList_AppendRetained(o, arg0->f84);
    }
}

void FUN_001c31d0(void) {

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
    if (GPR_00554c14 != 0) {
        a = ((SphereMapAllocator *)Memory_GetAllocatorBySelector(DAT_00587028[0]));
    } else {
        a = ((SphereMapAllocator *)Memory_GetAllocatorBySelector(DAT_00587060[0]));
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
                    FUN_001c4140(dir, color, &face, dst);
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
    if (GPR_00554c14 != 0) {
        a = ((SphereMapAllocator *)Memory_GetAllocatorBySelector(DAT_00587028[0]));
    } else {
        a = ((SphereMapAllocator *)Memory_GetAllocatorBySelector(DAT_00587060[0]));
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

