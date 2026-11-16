igMetaObject *g_beNumberCtrlInfo_metaObject;

void *beNumberCtrlInfo_GetMetaObject(void) {
    unsigned char b;
    if (g_beNumberCtrlInfo_metaObject != 0) {
        b = (g_beNumberCtrlInfo_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beNumberCtrlInfo_EnsureRegistered();
done:
    return g_beNumberCtrlInfo_metaObject;
}

int beNumberCtrlInfo_GetVTable(void) {
    beNumberCtrlInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beNumberCtrlInfo_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beNumberCtrlInfo_vtable[0];
    beBaseInfo_Destroy((struct S_33ec80 *)&obj, (short)0);
    return vtable;
}

void beNumberCtrlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNumberCtrlInfo_Register);
}

void *beNumberCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNumberCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNumberCtrlInfo_GetMetaObjectFunction,
        "beNumberCtrlInfo",
        0x1c, /* instance size */
        beNumberCtrlInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNumberCtrlInfo_GetMetaObjectFunction(void)
{
    beNumberCtrlInfo_GetMetaObject();
}

igMetaEnum *g_beNumberCtrlInfo_messageMetaEnum;
static const char *g_beNumberCtrlInfo_messageNames[] = {
    "GETVALUE", "SETVALUE", "SETVALUEDIRECT", "ADDVALUE",
};
static int g_beNumberCtrlInfo_messageValues[] = {
    0, 1, 2, 3,
};

igMetaEnum *beNumberCtrl_GetMessageEnum(void) {
    if (g_beNumberCtrlInfo_messageMetaEnum == 0) {
        g_beNumberCtrlInfo_messageMetaEnum = igMetaEnum_Create("Message", g_beNumberCtrlInfo_messageNames, g_beNumberCtrlInfo_messageValues, 4);
    }
    return g_beNumberCtrlInfo_messageMetaEnum;
}

