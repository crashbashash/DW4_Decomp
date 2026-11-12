igMetaObject *igSegment_GetMetaObject(void)
{
    igMetaObject *g = g_igSegment_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019ae10();
    return g_igSegment_metaObject[0];
}

int igSegment_GetVTable(void) {
    struct Obj_19ada0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.vt = &DAT_0052ad10[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052ad10[0];
    FUN_00195a90((struct T_195a90 *)&obj, 0);
    return t;
}

void FUN_0019ae10(void)
{
    igMetaObject_RunStaticInit(igSegment_Register);
}

void igSegment_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igSegment_metaObject),
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igSegment_GetMetaObject,
        igSegment_className,
        0x20, /* instance size */
        igSegment_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igSegment_GetMetaObject(void) {
    igSegment_GetMetaObject();
}

