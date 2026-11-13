void beNDMWItemBlueArmor_Create(int arg0) {
    FUN_003c8bd0();
    igMetaObject_CreateInstance(*(int *)0x58BF58, arg0);
}

void *beNDMWItemBlueArmor_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemBlueArmor_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c8bd0();
    }
    return g_beNDMWItemBlueArmor_metaObject[0];
}

int beNDMWItemBlueArmor_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005408f0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003c8bd0(void)
{
    igMetaObject_RunStaticInit(beNDMWItemBlueArmor_Register);
}

void *beNDMWItemBlueArmor_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWItemBlueArmor_metaObject,
        beNDMWItemRevisionPocketBase_Register,
        beNDMWItemRevisionPocketBase_GetPublishedMetaObject,
        beNDMWItemBlueArmor_GetMetaObject,
        beNDMWItemBlueArmor_className,
        0x1c, /* instance size */
        beNDMWItemBlueArmor_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWItemBlueArmor_GetMetaObject(void)
{
    beNDMWItemBlueArmor_GetReadyMetaObject();
}

igMetaObject *FUN_003c8c80(void) {
    return g_beNDMWItemRevisionPocketBase_metaObject[0];
}

