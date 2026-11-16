igMetaObject *g_beDataBaseList_metaObject;

void *beDataBaseList_GetMetaObject(void) {
    igMetaObject *g = g_beDataBaseList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beDataBaseList_EnsureRegistered();
    }
    return g_beDataBaseList_metaObject;
}

int beDataBaseList_GetVTable(void) {
    beDataBaseList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beDataBaseList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beDataBaseList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataBaseList_Register);
}

static igMetaObjectCallback g_beDataBaseList_callbackList[] = { beDataBase_EnsureRegistered, 0 };

void *beDataBaseList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataBaseList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beDataBaseList_GetMetaObjectFunction,
        "beDataBaseList",
        0x14, /* instance size */
        beDataBaseList_GetVTable,
        0,
        0, /* extra callback item */
        g_beDataBaseList_callbackList /* callback list */
    );
}

void beDataBaseList_GetMetaObjectFunction(void)
{
    beDataBaseList_GetMetaObject();
}

