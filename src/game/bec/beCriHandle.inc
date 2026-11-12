void FUN_00366910(int arg0) {
    FUN_00366b20();
    igMetaObject_CreateInstance(*(int *)0x5899C8, arg0);
}

igMetaObject *FUN_00366950(void) {
    if (g_beCriHandle_metaObject[0] == 0) {
        g_beCriHandle_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beCriHandle_metaObject[0];
}

void *FUN_003669a0(void) {
    igMetaObject *g = g_beCriHandle_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00366b20();
    }
    return g_beCriHandle_metaObject[0];
}

int beCriHandle_GetVTable(void) {
    union U u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p4C;
    char *p48;
    char *p50;

    igObject_InitHeader(u.b);
    p48 = &u.b[8];
    *(int *)p48 = 0;
    u.vt = (int)&DAT_00534f60[0];
    p4C = &u.b[12];
    *(int *)p4C = 0;
    p50 = &u.b[16];
    *(int *)p50 = 0;
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00534f60[0];
    if (p50 != 0) {
        v1 = *(int **)p50;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p4C != 0) {
        v1 = *(int **)p4C;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    u.vt = (int)&DAT_00524950[0];
    if (p48 != 0) {
        v1 = *(int **)p48;
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

void FUN_00366b20(void)
{
    igMetaObject_RunStaticInit(beCriHandle_Register);
}

void *beCriHandle_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCriHandle_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beCriHandle_GetMetaObject,
        beCriHandle_className,
        0x28, /* instance size */
        beCriHandle_GetVTable,
        beCriHandle_InitFields,
        0, /* extra callback item */
        g_beCriHandle_callbackList /* callback list */
    );
}

void beCriHandle_GetMetaObject(void)
{
    FUN_003669a0();
}

void beCriHandle_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beCriHandle_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7430[0], 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003671a0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_00366340();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c7450[0], &DAT_004c7470[0], &DAT_004c7490[0], temp_s2);
}

