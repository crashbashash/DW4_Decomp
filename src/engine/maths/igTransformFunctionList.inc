OpTable *FUN_00188d40(int arg0) {
    FUN_00188e10();
    return (OpTable *)igMetaObject_CreateInstance(*(int *)0x561030, arg0);
}

igMetaObject *igTransformFunctionList_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformFunctionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00188e10();
    return g_igTransformFunctionList_metaObject[0];
}

int igTransformFunctionList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00527d30[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00188e10(void)
{
    igMetaObject_RunStaticInit(igTransformFunctionList_Register);
}

void igTransformFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTransformFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igTransformFunctionList_GetMetaObject,
        igTransformFunctionList_className,
        0x14, /* instance size */
        igTransformFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTransformFunctionList_GetMetaObject(void) {
    igTransformFunctionList_GetMetaObject();
}

