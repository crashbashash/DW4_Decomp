int FUN_001a7440(void) {
    if (DAT_005621f8[0] == 0) {
        DAT_005621f8[0] = igMetaEnum_Create(&ModifierType[0], &DAT_0048d190[0], &DAT_0048d1a0[0], 4);
    }
    return DAT_005621f8[0];
}

igMetaObject *igAnimationModifier_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationModifier_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a7600();
    return g_igAnimationModifier_metaObject[0];
}

int igAnimationModifier_GetVTable(void) {
    struct Obj_1a74f0 obj;
    char *o;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00529ee0[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00529ee0[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
    }
    return t;
}

O *FUN_001a7580(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

void FUN_001a7600(void)
{
    igMetaObject_RunStaticInit(igAnimationModifier_Register);
}

void igAnimationModifier_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationModifier_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationModifier_GetMetaObject,
        igAnimationModifier_className,
        0x14, /* instance size */
        igAnimationModifier_GetVTable,
        &igAnimationModifier_InitFields,
        0, /* extra callback item */
        g_igAnimationModifier_callbackList /* callback list */
    );
}

void thunk_igAnimationModifier_GetMetaObject(void) {
    igAnimationModifier_GetMetaObject();
}

void igAnimationModifier_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationModifier_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igAnimationModifier_ctorTable[0], 3);
    FUN_002ea4b0(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)), -1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00196190();
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2)));
    FUN_002dc7a0(temp_v0, &DAT_0048d1f8[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(FUN_001a7440);
    igMetaObject_NameFields(temp_s0, &g_igAnimationModifier_fieldTable[0], &DAT_0048d1d8[0], &DAT_0048d1e8[0], temp_s2);
}

