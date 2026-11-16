igMetaObject *g_beSvSlotGC_metaObject;

void *beSvSlotGC_GetMetaObject(void) {
    igMetaObject *g = g_beSvSlotGC_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvSlotGC_EnsureRegistered();
    }
    return g_beSvSlotGC_metaObject;
}

int beSvSlotGC_GetVTable(void) {
    beSvSlotGC obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beSvSlotGC_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beSvSlotGC_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvSlotGC_Register);
}

void *beSvSlotGC_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvSlotGC_metaObject,
        beSvSlotData_Register,
        beSvSlotData_GetPublishedMetaObject,
        beSvSlotGC_GetMetaObjectFunction,
        "beSvSlotGC",
        0x18, /* instance size */
        beSvSlotGC_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvSlotGC_GetMetaObjectFunction(void)
{
    beSvSlotGC_GetMetaObject();
}

