igMetaObject *g_beCriAcxData_metaObject;

void *beCriAcxData_GetMetaObject(void) {
    igMetaObject *g = g_beCriAcxData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beCriAcxData_EnsureRegistered();
    }
    return g_beCriAcxData_metaObject;
}

int beCriAcxData_GetVTable(void) {
    beCriAcxData obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beCriAcxData_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beCriAcxData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCriAcxData_Register);
}

CallbackArray *beCriAcxData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCriAcxData_metaObject,
        beBinDataObject_Register,
        beBinDataObject_GetPublishedMetaObject,
        beCriAcxData_GetMetaObjectFunction,
        "beCriAcxData",
        0x18, /* instance size */
        beCriAcxData_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beCriAcxData_GetMetaObjectFunction(void)
{
    beCriAcxData_GetMetaObject();
}

