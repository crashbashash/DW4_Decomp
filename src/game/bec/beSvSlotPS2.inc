igMetaObject *g_beSvSlotPS2_metaObject;

void *beSvSlotPS2_GetMetaObject(void) {
    igMetaObject *g = g_beSvSlotPS2_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvSlotPS2_EnsureRegistered();
    }
    return g_beSvSlotPS2_metaObject;
}

int beSvSlotPS2_GetVTable(void) {
    beSvSlotPS2 obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beSvSlotPS2_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beSvSlotPS2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvSlotPS2_Register);
}

void *beSvSlotPS2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvSlotPS2_metaObject,
        beSvSlotData_Register,
        beSvSlotData_GetPublishedMetaObject,
        beSvSlotPS2_GetMetaObjectFunction,
        "beSvSlotPS2",
        0x18, /* instance size */
        beSvSlotPS2_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvSlotPS2_GetMetaObjectFunction(void)
{
    beSvSlotPS2_GetMetaObject();
}

igMetaObject *beSvSlotData_GetPublishedMetaObject(void) {
    return g_beSvSlotData_metaObject;
}

