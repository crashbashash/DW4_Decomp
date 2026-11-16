igMetaObject *g_beSvEndApi_metaObject;
int g_beSvEndApi_orderTypeStorage;

void beSvEndApi_Create(int allocator) {
    beSvEndApi_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5881E0, allocator);
}

void *beSvEndApi_GetMetaObject(void) {
    igMetaObject *g = g_beSvEndApi_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvEndApi_EnsureRegistered();
    }
    return g_beSvEndApi_metaObject;
}

int beSvEndApi_GetVTable(void) {
    Obj_348680 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &g_beSaveApi_vtable[0];
    obj.r1 = 0;
    obj.r2 = 0;
    obj.r3 = 0;
    obj.vt = &g_beSvEndApi_vtable[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beSaveApi_vtable[0];
    obj.rel(&obj.r3);
    obj.rel(&obj.r2);
    obj.rel(&obj.r1);
    return r;
}

void beSvEndApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvEndApi_Register);
}

void *beSvEndApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvEndApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvEndApi_GetMetaObjectFunction,
        "beSvEndApi",
        0x40, /* instance size */
        beSvEndApi_GetVTable,
        beSvEndApi_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvEndApi_GetMetaObjectFunction(void)
{
    beSvEndApi_GetMetaObject();
}

void beSvEndApi_InitFields(void) {
    int index;
    void **found;
    void *meta;
    igIntMetaField *clone;

    meta = (void *)g_beSvEndApi_metaObject;
    found = (void **)(igMetaObject_FindFieldByName(meta, "_orderType"));
    index = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, found);
    clone = (igIntMetaField *)(((DW4VC_84_1 *)(found))->vX((int)(1)));
    igIntMetaField_SetDefault(clone, 0xB);
    clone->_externalEnumStorage = (int)(&g_beSvEndApi_orderTypeStorage);
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
}

