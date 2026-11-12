void beLoadIntf2ComMdlData__Create(int allocator) {
    FUN_003c75a0();
    igMetaObject_CreateInstance(((int *)g_beLoadIntf2ComMdlData_metaObject)[0], allocator);
}

void *beLoadIntf2ComMdlData_GetReadyMetaObject(void) {
    struct G *g = DAT_0058be70[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c75a0();
    }
    return DAT_0058be70[0];
}

int beLoadIntf2ComMdlData_GetVTable(void) {
    union U_3c74e0 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p3C;
    char *p40;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053c810[0];
    p3C = &u.b[12];
    *(int *)p3C = 0;
    p40 = &u.b[16];
    *(int *)p40 = 0;
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053c810[0];
    if (p40 != 0) {
        v1 = *(int **)p40;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    if (p3C != 0) {
        v1 = *(int **)p3C;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return r;
}

void FUN_003c75a0(void)
{
    igMetaObject_RunStaticInit(beLoadIntf2ComMdlData_Register);
}

void *beLoadIntf2ComMdlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLoadIntf2ComMdlData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beLoadIntf2ComMdlData_GetMetaObject,
        beLoadIntf2ComMdlData_className,
        0x14, /* instance size */
        beLoadIntf2ComMdlData_GetVTable,
        beLoadIntf2ComMdlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beLoadIntf2ComMdlData_GetMetaObject(void)
{
    beLoadIntf2ComMdlData_GetReadyMetaObject();
}

void beLoadIntf2ComMdlData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058be70)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cbf28[0], 3);
    igMetaObject_NameFields(temp_s0, &DAT_004cbf38[0], &DAT_004cbf48[0], &DAT_004cbf58[0], temp_s1);
}

