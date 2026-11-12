igMetaObject *igMessageBase_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageBase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00226540();
    return g_igMessageBase_metaObject[0];
}

int igMessageBase_GetVTable(void) {
    Obj_4 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_0052c6e0[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00226540(void)
{
    igMetaObject_RunStaticInit(igMessageBase_Register);
}

void igMessageBase_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageBase_metaObject,
        igBase_Register,
        igBase_GetPublishedMetaObject,
        thunk_igMessageBase_GetMetaObject,
        igMessageBase_className,
        0x20, /* instance size */
        igMessageBase_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMessageBase_GetMetaObject(void) {
    igMessageBase_GetMetaObject();
}

igMetaObject *FUN_002265d0(void) {
    return g_igInterfaced_metaObject[0];
}

