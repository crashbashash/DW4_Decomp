igMetaObject *g_beGroupKeep_metaObject;

void *beGroupKeep_GetMetaObject(void) {
    igMetaObject *g = g_beGroupKeep_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beGroupKeep_EnsureRegistered();
    }
    return g_beGroupKeep_metaObject;
}

int beGroupKeep_GetVTable(void) {
    beGroupKeep obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._bound = 0;
    obj._parentList = 0;
    obj._childList = 0;
    obj._vtable = (int)&g_beGroupKeep_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beGroupKeep_vtable[0];
    igGroup_Destroy((igGroup *)&obj, 0);
    return vtable;
}

void beGroupKeep_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGroupKeep_Register);
}

CallbackArray *beGroupKeep_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGroupKeep_metaObject,
        (igMetaObjectRegisterFunction)igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beGroupKeep_GetMetaObjectFunction,
        "beGroupKeep",
        0x20, /* instance size */
        beGroupKeep_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beGroupKeep_GetMetaObjectFunction(void)
{
    beGroupKeep_GetMetaObject();
}

