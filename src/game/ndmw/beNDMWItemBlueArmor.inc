igMetaObject *g_beNDMWItemBlueArmor_metaObject;

void beNDMWItemBlueArmor_Create(int arg0) {
    beNDMWItemBlueArmor_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWItemBlueArmor_metaObject, arg0);
}

void *beNDMWItemBlueArmor_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemBlueArmor_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWItemBlueArmor_EnsureRegistered();
    }
    return g_beNDMWItemBlueArmor_metaObject;
}

int beNDMWItemBlueArmor_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beNDMWItemBlueArmor_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beNDMWItemBlueArmor_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWItemBlueArmor_Register);
}

void *beNDMWItemBlueArmor_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWItemBlueArmor_metaObject,
        beNDMWItemRevisionPocketBase_Register,
        beNDMWItemRevisionPocketBase_GetPublishedMetaObject,
        beNDMWItemBlueArmor_GetMetaObject,
        "beNDMWItemBlueArmor",
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

igMetaObject *beNDMWItemRevisionPocketBase_GetPublishedMetaObject(void) {
    return g_beNDMWItemRevisionPocketBase_metaObject;
}

