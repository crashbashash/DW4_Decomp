igMetaObject *g_beNDMWItemBlueArmor_metaObject;

beNDMWItemBlueArmor *beNDMWItemBlueArmor_Create(int allocator) {
    beNDMWItemBlueArmor_EnsureRegistered();
    return (beNDMWItemBlueArmor *)igMetaObject_CreateInstance(g_beNDMWItemBlueArmor_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWItemBlueArmor_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemBlueArmor_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWItemBlueArmor_EnsureRegistered();
    }
    return g_beNDMWItemBlueArmor_metaObject;
}

int beNDMWItemBlueArmor_GetVTable(void) {
    beNDMWItemBlueArmor obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWItemBlueArmor_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
}

void beNDMWItemBlueArmor_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWItemBlueArmor_Register);
}

CallbackArray *beNDMWItemBlueArmor_Register(void) {
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

