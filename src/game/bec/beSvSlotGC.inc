void *FUN_0034a780(void) {
    igMetaObject *g = g_beSvSlotGC_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034a810();
    }
    return g_beSvSlotGC_metaObject[0];
}

int beSvSlotGC_GetVTable(void) {
    struct Obj_34a7d0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005389d0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0034a810(void)
{
    igMetaObject_RunStaticInit(beSvSlotGC_Register);
}

void *beSvSlotGC_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvSlotGC_metaObject,
        beSvSlotData_Register,
        beSvSlotData_GetPublishedMetaObject,
        beSvSlotGC_GetMetaObject,
        beSvSlotGC_className,
        0x18, /* instance size */
        beSvSlotGC_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvSlotGC_GetMetaObject(void)
{
    FUN_0034a780();
}

