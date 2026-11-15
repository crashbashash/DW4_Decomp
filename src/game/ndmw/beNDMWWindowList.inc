igMetaObject *g_beNDMWWindowList_metaObject;
igMetaEnum *g_beNDMWWindowList_subWndMetaEnum;

igMetaObject *FUN_003b1be0(void) {
    if (g_beNDMWWindowList_metaObject == 0) {
        g_beNDMWWindowList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWWindowList_metaObject;
}

igMetaObject *FUN_003b1c30(void) {
    if (g_beNDMWWindowList_metaObject == 0 || !isValid(g_beNDMWWindowList_metaObject)) FUN_003b1cc0();
    return g_beNDMWWindowList_metaObject;
}

int beNDMWWindowList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053ddc0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003b1cc0(void)
{
    igMetaObject_RunStaticInit(beNDMWWindowList_Register);
}

static igMetaObjectCallback g_beNDMWWindowList_callbackList[] = { FUN_003b1e70, 0 };

void *beNDMWWindowList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWWindowList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWWindowList_GetMetaObject,
        "beNDMWWindowList",
        0x14, /* instance size */
        beNDMWWindowList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWWindowList_callbackList /* callback list */
    );
}

void beNDMWWindowList_GetMetaObject(void)
{
    FUN_003b1c30();
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

