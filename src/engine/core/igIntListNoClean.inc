void * FUN_002ca8b0(int arg0) {
    FUN_002ca9d0();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586878), (MemoryPool *)arg0));
}

igMetaObject *FUN_002ca8f0(void) {
    if (g_igIntListNoClean_metaObject[0] == 0) {
        g_igIntListNoClean_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    }
    return g_igIntListNoClean_metaObject[0];
}

igMetaObject *igIntListNoClean_GetMetaObject(void)
{
    igMetaObject *g = g_igIntListNoClean_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002ca9d0();
    return g_igIntListNoClean_metaObject[0];
}

int igIntListNoClean_GetVTable(void) {
    struct Obj_2ca990 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00531b10[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002ca9d0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igIntListNoClean_Register);
}

void igIntListNoClean_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igIntListNoClean_metaObject),
        igIntList_Register,
        igIntList_GetPublishedMetaObject,
        thunk_igIntListNoClean_GetMetaObject,
        igIntListNoClean_className,
        0x14, /* instance size */
        igIntListNoClean_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igIntListNoClean_GetMetaObject(void) {
    igIntListNoClean_GetMetaObject();
}

