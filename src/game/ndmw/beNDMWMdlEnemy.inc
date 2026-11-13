void beNDMWMdlEnemy_CreateInstance(int arg0) {
    FUN_003c1860();
    igMetaObject_CreateInstance(*(int *)0x58B508, arg0);
}

igMetaObject *FUN_003c1760(void) {
    if (g_beNDMWMdlEnemy_metaObject[0] == 0) {
        g_beNDMWMdlEnemy_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMdlEnemy_metaObject[0];
}

igMetaObject *beNDMWMdlEnemy_GetReadyMetaObject(void) {
    if (g_beNDMWMdlEnemy_metaObject[0] == 0 || !isValid(g_beNDMWMdlEnemy_metaObject[0])) FUN_003c1860();
    return g_beNDMWMdlEnemy_metaObject[0];
}

int beNDMWMdlEnemy_GetVTable(void) {
    struct Obj_3c1800 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_0053e3b0[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053e3b0[0];
    FUN_003bf9d0((O_3bf9d0 *)&obj, (short)0);
    return t;
}

void FUN_003c1860(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlEnemy_Register);
}

void *beNDMWMdlEnemy_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlEnemy_metaObject,
        beNDMWMdlPEBase_Register,
        beNDMWMdlPEBase_GetPublishedMetaObject,
        beNDMWMdlEnemy_GetMetaObject,
        beNDMWMdlEnemy_className,
        0x2c, /* instance size */
        beNDMWMdlEnemy_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlEnemy_GetMetaObject(void)
{
    beNDMWMdlEnemy_GetReadyMetaObject();
}

