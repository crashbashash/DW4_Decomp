igMetaObject *igTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igTraversal_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00194530();
    return g_igTraversal_metaObject[0];
}

int igTraversal_GetVTable(void) {
    struct Obj o;
    struct R *t;
    int r;
    igObject_InitHeader(&o);
    o.vt = &DAT_00528250[0];
    o.p = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_00528250[0];
    if (&o.p != 0) {
        t = o.p;
        if (t != 0) {
            t->rc = t->rc - 1;
            if ((t->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    return r;
}

void *FUN_00194490(struct S *arg0, short arg1) {
    void *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_00528250[0];
        if (&arg0->f1c) {
            p = arg0->f1c;
            if (p != 0) {
                rc = *(int *)((char *)(p) + 4) - 1;
                *(int *)((char *)(p) + 4) = rc;
                if (((unsigned long long) ((long long) *(int *)((char *)(p) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((void *)p);
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void FUN_00194530(void)
{
    igMetaObject_RunStaticInit(igTraversal_Register);
}

void igTraversal_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igTraversal_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igTraversal_GetMetaObject,
        igTraversal_className,
        0x20, /* instance size */
        igTraversal_GetVTable,
        &igTraversal_InitFields,
        &FUN_00194690, /* extra callback item */
        g_igTraversal_callbackList /* callback list */
    );
}

void thunk_igTraversal_GetMetaObject(void) {
    igTraversal_GetMetaObject();
}

void igTraversal_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igTraversal_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048af10[0], 5);
    FUN_002ebc00(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2)), -1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4)));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_0019a720();
    igMetaObject_NameFields(temp_s0, &DAT_0048af30[0], &DAT_0048af50[0], &DAT_0048af70[0], temp_s2);
    FUN_002fe480(&thunk_FUN_001e0470);
}

void FUN_00194690(void) {
    FUN_001e0410();
    FUN_002fe490((int *)FUN_001e02e0);
}

void thunk_FUN_001e0470(void) {
    FUN_001e0470();
}

