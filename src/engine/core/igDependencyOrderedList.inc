igMetaObject *igDependencyOrderedList_GetMetaObject(void)
{
    igMetaObject *g = g_igDependencyOrderedList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c7ba0();
    return g_igDependencyOrderedList_metaObject[0];
}

int igDependencyOrderedList_GetVTable(void) {
    igDependencyOrderedList list;
    int t;
    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_0052cc20[0];
    list._objectList = 0;
    list._dependencies = 0;
    list._order = 0;
    list._checkPoints = 0;
    t = *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    list._vtable = (int)&DAT_0052cc20[0];
    ObjectRef_Destruct_001c6460(&list._checkPoints, -1);
    FUN_00135430(&list._order, -1);
    FUN_00233590(&list._dependencies, -1);
    FUN_0014aa70(&list._objectList, -1);
    return t;
}

void FUN_002c7ba0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDependencyOrderedList_Register);
}

void igDependencyOrderedList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igDependencyOrderedList_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDependencyOrderedList_GetMetaObject,
        igDependencyOrderedList_className,
        0x1C, /* instance size */
        igDependencyOrderedList_GetVTable,
        &igDependencyOrderedList_InitFields,
        0, /* extra callback item */
        g_igDependencyOrderedList_callbackList /* callback list */
    );
}

void thunk_igDependencyOrderedList_GetMetaObject(void) {
    igDependencyOrderedList_GetMetaObject();
}

void igDependencyOrderedList_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)g_igDependencyOrderedList_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, (igMetaField * (**)(void *))&g_igDependencyOrderedList_ctorTable[0], 5);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_002c7d40();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_002c9170();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_002b9120();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, (const char **)&g_igDependencyOrderedList_fieldTable[0], (igMetaField ***)&DAT_004c1340[0], &DAT_004c1360[0], temp_s0);
}

