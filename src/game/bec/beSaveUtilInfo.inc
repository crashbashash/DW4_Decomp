igMetaObject *g_beSaveUtilInfo_metaObject;

void *beSaveUtilInfo_GetMetaObject(void) {
    igMetaObject *g = g_beSaveUtilInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSaveUtilInfo_EnsureRegistered();
    }
    return g_beSaveUtilInfo_metaObject;
}

int beSaveUtilInfo_GetVTable(void) {
    beSaveUtilInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beSaveUtilInfo_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beSaveUtilInfo_vtable[0];
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

void beSaveUtilInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSaveUtilInfo_Register);
}

CallbackArray *beSaveUtilInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSaveUtilInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beSaveUtilInfo_GetMetaObjectFunction,
        "beSaveUtilInfo",
        0x1c, /* instance size */
        beSaveUtilInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSaveUtilInfo_GetMetaObjectFunction(void)
{
    beSaveUtilInfo_GetMetaObject();
}

igMetaEnum *g_beSaveUtil_messageMetaEnum;
static const char *g_beSaveUtil_messageNames[] = {
    "GENERATE", "REMOVE", "REQUEST_FILEMAKE", "REQUEST_FILEFIND",
    "REQUEST_FORMAT", "REQUEST_USE_CHECK", "REQUEST_READ_MEDIA", "REQUEST_WRITE_MEDIA",
    "REQUEST_GETFREESIZE", "GETDELIVER", "REPORT", "ISBUSY",
    "GETRESULT", "ISRDY", "CHECKMEM", "GETOPERATE",
    "ISUSESAVEPOINT", "XBOX_HD_CAPACHK",
};
static int g_beSaveUtil_messageValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
    0x10, 0x11,
};

igMetaEnum *beSaveUtil_GetMessageEnum(void) {
    if (g_beSaveUtil_messageMetaEnum == 0) {
        g_beSaveUtil_messageMetaEnum = igMetaEnum_Create("Message", g_beSaveUtil_messageNames, g_beSaveUtil_messageValues, 0x12);
    }
    return g_beSaveUtil_messageMetaEnum;
}

