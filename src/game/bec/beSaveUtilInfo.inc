igMetaObject *g_beSaveUtilInfo_metaObject;

void *beSaveUtilInfo_GetMetaObject(void) {
    igMetaObject *g = g_beSaveUtilInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSaveUtilInfo_EnsureRegistered();
    }
    return g_beSaveUtilInfo_metaObject;
}

int beSaveUtilInfo_GetVTable(void) {
    struct Obj_346b00 o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f20 = 0;
    o.f24 = 0;
    o.vt = &g_beSaveUtilInfo_vtable[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beSaveUtilInfo_vtable[0];
    
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

void beSaveUtilInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSaveUtilInfo_Register);
}

void *beSaveUtilInfo_Register(void) {
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

igMetaEnum *g_beSaveUtilInfo_messageMetaEnum;
static const char *g_beSaveUtilInfo_messageNames[] = {
    "GENERATE", "REMOVE", "REQUEST_FILEMAKE", "REQUEST_FILEFIND",
    "REQUEST_FORMAT", "REQUEST_USE_CHECK", "REQUEST_READ_MEDIA", "REQUEST_WRITE_MEDIA",
    "REQUEST_GETFREESIZE", "GETDELIVER", "REPORT", "ISBUSY",
    "GETRESULT", "ISRDY", "CHECKMEM", "GETOPERATE",
    "ISUSESAVEPOINT", "XBOX_HD_CAPACHK",
};
static int g_beSaveUtilInfo_messageValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
    0x10, 0x11,
};

igMetaEnum *FUN_00346c20(void) {
    if (g_beSaveUtilInfo_messageMetaEnum == 0) {
        g_beSaveUtilInfo_messageMetaEnum = igMetaEnum_Create("Message", g_beSaveUtilInfo_messageNames, g_beSaveUtilInfo_messageValues, 0x12);
    }
    return g_beSaveUtilInfo_messageMetaEnum;
}

