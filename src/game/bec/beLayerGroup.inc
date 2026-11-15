igMetaObject *g_beLayerGroup_metaObject;

void *FUN_0035c850(void) {
    igMetaObject *g = g_beLayerGroup_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035c930();
    }
    return g_beLayerGroup_metaObject;
}

int beLayerGroup_GetVTable(void) {
    union U_35c8a0 u;
    int temp_s0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_igNamedObject_vtable[0];
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00536540[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_0035c930(void)
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
        beLayerGroup_GetMetaObject,
        "beLayerGroup",
        0xc, /* instance size */
        beLayerGroup_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beLayerGroup_GetMetaObject(void)
{
    FUN_0035c850();
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

