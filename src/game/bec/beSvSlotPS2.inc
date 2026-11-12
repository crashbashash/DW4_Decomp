void *FUN_0034a630(void) {
    igMetaObject *g = g_beSvSlotPS2_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034a6c0();
    }
    return g_beSvSlotPS2_metaObject[0];
}

int beSvSlotPS2_GetVTable(void) {
    struct Obj_34a680 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538a30[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0034a6c0(void)
{
    igMetaObject_RunStaticInit(beSvSlotPS2_Register);
}

void *beSvSlotPS2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvSlotPS2_metaObject,
        beSvSlotData_Register,
        beSvSlotData_GetPublishedMetaObject,
        beSvSlotPS2_GetMetaObject,
        beSvSlotPS2_className,
        0x18, /* instance size */
        beSvSlotPS2_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvSlotPS2_GetMetaObject(void)
{
    FUN_0034a630();
}

igMetaObject *FUN_0034a770(void) {
    return g_beSvSlotData_metaObject[0];
}

