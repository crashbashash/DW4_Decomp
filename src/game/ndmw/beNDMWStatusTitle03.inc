void FUN_003b36f0(int arg0) {
    FUN_003b3850();
    igMetaObject_CreateInstance(*(int *)0x58AB58, arg0);
}

igMetaObject *FUN_003b3730(void) {
    if (g_beNDMWStatusTitle03_metaObject[0] == 0) {
        g_beNDMWStatusTitle03_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWStatusTitle03_metaObject[0];
}

void *FUN_003b3780(void) {
    igMetaObject *g = g_beNDMWStatusTitle03_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b3850();
    }
    return g_beNDMWStatusTitle03_metaObject[0];
}

int beNDMWStatusTitle03_GetVTable(void) {
    struct Obj_3b37d0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.vt = &DAT_0053f5d0[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053f5d0[0];
    FUN_003b3030((int **)&obj, (long long)0);
    return t;
}

void FUN_003b3850(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle03_Register);
}

void *beNDMWStatusTitle03_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusTitle03_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWStatusTitle03_GetMetaObject,
        beNDMWStatusTitle03_className,
        0x50, /* instance size */
        beNDMWStatusTitle03_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusTitle03_GetMetaObject(void)
{
    FUN_003b3780();
}

