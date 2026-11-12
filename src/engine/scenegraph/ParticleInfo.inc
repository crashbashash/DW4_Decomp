/* Name lookup: the info's own name resolves to its scene graph; any other name falls through to
 * igObject_GetFieldValueByName, which finds the reflected field of that name
 * (igMetaObject_FindFieldByName) and returns its value in this object. */
int Gap__Bec__ParticleInfo__vfunc_22(ParticleInfo *self, int name) {
    if (strcmp(name, self->_name) == 0) {
        return self->_sceneGraph;
    }
    return igObject_GetFieldValueByName(self, name);
}

void FUN_001d6410(TraversedNode *collector, TraversedNode *node, void *path) {
    unsigned count;
    unsigned i;
    int child;
    NodeList *children;
    if (node != 0) {
        if (igObject_IsKindOf(node, DAT_005619f8[0]) != 0) {
            children = node->children;
            count = 0;
            if (children != 0) {
                count = children->count;
            }
            for (i = 0; i < count; i++) {
                child = node->children->data[i];
                FUN_001c5870((void *)path, i);
                FUN_001d6410(collector, (TraversedNode *)child, path);
                FUN_001c58c0((T_1c58c0 *)path);
            }
        }
        if (igObject_IsKindOf(node, DAT_00561ea0[0]) != 0) {
            igSmartPointer<PathEntry> entry(((PathEntry *)FUN_0019f630(igObject_GetAllocator(collector))));
            FUN_001c5740((U_1c5740 *)entry.p, (T_1c5740 *)path);
            ObjectList_AppendRetained(collector->children, entry.p);
        }
    }
}

