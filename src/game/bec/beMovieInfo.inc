igMetaObject *g_beMovieInfo_metaObject;

void *beMovieInfo_GetMetaObject(void) {
    igMetaObject *g = g_beMovieInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMovieInfo_EnsureRegistered();
    }
    return g_beMovieInfo_metaObject;
}

int beMovieInfo_GetVTable(void) {
    beMovieInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beMovieInfo_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beMovieInfo_vtable[0];
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

void beMovieInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMovieInfo_Register);
}

CallbackArray *beMovieInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMovieInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beMovieInfo_GetMetaObjectFunction,
        "beMovieInfo",
        0x1c, /* instance size */
        beMovieInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beMovieInfo_GetMetaObjectFunction(void)
{
    beMovieInfo_GetMetaObject();
}

