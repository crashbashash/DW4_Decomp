igMetaObject *g_beSwitchCtrl_metaObject;

beSwitchCtrl *beSwitchCtrl_CreateInstance(int allocator) {
    beSwitchCtrl_EnsureRegistered();
    return (beSwitchCtrl *)igMetaObject_CreateInstance(*(int *)0x587DF8, allocator);
}

igMetaObject *beSwitchCtrl_GetOrCreateMetaObject(void) {
    if (g_beSwitchCtrl_metaObject == 0) {
        g_beSwitchCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSwitchCtrl_metaObject;
}

void *beSwitchCtrl_GetMetaObject(void) {
    igMetaObject *g = g_beSwitchCtrl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSwitchCtrl_EnsureRegistered();
    }
    return g_beSwitchCtrl_metaObject;
}

int beSwitchCtrl_GetVTable(void) {
    beSwitchCtrl obj;
    int vtable;
    igObject **infoListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    infoListSlot = (igObject **)&obj._infoList;
    *infoListSlot = 0;
    obj._vtable = (int)&g_beSwitchCtrl_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    igObjectRef_Release(infoListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beSwitchCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSwitchCtrl_Register);
}

void *beSwitchCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSwitchCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beSwitchCtrl_GetMetaObjectFunction,
        "beSwitchCtrl",
        0x20, /* instance size */
        beSwitchCtrl_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSwitchCtrl_GetMetaObjectFunction(void)
{
    beSwitchCtrl_GetMetaObject();
}

igMetaEnum *g_beStaticInfoCtl_messageMetaEnum;
static const char *g_beStaticInfoCtl_messageNames[] = {
    "GETINFOLIST",
};
static int g_beStaticInfoCtl_messageValues[] = {
    0,
};

igMetaEnum *beStaticInfoCtl_GetMessageEnum(void) {
    if (g_beStaticInfoCtl_messageMetaEnum == 0) {
        g_beStaticInfoCtl_messageMetaEnum = igMetaEnum_Create("Message", g_beStaticInfoCtl_messageNames, g_beStaticInfoCtl_messageValues, 1);
    }
    return g_beStaticInfoCtl_messageMetaEnum;
}

