igMetaObject *g_igSegment_metaObject;

igMetaObject *igSegment_GetMetaObject(void)
{
    igMetaObject *g = g_igSegment_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igSegment_EnsureRegistered();
    return g_igSegment_metaObject;
}

int igSegment_GetVTable(void) {
    struct Obj_19ada0 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.vt = &g_igSegment_vtable[0];
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igSegment_vtable[0];
    igGroup_Destroy((igGroup *)&obj, 0);
    return t;
}

void igSegment_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igSegment_Register);
}

CallbackArray *igSegment_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igSegment_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        igSegment_GetMetaObjectFunction,
        "igSegment",
        0x20, /* instance size */
        igSegment_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igSegment_GetMetaObjectFunction(void) {
    igSegment_GetMetaObject();
}

