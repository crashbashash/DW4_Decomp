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
    struct Obj_34e1e0 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f14 = 0;
    obj.f18 = 0;
    obj.vt = (&g_beNumberCtrlInfo_vtable[0]);
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&g_beNumberCtrlInfo_vtable[0]);
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return temp_s0;
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

