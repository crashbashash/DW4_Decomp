igMetaObject *FUN_0019dfd0(void) {
    if (g_igIntersectTraversal_metaObject[0] == 0) {
        g_igIntersectTraversal_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igIntersectTraversal_metaObject[0];
}

igMetaObject *igIntersectTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igIntersectTraversal_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019e440();
    return g_igIntersectTraversal_metaObject[0];
}

int igIntersectTraversal_GetVTable(void) {
    struct Obj_19e070 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w[6] = 0;
    obj.vt = &DAT_00528cf0[0];
    obj.w[7] = 0;
    obj.w[8] = 0;
    obj.w[9] = 0;
    obj.w[12] = 0;
    obj.w[13] = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00528cf0[0];
    FUN_0019e3c0((void * *)&obj.w[13], -1);
    FUN_0018fa00(&obj.w[12], -1);
    FUN_0019e340((void * *)&obj.w[9], -1);
    FUN_001958f0((void * *)&obj.w[8], -1);
    FUN_00150fb0(&obj.w[7], -1);
    FUN_00194490((struct S *)((int *)&obj), 0);
    return t;
}

O_19e150 *FUN_0019e150(O_19e150 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &DAT_00528cf0[0];
        if (&arg0->m56) {
            S1 *t = arg0->m56;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m52) {
            S1 *t = arg0->m52;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m40) {
            S1 *t = arg0->m40;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m36) {
            S1 *t = arg0->m36;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (&arg0->m32) {
            S1 *t = arg0->m32;
            if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        }
        if (arg0) {
            arg0->vt = &DAT_00528250[0];
            if (&arg0->m28) {
                S1 *t = arg0->m28;
                if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
            }
        }
        if (arg1 > 0) thunk_FUN_002ed460__002ff810(arg0);
    }
    return arg0;
}

void **FUN_0019e340(void **arg0, short arg1) {
    S_temp_a0_19e340 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_19e340 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_0019e3c0(void **arg0, short arg1) {
    S_temp_a0_19e3c0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_19e3c0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_0019e440(void)
{
    igMetaObject_RunStaticInit(igIntersectTraversal_Register);
}

void igIntersectTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igIntersectTraversal_metaObject),
        igTraversal_Register,
        igTraversal_GetPublishedMetaObject,
        thunk_igIntersectTraversal_GetMetaObject,
        igIntersectTraversal_className,
        0x40, /* instance size */
        igIntersectTraversal_GetVTable,
        &igIntersectTraversal_InitFields,
        &FUN_0019e640, /* extra callback item */
        g_igIntersectTraversal_callbackList /* callback list */
    );
}

void thunk_igIntersectTraversal_GetMetaObject(void) {
    igIntersectTraversal_GetMetaObject();
}

igMetaObject *FUN_0019e4e0(void) {
    return g_igTraversal_metaObject[0];
}

void igIntersectTraversal_InitFields(void) {
    void *temp_s1;
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;

    temp_s1 = (void *)g_igIntersectTraversal_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_0048be00[0], 7);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_001e4740();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_0019cbe0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_0019e6c0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    FUN_002ea4b0(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3)), 5);
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt(temp_s1, 4 + temp_s0))))->_persistent = 0;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00186c40();
    ((igMetaField *)temp_s2_4)->_persistent = 0;
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00188260();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    ((igMetaField *)temp_s2_5)->_persistent = 0;
    igMetaObject_NameFields(temp_s1, &DAT_0048be20[0], &DAT_0048be40[0], &DAT_0048be60[0], temp_s0);
    FUN_002fe480(&thunk_FUN_001ce740);
}

void FUN_0019e640(void) {
    FUN_001ce710();
    FUN_002fe490(FUN_001ce660);
}

void thunk_FUN_001ce740(void) {
    FUN_001ce740();
}

