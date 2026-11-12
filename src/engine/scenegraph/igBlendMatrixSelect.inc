igMetaObject *igBlendMatrixSelect_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendMatrixSelect_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a4c50();
    return g_igBlendMatrixSelect_metaObject[0];
}

int igBlendMatrixSelect_GetVTable(void) { struct Obj_1a4ba0 o; int *p = (int *)&o; int *q; int t;
 igObject_InitHeader((struct Obj_1a4ba0 *)p); o.vt = &DAT_0052a400[0]; o.f8 = 0; o.f12 = 0; o.f16 = 0; o.f28 = 0; o.f32 = 0; q = &o.f40; *q = 0;
 igMatrix44f_SetIdentity(o.sub1); igMatrix44f_SetIdentity(p + 27);
 t = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
 o.vt = &DAT_0052a400[0]; ObjectRef_Destruct_00150eb0(q, -1); p = (int*)&o; FUN_0019c0e0((struct S_19c0e0 *)((struct Obj_1a4ba0 *)p), 0); return t; }

void FUN_001a4c50(void)
{
    igMetaObject_RunStaticInit(igBlendMatrixSelect_Register);
}

void igBlendMatrixSelect_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igBlendMatrixSelect_metaObject),
        igAttrSet_Register,
        igAttrSet_GetPublishedMetaObject,
        thunk_igBlendMatrixSelect_GetMetaObject,
        igBlendMatrixSelect_className,
        0xAC, /* instance size */
        igBlendMatrixSelect_GetVTable,
        &igBlendMatrixSelect_InitFields,
        0, /* extra callback item */
        g_igBlendMatrixSelect_callbackList /* callback list */
    );
}

void thunk_igBlendMatrixSelect_GetMetaObject(void) {
    igBlendMatrixSelect_GetMetaObject();
}

void igBlendMatrixSelect_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igBlendMatrixSelect_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048cb58[0], 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_0048cb68[0], &DAT_0048cb78[0], &DAT_0048cb88[0], temp_s2);
}