ObjectRefWord *FUN_001d6560(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void FUN_001d65e0(O_1d65e0 *self) {
    igObject *created = ((igObject *)FUN_0019f480(igObject_GetAllocator(self)));
    if (created != 0) {
        created->_refCount = created->_refCount + 1;
    }
    igObject *previous = self->f28;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->f28 = created;
    igObject *held = self->f28;
    held->_refCount = held->_refCount - 1;
    if ((held->_refCount & 0x7FFFFF) == 0) {
        igObject_Destroy(held);
    }
    igSmartPointer<igObject> second(((igObject *)FUN_0019f630(igObject_GetAllocator(self))));
    FUN_001c5730((int *)(second.get()), self->f20);
    FUN_001d6410((TraversedNode *)self, (TraversedNode *)self->f20, (void *)(second.get()));
}

void FUN_001d6700(ChildOwner *self) {
    igSmartPointer<ChildObject> created(FUN_002c72c0(igObject_GetAllocator(self)));
    FUN_002d8620(created.get(), self->f20, 0, 0);
    FUN_001d6790((OO_1d6790 *)self, (AA *)(created.get()));
}

void FUN_001d6790(OO_1d6790 *arg0, AA *arg1) {
    long long temp_v1;
    unsigned int temp_s3;
    unsigned int var_s2;
    long long temp_s1;
    long long var_s0;
    void *temp_s6;
    EE_1d6790 *temp_v0;

    arg0->f32 = 0;
    arg0->f40 = 0;
    temp_s3 = arg1->n;
    var_s2 = 0;
    while (var_s2 < temp_s3) {
        temp_v0 = FUN_002d7e90(arg1, var_s2);
        if (0 != igObject_IsKindOf(temp_v0, DAT_00585b70[0])) {
            temp_s6 = temp_v0->f24;
            if (igObject_IsKindOf(temp_s6, DAT_005611d0[0]) != 0) {
                temp_s1 = ((DW4VC_124_0_1d6790 *)(temp_s6))->vX();
                var_s0 = ((DW4VC_128_0 *)(temp_s6))->vX();
                if (igObject_IsKindOf(temp_s6, DAT_005611d8[0]) != 0) {
                    temp_v1 = temp_s1 + ((DW4VC_260_0 *)(temp_s6))->vX();
                    if (var_s0 < temp_v1) {
                        var_s0 = temp_v1;
                    }
                }
                if (temp_s1 < arg0->f32) {
                    arg0->f32 = temp_s1;
                }
                if (arg0->f40 < var_s0) {
                    arg0->f40 = var_s0;
                }
            }
        }
        var_s2++;
    }
}

int FUN_001d68e0(void) {
    return 0;
}

int FUN_001d68f0(void) {
    return 0;
}

int FUN_001d6900(Primitive **out) {
    float v[18];
    igSmartPointer<Primitive> quad(FUN_00137810(FUN_002f8a20()));
    VertexFormat format;
    int i;
    format.flags = 0;
    format.flags = 1 | format.flags;
    quad->configure(&format, 6, 0, 0);
    quad->setPrimitives(3, 2, 0);
    v[2] = 0.0f;
    v[0] = -1.0f;
    i = 0;
    v[1] = -1.0f;
    v[3] = 1.0f;
    v[4] = -1.0f;
    v[5] = 0.0f;
    v[6] = -1.0f;
    v[7] = 1.0f;
    v[8] = 0.0f;
    v[9] = 1.0f;
    v[10] = 1.0f;
    v[11] = 0.0f;
    v[12] = -1.0f;
    v[16] = -1.0f;
    v[13] = 1.0f;
    v[14] = 0.0f;
    v[15] = 1.0f;
    v[17] = 0.0f;
    do {
        quad->vertices->setPosition(i, &v[i * 3]);
        i += 1;
    } while (i < 6);
    *out = quad.p;
    Primitive *retained = *out;
    if (retained != 0) {
        retained->_refCount = retained->_refCount + 1;
    }
    return 0;
}

void FUN_001d6a70(void) {
  Ref_1d6a70 *scratch;
  Vec3x eye, origin, up;
  Vec4 white;
  Vec4 forward;
  Lens *lens, *tint;
  DAT_005628f0[0]->mode = 2;
  DAT_005628f0[0]->flag24 = 1;
  DAT_005628f0[0]->w20 = -1;
  DAT_005628f0[0]->w36 = 1;
  DAT_00562908[0]->select(0);
  DAT_00562908[0]->set(1);
  DAT_00562918[0]->select(1);
  DAT_00562918[0]->set(1);
  DAT_00562920[0]->select(2);
  DAT_00562920[0]->set(1);
  DAT_00562928[0]->select(3);
  DAT_00562928[0]->set(1);
  DAT_00562930[0]->select(4);
  DAT_00562930[0]->set(1);
  DAT_00562910[0]->select(0);
  DAT_00562910[0]->set(0);
  DAT_005628f8[0]->set(0);
  lens = DAT_00562900[0];
  lens->w48 = (long long)0x3ff00000 << 32;
  lens->w64 = 0x3f800000;
  DAT_00562900[0]->mode = 2;
  white.x = 1.0f; white.y = 1.0f; white.z = 1.0f; white.w = 1.0f;
  tint = DAT_00562940[0];
  tint->color = white;
  tint->w60 = FUN_001931b0(&white, 1, 0x3f800000, lens);
  DAT_00562940[0]->mode = 3;
  DAT_00562948[0]->set(5);
  DAT_00562948[0]->select(0);
  DAT_00562950[0]->set(1);
  DAT_00562950[0]->select(0);
  DAT_00562958[0]->set(1);
  DAT_00562958[0]->select(1);
  DAT_00562960[0]->set(1);
  DAT_00562960[0]->select(2);
  DAT_00562968[0]->set(1);
  DAT_00562968[0]->select(0);
  DAT_00562970[0]->set(1);
  DAT_00562970[0]->select(1);
  DAT_00562978[0]->set(1);
  DAT_00562978[0]->select(2);
  DAT_00562980[0]->set(0, 0, 0, 0);
  DAT_00562988[0]->set(0, 0, 0, 1);
  DAT_00562990[0]->set(1, 1, 1, 0);
  DAT_00562998[0]->set(0);
  DAT_005629e8[0]->set(1);
  DAT_005629f0[0]->set(4);
  DAT_005629f0[0]->set2(5);
  DAT_00562938[0]->mode = 2;
  DAT_00562938[0]->select(0);
  FUN_001d6900((Primitive * *)&scratch);
  {
    SceneList *list = DAT_005629a0[0]->items;
    int n = list->count;
    int m;
    int i;
    for (i = 0; i < n; i++) {
      Ref_1d6a70 *o = (Ref_1d6a70 *)list->data[i];
      if (o != 0) {
        o->refs = o->refs - 1;
        if (((unsigned long long)((long long)o->refs << 0x29) >> 0x29) == 0) igObject_Destroy(o);
      }
    }
    m = list->count;
    for (i = 0; i < m; i++) list->data[i] = 0;
    list->count = 0;
  }
  ObjectList_AppendRetained(DAT_005629a0[0]->items, scratch);
  FUN_00191860((char *)DAT_005629a8[0] + 12, -1.0f, 1.0f, -1.0f, 1.0f, -5.0f, 5.0f);
  up.x = 0.0f; up.y = 1.0f; up.z = 0.0f;
  origin.x = 0.0f; origin.y = 0.0f; origin.z = 0.0f;
  eye.x = 0.0f; eye.y = 0.0f; eye.z = 5.0f;
  FUN_00191b10((char *)DAT_005629b0[0] + 12, &eye, &origin, &up);
  {
    Ref_1d6a70 *o = scratch;
    if (o != 0) {
      o->refs = o->refs - 1;
      if (((unsigned long long)((long long)o->refs << 0x29) >> 0x29) == 0) igObject_Destroy(o);
    }
  }
  DAT_005629c0[0]->set(0);
  DAT_005629b8[0]->set(0);
  forward.x = 0.0f; forward.y = 0.0f; forward.z = 0.0f; forward.w = 1.0f;
  DAT_005629c8[0]->set(&forward);
  DAT_005629e0[0]->set(1);
  DAT_005629d8[0]->set3(2);
  DAT_005629d8[0]->set(0);
  DAT_005629d0[0]->set(1);
  DAT_005629d0[0]->set2(1);
}

void FUN_001d7120(ProjectiveShadowView *s) {
    bool missing = !(s->format != 0);
    if (missing != false) { s->format = 0; }
    s->f184->s23(1);
    ShadowRef_1d7120 none(0);
    s->f184->s31((int)none.p);
    s->f156->s23(0);
    s->f156->s31((int)s->texture);
    s->f160->s23(1);
    s->f160->s31((int)s->texture);
    s->f164->s23(2);
    s->f164->s31((int)s->texture);
    s->texState->mode = 3;
    { ShadowRefObj *v = s->image; s->texState->set_source(v); }
    { ShadowRefObj *v = s->texture; s->texState->set_target(v); }
    s->texState->f28 = 0;
    s->texState->f32 = 0;
    s->texState->f36 = 0;
    s->texState->f40 = 0;
    s->texState->set_image(((ShadowRefObj *)DAT_005628f0[0]));
    s->texState->width = s->width;
    s->texState->height = s->height;
    s->image->s26(s->width);
    s->image->s27(s->height);
    s->image->s28(DAT_004e4820[s->format]);
    s->texture->s30(0);
    s->texture->s31(0);
    s->texture->s32(0);
    s->texture->s33(0);
    FUN_00140ad0(s->texture, s->image, 0);
    ((ShadowTexState *)s->texture)->width = 3;
    if (FUN_00166d40() != 0) {
        ShadowStateObj *t = s->texture;
        t->s22(FUN_00166d40());
    }
    s->target->f24 = 1;
    s->target->f20 = -1;
    s->target->f36 = 2;
    s->target->f12 = 1;
    s->target->f16 = 0;
    { ShadowRefObj *v = s->texture; s->target->set_texture(v); }
    { int h = s->height; s->target->setSize(s->width, h); }
    s->target->f60 = 0;
    s->target->f56 = 16;
    s->target->f48 = 24;
    s->target->f52 = 8;
    { ShadowRefObj *v = s->target; s->holder->set_target(v); }
    s->f228->s30(1, 1, s->width - 2, s->height - 2, 0.0f, 1.0f);
    s->f176->s30(0, 0, s->width, s->height, 0.0f, 1.0f);
    ((ShadowFlagObj *)s->f100)->enabled = 1;
    ((ShadowFlagObj *)s->f104)->enabled = 1;
    s->f100->s23(0);
    s->f104->s23(0);
    FUN_001d7b10(s, s->f112);
}

void FUN_001d7630(void *arg0, float *arg1) {
    T_1d7630 *t = (T_1d7630 *)arg0;
    float m1[16];
    float m2[16];
    float m3[16];
    float m4[16];
    float v1[3];
    float v2[3];
    float v3[3];
    float *s2, *s0, *s4;
    float f20;
    Src_1d7630 *a = t->f192;
    if (a != 0) {
        t->p[0] = a->f116;
        t->p[1] = a->f120;
        t->p[2] = a->f124;
        Src_1d7630 *b = t->f192;
        t->q[0] = b->f128;
        t->q[1] = b->f132;
        t->q[2] = b->f136;
        t->f60 = t->f192->f96;
    }
    v1[0] = t->p[0] + t->q[0];
    v1[1] = t->p[1] + t->q[1];
    v1[2] = t->p[2] + t->q[2];
    FUN_00191b10(m1, t->p, v1, t->f72);
    if (t->f208 != 0) {
        FUN_00191860((void *)m2, t->f224, t->f220, t->f216, t->f212, t->f64, t->f68);
    } else {
        float f12 = 0.0174532924f * (2.0f * t->f60);
        FUN_001919d0((void *)m2, f12, f12, 1.0f, t->f64, t->f68);
    }
    t->f92->vX(m1);
    t->f96->vX(m2);
    s2 = (float *)(t->f100 + DAT_0055ece0[0]->f8);
    FUN_001908f0(s2, arg1);
    FUN_001904f0(s2, s2, m1);
    FUN_001904f0(s2, s2, m2);
    igMatrix44f_SetIdentity(m3);
    v2[0] = 0.5f; v2[2] = 0.0f; v2[1] = -0.5f;
    FUN_00190c60(m3, v2);
    v3[0] = 0.5f; v3[1] = 0.5f; v3[2] = 0.0f;
    FUN_00190a10(m3, v3);
    FUN_001904f0(s2, s2, m3);
    s0 = (float *)(t->f196 + DAT_0055ee30[0]->f8);
    s4 = (float *)(t->f200 + DAT_0055ee30[0]->f8);
    FUN_001908f0(s4, arg1);
    FUN_001904f0(s4, s4, m1);
    f20 = t->f68 - t->f64;
    FUN_001908f0(m4, DAT_004e0f30);
    m4[11] = 128.0f / f20;
    m4[15] = 128.0f + (128.0f * (t->f108 + t->f64)) / f20;
    FUN_001904f0(s4, s4, m4);
    m4[11] = -128.0f / f20;
    m4[15] = (128.0f * -t->f64) / f20;
    FUN_001908f0(s0, m4);
}

void FUN_001d7910(void) {
    void *metas[7];
    ShaderTraversalPairs pairs;
    int i;
    int count;
    int child;
    ShaderTraversalPair *p;
    int n;
    int j;
    void **m;
    FUN_00300c00(((void *)DAT_005628e0[0]), ((void *)DAT_00562640[0]), 1);
    FUN_00300c00(((void *)DAT_005628e8[0]), ((void *)DAT_00562640[0]), 1);
    clearBytes((char *)metas, 28);
    metas[0] = ((void *)DAT_005618d8[0]);
    metas[1] = ((void *)DAT_00561a98[0]);
    metas[2] = ((void *)DAT_00561860[0]);
    metas[3] = ((void *)DAT_00561e98[0]);
    metas[4] = ((void *)DAT_00561ee8[0]);
    metas[5] = ((void *)DAT_00561578[0]);
    metas[6] = ((void *)DAT_00561570);
    for (i = 0; i < 7; i++) {
        m = &metas[i];
        count = igMetaObject_CountTree(*m);
        for (child = 0; child < count; child++) {
            igTraversal_RegisterFunction((struct L_1e06c0 *)((void *)DAT_005628e0[0]), (struct X_1e06c0 *)(FUN_002fe300(*m, child)), igTraversal_TraverseChildren);
        }
    }
    pairs = DAT_0048dac0;
    pairs._pairs[0]._meta = ((void *)DAT_00561860[0]);
    pairs._pairs[1]._meta = ((void *)DAT_00561e98[0]);
    pairs._pairs[2]._meta = ((void *)DAT_00561ee8[0]);
    pairs._pairs[3]._meta = ((void *)DAT_00561a98[0]);
    for (i = 0; i < 4; i++) {
        p = &pairs._pairs[i];
        n = igMetaObject_CountTree(p->_meta);
        for (j = 0; j < n; j++) {
            igTraversal_RegisterFunction((struct L_1e06c0 *)((void *)DAT_005628e8[0]), (struct X_1e06c0 *)(FUN_002fe300(p->_meta, j)), p->_function);
        }
    }
}

void FUN_001d7b10(void *arg0, void *arg1) {
    float v[4];
    float *s = (float *)arg1;
    float *d = (float *)arg0;
    d[28] = s[0];
    d[29] = s[1];
    d[30] = s[2];
    d[31] = s[3];
    v[3] = s[3];
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    ((DW4VCSR_128_0 *)(*(void **)((char *)arg0 + 204)))->vX(v);
}

void FUN_001d7b70(S0_1d7b70 *arg0, S1_1d7b70 *arg1) {
    int var_s5;
    int var_s6;
    int temp_s5;
    int var_s3;
    int var_s5_2;
    L_1d7b70 *temp_v0_2;
    int var_s2;
    int temp_s2;
    TravFunctionTable *temp_s4;
    int temp_s3;
    int temp_s2_2;
    int temp_s5_2;
    TravFunctionTable *temp_s2_3;
    L_1d7b70 *temp_v0;

    if (arg0->b32 == 0) {
        FUN_001d6a70();
        FUN_001d7120((ProjectiveShadowView *)arg0);
        FUN_001d7910();
        arg0->b32 = 1;
    }
    FUN_001d7630((void *)arg0, (float *)((char *)arg1 + 164));
    temp_s4 = DAT_00562640[0];
    DAT_00562640[0] = DAT_005628e0[0];
    if (arg0->b140 != 0) {
        temp_s2 = arg1->f52;
        FUN_001dc500((A_1dc500 *)arg1->f68, 0, 1);
        FUN_001b12f0((igAttrStackManager *)temp_s2, (igAttr *)arg0->f148);
        FUN_001b12f0((igAttrStackManager *)temp_s2, (igAttr *)arg0->f176);
        FUN_001d9ac0((struct A_1d9ac0 *)arg1->f68, ((int *)DAT_00562940)[0], temp_s2);
        FUN_001b13d0((struct A_1b13d0 *)temp_s2, (struct B_1b13d0 *)arg0->f176);
        FUN_001b12f0((igAttrStackManager *)temp_s2, (igAttr *)((int *)DAT_005629d0)[0]);
        FUN_001b12f0((igAttrStackManager *)temp_s2, (igAttr *)((int *)DAT_005628f8)[0]);
        FUN_001b12f0((igAttrStackManager *)temp_s2, (igAttr *)((int *)DAT_00562910)[0]);
        FUN_001b12f0((igAttrStackManager *)temp_s2, (igAttr *)((int *)DAT_00562948)[0]);
        FUN_001b12f0((igAttrStackManager *)temp_s2, (igAttr *)arg0->f196);
        FUN_001b12f0((igAttrStackManager *)temp_s2, (igAttr *)((int *)DAT_00562998)[0]);
        FUN_001b1030((igAttrStackManager *)temp_s2, (igAttr *)arg0->f92);
        FUN_001b1030((igAttrStackManager *)temp_s2, (igAttr *)arg0->f96);
        FUN_001b1030((igAttrStackManager *)temp_s2, (igAttr *)arg0->f228);
        temp_s5 = arg0->f84->n;
        for (var_s3 = 0; var_s3 < temp_s5; var_s3++) {
            FUN_001e04c0((S_1e04c0 *)arg1, (V_1e04c0 *)arg0->f84->arr[var_s3]);
        }
        FUN_001b1100((struct A_1b1100 *)temp_s2, (struct B_1b1100 *)arg0->f228);
        FUN_001b1100((struct A_1b1100 *)temp_s2, (struct B_1b1100 *)arg0->f96);
        FUN_001b1100((struct A_1b1100 *)temp_s2, (struct B_1b1100 *)arg0->f92);
        FUN_001b13d0((struct A_1b13d0 *)temp_s2, (struct B_1b13d0 *)((int *)DAT_00562998)[0]);
        FUN_001b13d0((struct A_1b13d0 *)temp_s2, (struct B_1b13d0 *)arg0->f196);
        FUN_001b13d0((struct A_1b13d0 *)temp_s2, (struct B_1b13d0 *)((int *)DAT_00562948)[0]);
        FUN_001b13d0((struct A_1b13d0 *)temp_s2, (struct B_1b13d0 *)((int *)DAT_00562910)[0]);
        FUN_001b13d0((struct A_1b13d0 *)temp_s2, (struct B_1b13d0 *)((int *)DAT_005628f8)[0]);
        FUN_001b13d0((struct A_1b13d0 *)temp_s2, (struct B_1b13d0 *)((int *)DAT_005629d0)[0]);
        FUN_001b13d0((struct A_1b13d0 *)temp_s2, (struct B_1b13d0 *)arg0->f148);
        FUN_001dc610(arg1->f68);
    }
    DAT_00562640[0] = DAT_005628e8[0];
    temp_s3 = arg1->f52;
    FUN_001dc500((A_1dc500 *)arg1->f68, 0, 0);
    temp_v0 = arg0->f28;
    var_s5 = 0;
    if (temp_v0 != 0) {
        var_s5 = temp_v0->n;
    }
    for (var_s2 = 0; var_s2 < var_s5; var_s2++) {
        FUN_001e04c0((S_1e04c0 *)arg1, (V_1e04c0 *)arg0->f28->arr[var_s2]);
    }
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)((int *)DAT_00562998)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)((int *)DAT_005629c0)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)((int *)DAT_005628f8)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)((int *)DAT_00562988)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)((int *)DAT_005629c8)[0]);
    temp_s2_2 = arg1->f52;
    FUN_001b12f0((igAttrStackManager *)temp_s2_2, (igAttr *)((int *)DAT_005629a8)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s2_2, (igAttr *)((int *)DAT_005629b0)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s2_2, (igAttr *)((int *)DAT_005629b8)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s2_2, (igAttr *)((int *)DAT_00562910)[0]);
    FUN_001db720(arg1->f68, ((int *)DAT_005629a0)[0], temp_s2_2);
    FUN_001b13d0((struct A_1b13d0 *)temp_s2_2, (struct B_1b13d0 *)((int *)DAT_00562910)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s2_2, (struct B_1b13d0 *)((int *)DAT_005629b8)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s2_2, (struct B_1b13d0 *)((int *)DAT_005629b0)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s2_2, (struct B_1b13d0 *)((int *)DAT_005629a8)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)((int *)DAT_005629c8)[0]);
    temp_s2_3 = DAT_00562640[0];
    DAT_00562640[0] = DAT_005628e0[0];
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)((int *)DAT_00562908)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)((int *)DAT_00562938)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)arg0->f156);
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)((int *)DAT_00562948)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)arg0->f100);
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)((int *)DAT_00562968)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)arg0->f200);
    temp_v0_2 = arg0->f28;
    var_s6 = 0;
    if (temp_v0_2 != 0) {
        var_s6 = temp_v0_2->n;
    }
    for (var_s5_2 = 0; var_s5_2 < var_s6; var_s5_2++) {
        FUN_001e04c0((S_1e04c0 *)arg1, (V_1e04c0 *)arg0->f28->arr[var_s5_2]);
    }
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)arg0->f200);
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)((int *)DAT_00562968)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)arg0->f100);
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)((int *)DAT_00562948)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)arg0->f156);
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)((int *)DAT_00562938)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)((int *)DAT_00562908)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)((int *)DAT_00562988)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)((int *)DAT_00562990)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)((int *)DAT_005629e0)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)((int *)DAT_005629d8)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)arg0->f204);
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)((int *)DAT_005629e8)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s3, (igAttr *)((int *)DAT_005629f0)[0]);
    temp_s5_2 = arg1->f52;
    FUN_001b12f0((igAttrStackManager *)temp_s5_2, (igAttr *)((int *)DAT_005629a8)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s5_2, (igAttr *)((int *)DAT_005629b0)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s5_2, (igAttr *)((int *)DAT_005629b8)[0]);
    FUN_001b12f0((igAttrStackManager *)temp_s5_2, (igAttr *)((int *)DAT_00562910)[0]);
    FUN_001db720(arg1->f68, ((int *)DAT_005629a0)[0], temp_s5_2);
    FUN_001b13d0((struct A_1b13d0 *)temp_s5_2, (struct B_1b13d0 *)((int *)DAT_00562910)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s5_2, (struct B_1b13d0 *)((int *)DAT_005629b8)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s5_2, (struct B_1b13d0 *)((int *)DAT_005629b0)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s5_2, (struct B_1b13d0 *)((int *)DAT_005629a8)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)((int *)DAT_005629f0)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)((int *)DAT_005629e8)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)arg0->f204);
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)((int *)DAT_005629d8)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)((int *)DAT_005629e0)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)((int *)DAT_00562990)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)((int *)DAT_005628f8)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)((int *)DAT_00562998)[0]);
    FUN_001b13d0((struct A_1b13d0 *)temp_s3, (struct B_1b13d0 *)((int *)DAT_005629c0)[0]);
    DAT_00562640[0] = temp_s2_3;
    FUN_001dc610(arg1->f68);
    DAT_00562640[0] = temp_s4;
}

