void FUN_0019fde0(int arg0) {
    FUN_001a1170();
    igMetaObject_CreateInstance(*(int *)0x561A50, arg0);
}

igMetaObject *igFrustCullTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igFrustCullTraversal_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a1170();
    return g_igFrustCullTraversal_metaObject[0];
}

int igFrustCullTraversal_GetVTable(void) {
    struct S_19fde0 s; char *p;
    int r;
    p = (char *)&s; FUN_001a10a0((igCommonTraversal *)p);
    s.vt = &DAT_00528f10[0];
    FUN_001a1090(&s.a);
    FUN_001510a0(s.b);
    FUN_001a1080((int *)(p + 548));
    r = *(int *)((char *)&s + *(int *)((char *)(g_objectSystem[0]) + 916));
    s.vt = &DAT_00528f10[0];
    FUN_001a1000((void **)&s.c, -1);
    FUN_00198190((void * *)&s.a, -1);
    FUN_001a0910((Obj_19fde0 *)&s, 0);
    return r;
}

struct R **FUN_0019ff10(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

struct T_19fde0 **FUN_0019ff90(struct T_19fde0 **arg0, short arg1) {
    struct T_19fde0 *o;
    if (arg0 != 0) {
        o = *arg0;
        if (o != 0) {
            o->refs = o->refs - 1;
            if ((o->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_001a0010(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_001a0090(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_001a0110(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void **FUN_001a0190(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

O *FUN_001a0210(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

void **FUN_001a0290(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_001a0310(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_001a0390(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void **FUN_001a0410(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_001a0490(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

ObjectRefWord *FUN_001a0590(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void **FUN_001a0610(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_001a0690(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_001a0710(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void **FUN_001a0790(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

O *FUN_001a0810(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

ObjectRefWord *FUN_001a0890(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

Obj_19fde0 *FUN_001a0910(Obj_19fde0 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = DAT_005293c0;
        arg0->rel(&arg0->m336);
        arg0->rel(&arg0->m268);
        arg0->rel(&arg0->m264);
        arg0->rel(&arg0->m260);
        arg0->rel(&arg0->m256);
        arg0->rel(&arg0->m252);
        arg0->rel(&arg0->m248);
        arg0->rel(&arg0->m244);
        arg0->rel(&arg0->m240);
        arg0->rel(&arg0->m236);
        arg0->rel(&arg0->m232);
        arg0->rel(&arg0->m96);
        arg0->rel(&arg0->m92);
        arg0->rel(&arg0->m88);
        arg0->rel(&arg0->m84);
        arg0->rel(&arg0->m80);
        arg0->rel(&arg0->m76);
        arg0->rel(&arg0->m72);
        arg0->rel(&arg0->m68);
        arg0->rel(&arg0->m64);
        arg0->rel(&arg0->m60);
        arg0->rel(&arg0->m56);
        arg0->rel(&arg0->m52);
        arg0->rel(&arg0->m36);
        arg0->rel(&arg0->m32);
        if (arg0) {
            arg0->vt = DAT_00528250;
            arg0->rel(&arg0->m28);
        }
        if (arg1 > 0) {
            thunk_Memory_FreeBuffer(arg0);
        }
    }
    return arg0;
}

void **FUN_001a1000(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

int *FUN_001a1080(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_001a1090(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void *FUN_001a10a0(igCommonTraversal *arg0) {
    igObject_InitHeader();
    arg0->_vtable = (int)(&DAT_00528250[0]);
    arg0->_travProcs = 0;
    arg0->_vtable = (int)(&DAT_005293c0[0]);
    arg0->_capabilityManager = 0;
    arg0->_defaultManager = 0;
    arg0->_attrStack = 0;
    arg0->_transformStack = 0;
    arg0->_vc = 0;
    arg0->_flushedAttrs = 0;
    arg0->_sorter = 0;
    arg0->_matrixPool = 0;
    arg0->_timePool = 0;
    arg0->_blendMatrixPool = 0;
    arg0->_texMatPool = 0;
    arg0->_vertexBlendMatListPool = 0;
    arg0->_matrixObjectPool = 0;
    arg0->_projectionMatrixPool = 0;
    igMatrix44f_SetIdentity((char *)arg0 + 0x64);
    igMatrix44f_SetIdentity((char *)arg0 + 0xA4);
    arg0->_matrixOptimization = 0;
    arg0->_normalizeNormalsEnable = 0;
    arg0->_timeStack = 0;
    arg0->_matrixObjectList = 0;
    arg0->_boneMatrixPaletteList = 0;
    arg0->_blendMatrixPaletteList = 0;
    arg0->_blendMatrixPaletteLengths = 0;
    arg0->_segmentOverrideNames = 0;
    arg0->_segmentOverrideStacks = 0;
    arg0->_blendMatricesAttrPool = 0;
    igMatrix44f_SetIdentity((char *)arg0 + 0x110);
    arg0->_defaultTimeAttr = 0;
    igMatrix44f_SetIdentity((char *)arg0 + 0x158);
    igMatrix44f_SetIdentity((char *)arg0 + 0x198);
    return arg0;
}

void FUN_001a1170(void)
{
    igMetaObject_RunStaticInit(igFrustCullTraversal_Register);
}

void igFrustCullTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFrustCullTraversal_metaObject,
        igCommonTraversal_Register,
        FUN_001a1210,
        thunk_igFrustCullTraversal_GetMetaObject,
        igFrustCullTraversal_className,
        0x230, /* instance size */
        igFrustCullTraversal_GetVTable,
        &igFrustCullTraversal_InitFields,
        &FUN_001a13a0, /* extra callback item */
        g_igFrustCullTraversal_callbackList /* callback list */
    );
}

void thunk_igFrustCullTraversal_GetMetaObject(void) {
    igFrustCullTraversal_GetMetaObject();
}

igMetaObject *FUN_001a1210(void) {
    return g_igCommonTraversal_metaObject[0];
}

void igFrustCullTraversal_InitFields(void) {
    void *temp_s2_3;
    void *temp_s2_2;
    void *temp_s2;
    void *temp_s1;
    int temp_s0;
    struct M_19fde0 o1;
    struct V o2;
    struct V o3;
    struct V o4;
    struct V o5;

    temp_s1 = (void *)g_igFrustCullTraversal_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igFrustCullTraversal_ctorTable[0], 7);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0)));
    o5.x = 0;
    o5.y = 0;
    o5.z = 0;
    o5.w = 0x3F800000;
    o4.x = 0;
    o4.y = 0;
    o4.z = 0x3F800000;
    o4.w = 0;
    o3.x = 0;
    o3.y = 0x3F800000;
    o3.z = 0;
    o3.w = 0;
    o2.x = 0x3F800000;
    o2.y = 0;
    o2.z = 0;
    o2.w = 0;
    FUN_00130e90(&o1, &o2, &o3, &o4, &o5);
    FUN_0018c640(temp_s2, &o1);
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00139170();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    igFloatMetaField_SetDefault(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4)), 1.0f);
    igFloatMetaField_SetDefault(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5)), 2.0f);
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0018a6a0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &g_igFrustCullTraversal_fieldTable[0], &DAT_0048c0d0[0], &DAT_0048c0f0[0], temp_s0);
    igMetaObject_AddExitCallback(&thunk_FUN_001c45d0);
}

void FUN_001a13a0(void) {
    FUN_001c45a0();
    igMetaObject_AddRegistrationCallback((int *)FUN_001c4590);
}

void thunk_FUN_001c45d0(void) {
    FUN_001c45d0();
}

