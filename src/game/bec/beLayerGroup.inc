igMetaObject *g_beLayerGroup_metaObject;

void *beLayerGroup_GetMetaObject(void) {
    igMetaObject *g = g_beLayerGroup_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beLayerGroup_EnsureRegistered();
    }
    return g_beLayerGroup_metaObject;
}

int beLayerGroup_GetVTable(void) {
    beLayerGroup obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beLayerGroup_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beLayerGroup_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLayerGroup_Register);
}

void *beLayerGroup_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLayerGroup_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beLayerGroup_GetMetaObjectFunction,
        "beLayerGroup",
        0xc, /* instance size */
        beLayerGroup_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beLayerGroup_GetMetaObjectFunction(void)
{
    beLayerGroup_GetMetaObject();
}

igMetaEnum *g_beLayerGroup_swtCtlMetaEnum;
static const char *g_beLayerGroup_swtCtlNames[] = {
    "CLR", "SET", "DISPOFF", "DISPON",
    "FLIP",
};
static int g_beLayerGroup_swtCtlValues[] = {
    0, 1, 0, 1, 2,
};

igMetaEnum *beLayerCtl_GetSwtCtlEnum(void) {
    if (g_beLayerGroup_swtCtlMetaEnum == 0) {
        g_beLayerGroup_swtCtlMetaEnum = igMetaEnum_Create("SwtCtl", g_beLayerGroup_swtCtlNames, g_beLayerGroup_swtCtlValues, 5);
    }
    return g_beLayerGroup_swtCtlMetaEnum;
}

igMetaEnum *g_beLayerGroup_messageMetaEnum;
static const char *g_beLayerGroup_messageNames[] = {
    "ORDER", "SWITCH", "REMOVE", "GETNAMELIST",
    "GETLAYERNODE", "INFO",
};
static int g_beLayerGroup_messageValues[] = {
    0, 1, 2, 3, 4, 5,
};

igMetaEnum *beLayerCtl_GetMessageEnum(void) {
    if (g_beLayerGroup_messageMetaEnum == 0) {
        g_beLayerGroup_messageMetaEnum = igMetaEnum_Create("Message", g_beLayerGroup_messageNames, g_beLayerGroup_messageValues, 6);
    }
    return g_beLayerGroup_messageMetaEnum;
}

