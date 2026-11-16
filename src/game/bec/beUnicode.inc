igMetaObject *g_beUnicode_metaObject;

void *beUnicode_GetMetaObject(void) {
    igMetaObject *g = g_beUnicode_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beUnicode_EnsureRegistered();
    }
    return g_beUnicode_metaObject;
}

int beUnicode_GetVTable(void) {
    beUnicode obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beUnicode_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void beUnicode_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beUnicode_Register);
}

CallbackArray *beUnicode_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beUnicode_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beUnicode_GetMetaObjectFunction,
        "beUnicode",
        8, /* instance size */
        beUnicode_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beUnicode_GetMetaObjectFunction(void)
{
    beUnicode_GetMetaObject();
}

