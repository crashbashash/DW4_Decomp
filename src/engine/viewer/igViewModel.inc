igMetaObject *FUN_0045d470(void) {
    if (g_igViewModel_metaObject[0] == 0) {
        g_igViewModel_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igViewModel_metaObject[0];
}

void *igViewModel_GetMetaObject(void) {
    igMetaObject *g = g_igViewModel_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0045d5c0();
    }
    return g_igViewModel_metaObject[0];
}

int igViewModel_GetVTable(void) {
    union U_45d510 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p38;
    igObject_InitHeader(u.b);
    p38 = &u.b[8];
    *(int *)p38 = 0;
    u.vt = (int)&DAT_00542040[0];
    igMatrix44f_SetIdentity(&u.b[12]);
    r = *(int *)&u.b[*(int *)((char *)(((void *)g_objectSystem[0])) + 916)];
    u.vt = (int)&DAT_00540e30[0];
    if (p38 != 0) {
        v1 = *(int **)p38;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return r;
}

void FUN_0045d5c0(void)
{
    igMetaObject_RunStaticInit(igViewModel_Register);
}

void igViewModel_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewModel_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igViewModel_GetMetaObject,
        igViewModel_className,
        0xB0, /* instance size */
        igViewModel_GetVTable,
        &igViewModel_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igViewModel_GetMetaObject(void) {
    igViewModel_GetMetaObject();
}

void igViewModel_InitFields(void) {
    int temp_s1;
    void *temp_s0;
    void *temp_a1, *temp_a2, *temp_a3, *temp_a4, *temp_a5, *temp_a6;
    float v1[4];
    float v2[4];
    float v3[4];
    float v4[4];
    float v5[4];
    float v6[4];

    temp_s0 = (void *)g_igViewModel_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igViewModel_ctorTable[0], 0xD);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), 1.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), 45.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 1.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4), 1000.0f);
    temp_a1 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5);
    v1[0] = 0.0f; v1[1] = 0.0f; v1[2] = 0.0f;
    FUN_0018e470(temp_a1, v1);
    temp_a2 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6);
    v2[0] = 0.0f; v2[1] = 0.0f; v2[2] = 1.0f;
    FUN_0018e470(temp_a2, v2);
    temp_a3 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7);
    v3[0] = 0.0f; v3[1] = 1.0f; v3[2] = 0.0f;
    FUN_0018e470(temp_a3, v3);
    temp_a4 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8);
    v4[0] = 1.0f; v4[1] = 0.0f; v4[2] = 0.0f;
    FUN_0018e470(temp_a4, v4);
    temp_a5 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9);
    v5[0] = 0.0f; v5[1] = 1.0f; v5[2] = 0.0f;
    FUN_0018e470(temp_a5, v5);
    temp_a6 = igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB);
    v6[0] = 0.0f; v6[1] = 0.0f; v6[2] = 0.0f;
    FUN_0018e470(temp_a6, v6);
    igMetaObject_NameFields(temp_s0, &g_igViewModel_fieldTable[0], &DAT_004d1770[0], &DAT_004d17b0[0], temp_s1);
}

