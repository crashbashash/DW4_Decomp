igMetaObject *g_beMeterCtrl_metaObject;

void beMeterCtrl_CreateInstance(int allocator) {
    beMeterCtrl_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588F30, allocator);
}

igMetaObject *beMeterCtrl_GetOrCreateMetaObject(void) {
    if (g_beMeterCtrl_metaObject == 0) {
        g_beMeterCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMeterCtrl_metaObject;
}

void *beMeterCtrl_GetMetaObject(void) {
    unsigned char b;
    if (g_beMeterCtrl_metaObject != 0) {
        b = (g_beMeterCtrl_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beMeterCtrl_EnsureRegistered();
done:
    return g_beMeterCtrl_metaObject;
}

int beMeterCtrl_GetVTable(void) {
    Obj_357740 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &g_beBaseInfoManager_vtable[0];
    obj.r1 = 0;
    obj.r2 = 0;
    obj.vt = &g_beMeterCtrl_vtable[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beBaseInfoManager_vtable[0];
    obj.rel2();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel1();
    return r;
}

void beMeterCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMeterCtrl_Register);
}

void *beMeterCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMeterCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beMeterCtrl_GetMetaObjectFunction,
        "beMeterCtrl",
        0x20, /* instance size */
        beMeterCtrl_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beMeterCtrl_GetMetaObjectFunction(void)
{
    beMeterCtrl_GetMetaObject();
}

