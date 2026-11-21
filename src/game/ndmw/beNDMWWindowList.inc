igMetaObject *g_beNDMWWindowList_metaObject;
igMetaEnum *g_beNDMWWindowList_subWndMetaEnum;

igMetaObject *beNDMWWindowList_GetOrCreateMetaObject(void) {
    if (g_beNDMWWindowList_metaObject == 0) {
        g_beNDMWWindowList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWWindowList_metaObject;
}

igMetaObject *beNDMWWindowList_GetMetaObject(void) {
    if (g_beNDMWWindowList_metaObject == 0 || !isValid(g_beNDMWWindowList_metaObject)) beNDMWWindowList_EnsureRegistered();
    return g_beNDMWWindowList_metaObject;
}

int beNDMWWindowList_GetVTable(void) {
    beNDMWWindowList obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWWindowList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beNDMWWindowList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWWindowList_Register);
}

static igMetaObjectCallback g_beNDMWWindowList_callbackList[] = { beNDMWWindow_EnsureRegistered, 0 };

CallbackArray *beNDMWWindowList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWWindowList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        beNDMWWindowList_GetMetaObjectFunction,
        "beNDMWWindowList",
        0x14, /* instance size */
        beNDMWWindowList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWWindowList_callbackList /* callback list */
    );
}

void beNDMWWindowList_GetMetaObjectFunction(void)
{
    beNDMWWindowList_GetMetaObject();
}

static const char *g_beNDMWWindowList_subWndNames[] = {
    "STATUS",
    "XDATA",
    "LABO",
    "BANK",
    "CNOS",
    "DISK",
    "WPU",
    "APU",
    "CHIP",
    "JUNK",
    "CARD",
};
static int g_beNDMWWindowList_subWndValues[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    0xa,
};

igMetaEnum *SubWnd_GetMetaEnum(void) {
    if (g_beNDMWWindowList_subWndMetaEnum == 0) {
        g_beNDMWWindowList_subWndMetaEnum = igMetaEnum_Create("SubWnd", g_beNDMWWindowList_subWndNames, g_beNDMWWindowList_subWndValues, 11);
    }
    return g_beNDMWWindowList_subWndMetaEnum;
}

