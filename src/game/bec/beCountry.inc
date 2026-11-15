igMetaObject *g_beCountry_metaObject;

void *FUN_00367d10(void) {
    igMetaObject *g = g_beCountry_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00367da0();
    }
    return g_beCountry_metaObject;
}

int beCountry_GetVTable(void) {
    struct Obj_367d60 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00534d10[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00367da0(void)
{
    igMetaObject_RunStaticInit(beCountry_Register);
}

void *beCountry_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCountry_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCountry_GetMetaObject,
        "beCountry",
        8, /* instance size */
        beCountry_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beCountry_GetMetaObject(void)
{
    FUN_00367d10();
}

