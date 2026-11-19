igMetaObject *g_beCountry_metaObject;

void *beCountry_GetMetaObject(void) {
    igMetaObject *g = g_beCountry_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beCountry_EnsureRegistered();
    }
    return g_beCountry_metaObject;
}

int beCountry_GetVTable(void) {
    beCountry obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beCountry_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beCountry_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCountry_Register);
}

CallbackArray *beCountry_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCountry_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beCountry_GetMetaObjectFunction,
        "beCountry",
        8, /* instance size */
        beCountry_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beCountry_GetMetaObjectFunction(void)
{
    beCountry_GetMetaObject();
}

