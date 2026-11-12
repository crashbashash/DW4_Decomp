void FUN_00363e80(int arg0) {
    FUN_00363fa0();
    igMetaObject_CreateInstance(*(int *)0x589838, arg0);
}

igMetaObject *FUN_00363ec0(void) {
    if (g_beDataObjListList_metaObject[0] == 0) {
        g_beDataObjListList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beDataObjListList_metaObject[0];
}

igMetaObject *FUN_00363f10(void) {
    igMetaObject *g = g_beDataObjListList_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_00363fa0();
done:
    return g_beDataObjListList_metaObject[0];
}

int beDataObjListList_GetVTable(void) {
    Obj_363f60 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_005355a0[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00363fa0(void)
{
    igMetaObject_RunStaticInit(beDataObjListList_Register);
}

void *beDataObjListList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beDataObjListList_GetMetaObject,
        beDataObjListList_className,
        0x14, /* instance size */
        beDataObjListList_GetVTable,
        0,
        0, /* extra callback item */
        pA6 /* callback list */
    );
}

void beDataObjListList_GetMetaObject(void)
{
    FUN_00363f10();
}

