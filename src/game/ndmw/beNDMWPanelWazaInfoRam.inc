void *beNDMWPanelWazaInfoRam_ResolveMetaObject(void) {
    igMetaObject *meta = g_beNDMWPanelWazaInfoRam_metaObject[0];
    if (meta) {
        bool t;
        if ((t = (meta->_validity & 4) != 0) != false) goto end;
    }
    FUN_003bd9c0();
end:
    return g_beNDMWPanelWazaInfoRam_metaObject[0];
}

int beNDMWPanelWazaInfoRam_GetVTable(void) {
    union WazaInfoRamProbe u;
    int temp_s1;
    WazaInfoRamRefHeader * q0;
    WazaInfoRamRefHeader * q1;

    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    q0 = (WazaInfoRamRefHeader *)&u.b[40];
    *(int *)q0 = 0;
    u.vt = (int)(&DAT_0053d630[0]);
    q1 = (WazaInfoRamRefHeader *)&u.b[44];
    *(int *)q1 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)(&DAT_0053d630[0]);
    if (q1 != 0) {
        q1 = *(WazaInfoRamRefHeader **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    u.vt = (int)(&DAT_00539e90[0]);
    if (q0 != 0) {
        q0 = *(WazaInfoRamRefHeader **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s1;
}

struct RefHolderTarget **FUN_003bd940(struct RefHolderTarget **arg0, short arg1) {
    struct RefHolderTarget *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_003bd9c0(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelWazaInfoRam_Register);
}

void *beNDMWPanelWazaInfoRam_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWPanelWazaInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNDMWPanelWazaInfoRam_GetMetaObject,
        beNDMWPanelWazaInfoRam_className,
        0x30, /* instance size */
        beNDMWPanelWazaInfoRam_GetVTable,
        beNDMWPanelWazaInfoRam_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelWazaInfoRam_callbackList /* callback list */
    );
}

void beNDMWPanelWazaInfoRam_GetMetaObject(void)
{
    beNDMWPanelWazaInfoRam_ResolveMetaObject();
}

void beNDMWPanelWazaInfoRam_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWPanelWazaInfoRam_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca460[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003bdb50();
    igMetaObject_NameFields(temp_s0, &DAT_004ca468[0], &DAT_004ca470[0], &DAT_004ca478[0], temp_s2);
}

