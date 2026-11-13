void *FUN_0035c850(void) {
    igMetaObject *g = g_beLayerGroup_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035c930();
    }
    return g_beLayerGroup_metaObject[0];
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
        g_beLayerGroup_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beLayerGroup_GetMetaObject,
        beLayerGroup_className,
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

int beLayerCtl_GetSwtCtlEnum(void) {
    if (DAT_00589288[0] == 0) {
        DAT_00589288[0] = igMetaEnum_Create(&SwtCtl[0], &DAT_004c63b0[0], &DAT_004c63d0[0], 5);
    }
    return DAT_00589288[0];
}

int beLayerCtl_GetMessageEnum(void) {
    if (DAT_00589290[0] == 0) {
        DAT_00589290[0] = igMetaEnum_Create(&Message_2[0], &DAT_004c63f0[0], &DAT_004c6410[0], 6);
    }
    return DAT_00589290[0];
}

