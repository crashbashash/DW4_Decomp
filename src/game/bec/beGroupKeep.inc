void *FUN_0035ef90(void) {
    igMetaObject *g = g_beGroupKeep_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035f050();
    }
    return g_beGroupKeep_metaObject[0];
}

int beGroupKeep_GetVTable(void) {
    struct Obj_35efe0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.vt = &DAT_005360b0[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_005360b0[0];
    FUN_00195a90(&obj, 0);
    return t;
}

void FUN_0035f050(void)
{
    igMetaObject_RunStaticInit(beGroupKeep_Register);
}

void *beGroupKeep_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGroupKeep_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beGroupKeep_GetMetaObject,
        beGroupKeep_className,
        0x20, /* instance size */
        beGroupKeep_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beGroupKeep_GetMetaObject(void)
{
    FUN_0035ef90();
}

