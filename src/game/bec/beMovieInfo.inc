igMetaObject *g_beMovieInfo_metaObject;

void *beMovieInfo_GetMetaObject(void) {
    igMetaObject *g = g_beMovieInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMovieInfo_EnsureRegistered();
    }
    return g_beMovieInfo_metaObject;
}

int beMovieInfo_GetVTable(void) {
    struct W_34eb60 o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[4] = 0;
    o.w[5] = 0;
    o.vt = g_beMovieInfo_vtable;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beMovieInfo_vtable;
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

void beMovieInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMovieInfo_Register);
}

void *beMovieInfo_Register(void) {
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

