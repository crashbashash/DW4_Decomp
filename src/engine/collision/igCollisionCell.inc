igCollisionCell *FUN_0023a6e0(int arg0) {
    FUN_0023a850();
    return (igCollisionCell *)igMetaObject_CreateInstance(*(int *)0x56DDC8, arg0);
}

igMetaObject *igCollisionCell_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionCell_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0023a850();
    return g_igCollisionCell_metaObject[0];
}

int igCollisionCell_GetVTable(void) {
    Obj_23a770 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052d290[0];
    obj.r1 = 0;
    obj.r3 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0052d290[0];
    obj.rel3();
    obj.rel1();
    return r;
}

void FUN_0023a850(void)
{
    igMetaObject_RunStaticInit(igCollisionCell_Register);
}

void igCollisionCell_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionCell_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCollisionCell_GetMetaObject,
        igCollisionCell_className,
        0x20, /* instance size */
        igCollisionCell_GetVTable,
        &igCollisionCell_InitFields,
        0, /* extra callback item */
        g_igCollisionCell_callbackList /* callback list */
    );
}

void thunk_igCollisionCell_GetMetaObject(void) {
    igCollisionCell_GetMetaObject();
}

void igCollisionCell_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igCollisionCell_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igCollisionCell_ctorTable[0], 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00239a40();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0023a080();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0018a6a0();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_igCollisionCell_fieldTable[0], &DAT_004985e0[0], &DAT_00498600[0], temp_s2);
}

