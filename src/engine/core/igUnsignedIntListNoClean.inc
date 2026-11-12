void * FUN_002ca260(int arg0) {
    FUN_002ca380();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586850), (MemoryPool *)arg0));
}

igMetaObject *FUN_002ca2a0(void) {
    if (g_igUnsignedIntListNoClean_metaObject[0] == 0) {
        g_igUnsignedIntListNoClean_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    }
    return g_igUnsignedIntListNoClean_metaObject[0];
}

igMetaObject *igUnsignedIntListNoClean_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedIntListNoClean_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002ca380();
    return g_igUnsignedIntListNoClean_metaObject[0];
}

int igUnsignedIntListNoClean_GetVTable(void) {
    struct Obj_2ca340 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00531c30[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002ca380(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedIntListNoClean_Register);
}

void igUnsignedIntListNoClean_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedIntListNoClean_metaObject),
        igUnsignedIntList_Register,
        igUnsignedIntList_GetPublishedMetaObject,
        thunk_igUnsignedIntListNoClean_GetMetaObject,
        igUnsignedIntListNoClean_className,
        0x14, /* instance size */
        igUnsignedIntListNoClean_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igUnsignedIntListNoClean_GetMetaObject(void) {
    igUnsignedIntListNoClean_GetMetaObject();
}

