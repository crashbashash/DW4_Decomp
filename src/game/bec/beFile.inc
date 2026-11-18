igMetaObject *g_beFile_metaObject;

void *beFile_GetMetaObject(void) {
    igMetaObject *g = g_beFile_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beFile_EnsureRegistered();
    }
    return g_beFile_metaObject;
}

int beFile_GetVTable(void) {
    beFile obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beFile_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beFile_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beFile_Register);
}

CallbackArray *beFile_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beFile_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beFile_GetMetaObjectFunction,
        "beFile",
        8, /* instance size */
        beFile_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beFile_GetMetaObjectFunction(void)
{
    beFile_GetMetaObject();
}

