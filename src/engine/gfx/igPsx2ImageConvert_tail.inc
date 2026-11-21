igMetaObject *igPsx2ImageConvert_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ImageConvert_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2ImageConvert_EnsureRegistered();
    return g_igPsx2ImageConvert_metaObject;
}

int igPsx2ImageConvert_GetVTable(void) {
    struct Obj_153c40 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igPsx2ImageConvert_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igPsx2ImageConvert_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPsx2ImageConvert_Register);
}

CallbackArray *igPsx2ImageConvert_Register(void) {
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2ImageConvert_metaObject,
        igImageConvert_Register,
        igImageConvert_GetPublishedMetaObject,
        igPsx2ImageConvert_GetMetaObjectFunction,
        "igPsx2ImageConvert",
        8, /* instance size */
        igPsx2ImageConvert_GetVTable,
        igPsx2ImageConvert_InitFields_00153d10,     /* Field adder. */
        0,                                              /* extra callback-vector item (none) */
        0                                               /* zero-terminated callback-vector item list (none) */
    );
}

int FUN_00153d00(void) {
    return (int)g_igImageConvert_metaObject;
}

void FUN_00153d10(void) {
    *(int *)((char *)(g_igPsx2ImageConvert_metaObject) + 64) = (int)(&igImageConvert_GetMetaObjectFunction);
}

