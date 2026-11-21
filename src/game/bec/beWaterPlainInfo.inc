igMetaObject *g_beWaterPlainInfo_metaObject;

void *beWaterPlainInfo_GetMetaObject(void) {
    unsigned char b;
    if (g_beWaterPlainInfo_metaObject != 0) {
        b = (g_beWaterPlainInfo_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beWaterPlainInfo_EnsureRegistered();
done:
    return g_beWaterPlainInfo_metaObject;
}

int beWaterPlainInfo_GetVTable(void) {
    beWaterPlainInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beWaterPlainInfo_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beWaterPlainInfo_vtable[0];
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

void beWaterPlainInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beWaterPlainInfo_Register);
}

CallbackArray *beWaterPlainInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWaterPlainInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beWaterPlainInfo_GetMetaObjectFunction,
        "beWaterPlainInfo",
        0x1c, /* instance size */
        beWaterPlainInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beWaterPlainInfo_GetMetaObjectFunction(void)
{
    beWaterPlainInfo_GetMetaObject();
}

igMetaEnum *g_beWaterPlainInfo_messageMetaEnum;
static const char *g_beWaterPlainInfo_messageNames[] = {
    "MAKEWAVE",
};
static int g_beWaterPlainInfo_messageValues[] = {
    0,
};

igMetaEnum *beWaterPlain_GetMessageEnum(void) {
    if (g_beWaterPlainInfo_messageMetaEnum == 0) {
        g_beWaterPlainInfo_messageMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("Message", g_beWaterPlainInfo_messageNames, g_beWaterPlainInfo_messageValues, 1);
    }
    return g_beWaterPlainInfo_messageMetaEnum;
}