int FUN_001d81e0(void) {
    int temp_s0;

    if (DAT_0048dae0[0] == -1) {
        temp_s0 = *(int *)((char *)DAT_00586dc8[0] + 56);
        FUN_003065f0(temp_s0, 7, &DAT_004e4830[0], &DAT_0048dae0[0], 0x100, 1);
        FUN_00306e50(temp_s0, 7, &DAT_004e4850[0], &GPR_00554b9c, 0, 1);
    }
    return DAT_0048dae0[0];
}

int FUN_001d8270(int arg0) {
    if (arg0 == DAT_0055f088[0]) {
        return 1;
    }
    if (arg0 == ((int *)DAT_0055f060)[0]) {
        return FUN_001d81e0();
    }
    return 0;
}

int FUN_001d82c0(void *arg0, int arg1, int arg2) {
    return *(int *)(*(int *)((char *)((*(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 32)) + 16) + (arg1 * 4)))) + 16) + (arg2 * 4));
}

int FUN_001d82f0(void *arg0, int arg1) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 44)) + 16) + (arg1 << 6);
}

int FUN_001d8310(void *arg0, int arg1) {
    return *(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 48)) + 16) + (arg1 * 4));
}

int FUN_001d8330(void *arg0, unsigned int arg1) {
    return ((1 << (arg1 & 0x1F)) & *(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 52)) + 16) + ((arg1 >> 5) * 4))) != 0;
}

