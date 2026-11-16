igMetaObject *g_beGroupKeep_metaObject;

void *beGroupKeep_GetMetaObject(void) {
    igMetaObject *g = g_beGroupKeep_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beGroupKeep_EnsureRegistered();
    }
    return g_beGroupKeep_metaObject;
}

int beGroupKeep_GetVTable(void) {
    struct Obj_35efe0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.vt = &g_beGroupKeep_vtable[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beGroupKeep_vtable[0];
    FUN_00195a90(&obj, 0);
    return t;
}

void beGroupKeep_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGroupKeep_Register);
}

void *beGroupKeep_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGroupKeep_metaObject,
        igGroup_Register,
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

