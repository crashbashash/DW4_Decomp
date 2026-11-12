int FUN_001340f0(void) {
    if (DAT_0055eec8[0] == 0) {
        DAT_0055eec8[0] = igMetaEnum_Create(&DAT_004d5080[0], &DAT_00485f88[0], &DAT_00485f90[0], 2);
    }
    return DAT_0055eec8[0];
}

int FUN_00134150(void) {
    if (DAT_0055eed0[0] == 0) {
        DAT_0055eed0[0] = igMetaEnum_Create(&DAT_004d5140[0], &DAT_00485f98[0], &DAT_00485fa8[0], 3);
    }
    return DAT_0055eed0[0];
}

int FUN_001341b0(int arg0) {
    FUN_00134370();
    return igMetaObject_CreateInstance(*(int *)0x55EED8, arg0);
}

igMetaObject *FUN_001341f0(void) {
    if (g_igRenderDestinationAttr_metaObject[0] == 0) {
        g_igRenderDestinationAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igRenderDestinationAttr_metaObject[0];
}

igMetaObject *igRenderDestinationAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderDestinationAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00134370();
    return g_igRenderDestinationAttr_metaObject[0];
}

int igRenderDestinationAttr_GetVTable(void) {
    union U_134290 u;
    int temp_s0;
    S_ref *p1;
    S_ref *p2;
    S_ref *t1;
    S_ref *t2;

    igObject_InitHeader(u.b);
    p1 = (S_ref *)&u.b[64];
    p2 = (S_ref *)&u.b[32];
    u.vt = (int)&DAT_00523060[0];
    *(int *)p2 = 0;
    *(int *)p1 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00523060[0];
    if (p1 != 0) {
        t1 = *(S_ref **)p1;
        if (t1 != 0) {
            t1->f4 = (int)((int) (t1->f4 - 1));
            if (((unsigned long long) ((long long) t1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t1);
            }
        }
    }
    if (p2 != 0) {
        t2 = *(S_ref **)p2;
        if (t2 != 0) {
            t2->f4 = (int)((int) (t2->f4 - 1));
            if (((unsigned long long) ((long long) t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t2);
            }
        }
    }
    return temp_s0;
}

void FUN_00134370(void)
{
    igMetaObject_RunStaticInit(igRenderDestinationAttr_Register);
}

void igRenderDestinationAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRenderDestinationAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igRenderDestinationAttr_GetMetaObject,
        igRenderDestinationAttr_className,
        0x44, /* instance size */
        igRenderDestinationAttr_GetVTable,
        &igRenderDestinationAttr_InitFields,
        0, /* extra callback item */
        g_igRenderDestinationAttr_callbackList /* callback list */
    );
}

void thunk_igRenderDestinationAttr_GetMetaObject(void) {
    igRenderDestinationAttr_GetMetaObject();
}

void igRenderDestinationAttr_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_v0;
    void *temp_v0_10;
    void *temp_v0_11;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v0_7;
    void *temp_v0_8;
    void *temp_v0_9;
    void *temp_s1;

    temp_s1 = (void *)g_igRenderDestinationAttr_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_00485fd0[0], 0xE);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    FUN_002dc7a0(temp_v0, &DAT_004860c8[0]);
    ((igMetaField *)temp_v0)->_persistent = 0;
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_00134150);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    FUN_002dc7a0(temp_v0_2, &DAT_004860d0[0]);
    ((igMetaField *)temp_v0_2)->_persistent = 0;
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(&FUN_001340f0);
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    FUN_002ea4b0(temp_v0_3, -1);
    ((igMetaField *)temp_v0_3)->_persistent = 0;
    ((igMetaField *)temp_v0_3)->_deepCopyMethod = 4;
    ((igMetaField *)temp_v0_3)->_shallowCopyMethod = 4;
    ((igMetaField *)temp_v0_3)->_isAlikeShallowMethod = 3;
    ((igMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3))->_persistent = 0;
    temp_v0_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    FUN_002ea4b0(temp_v0_4, -1);
    ((igMetaField *)temp_v0_4)->_persistent = 0;
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_00132ba0();
    ((igMetaField *)temp_s2)->_persistent = 0;
    temp_v0_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    FUN_002dc7a0(temp_v0_5, &DAT_004860d8[0]);
    ((igEnumMetaField *)temp_v0_5)->_getMetaEnumFunction = (int)(&FUN_00149b00);
    temp_v0_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    FUN_002ea4b0(temp_v0_6, -1);
    ((igMetaField *)temp_v0_6)->_persistent = 0;
    temp_v0_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    FUN_002ea4b0(temp_v0_7, -1);
    ((igMetaField *)temp_v0_7)->_persistent = 0;
    temp_v0_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    FUN_002ea4b0(temp_v0_8, -1);
    ((igMetaField *)temp_v0_8)->_persistent = 0;
    temp_v0_9 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA));
    FUN_002ea4b0(temp_v0_9, -1);
    ((igMetaField *)temp_v0_9)->_persistent = 0;
    temp_v0_10 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB));
    FUN_002ea4b0(temp_v0_10, -1);
    ((igMetaField *)temp_v0_10)->_persistent = 0;
    temp_v0_11 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xC));
    FUN_002ea4b0(temp_v0_11, -1);
    ((igMetaField *)temp_v0_11)->_persistent = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xD));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0014a040();
    ((igMetaField *)temp_s2_2)->_persistent = 0;
    ((igMetaField *)temp_s2_2)->_deepCopyMethod = 1;
    ((igMetaField *)temp_s2_2)->_shallowCopyMethod = 1;
    ((igMetaField *)temp_s2_2)->_isAlikeShallowMethod = 3;
    igMetaObject_NameFields(temp_s1, &DAT_00486010[0], &DAT_00486050[0], &DAT_00486090[0], temp_s0);
}

