igMetaObject *FUN_0019dbb0(void) {
    if (g_igLightSet_metaObject[0] == 0) {
        g_igLightSet_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igLightSet_metaObject[0];
}

igMetaObject *igLightSet_GetMetaObject(void)
{
    igMetaObject *g = g_igLightSet_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019dcd0();
    return g_igLightSet_metaObject[0];
}

int igLightSet_GetVTable(void) {
    struct Obj_19dc50 o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f12 = 0;
    o.f16 = 0;
    o.vt = &DAT_00528c60[0];
    o.f28 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_00528c60[0];
    FUN_0019c1a0((ObjectRefWord *)&o.f28, -1);
    FUN_00195970((struct T_195970 *)&o, 0);
    return r;
}

void FUN_0019dcd0(void)
{
    igMetaObject_RunStaticInit(igLightSet_Register);
}

void igLightSet_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igLightSet_metaObject),
        igNode_Register,
        igNode_GetPublishedMetaObject,
        thunk_igLightSet_GetMetaObject,
        igLightSet_className,
        0x20, /* instance size */
        igLightSet_GetVTable,
        &igLightSet_InitFields,
        0, /* extra callback item */
        g_igLightSet_callbackList /* callback list */
    );
}

void thunk_igLightSet_GetMetaObject(void) {
    igLightSet_GetMetaObject();
}

igMetaObject *FUN_0019dd70(void) {
    return g_igNode_metaObject[0];
}

void igLightSet_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igLightSet_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igLightSet_ctorTable[0], 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001365e0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    ((igMetaField *)temp_s1)->_deepCopyMethod = 0;
    ((igMetaField *)temp_s1)->_shallowCopyMethod = 2;
    igMetaObject_NameFields(temp_s0, &g_igLightSet_fieldTable[0], &DAT_0048bdd0[0], &DAT_0048bdd8[0], temp_s2);
}

igMetaObject *FUN_0019de30(void) {
    return g_igTransform_metaObject[0];
}

igMetaObject *FUN_0019de40(void) {
    return g_igAnimationSequence_metaObject[0];
}

void **FUN_0019de50(struct Ref **self, short flag) {
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

void **FUN_0019ded0(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

O *FUN_0019df50(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

