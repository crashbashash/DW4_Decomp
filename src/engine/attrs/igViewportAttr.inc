igMetaObject *FUN_00130440(void) {
    if (g_igViewportAttr_metaObject[0] == 0) {
        g_igViewportAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igViewportAttr_metaObject[0];
}

igMetaObject *igViewportAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igViewportAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00130570();
    return g_igViewportAttr_metaObject[0];
}

int igViewportAttr_GetVTable(void) {
    union U_1304e0 u;
    int temp_s0;
    char *ps;
    int *temp_a0;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00522520[0];
    ps = &u.b[28];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00522520[0];
    if (ps != 0) {
        temp_a0 = *(int **)ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

void FUN_00130570(void)
{
    igMetaObject_RunStaticInit(igViewportAttr_Register);
}

void igViewportAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewportAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igViewportAttr_GetMetaObject,
        igViewportAttr_className,
        0x28, /* instance size */
        igViewportAttr_GetVTable,
        &igViewportAttr_InitFields,
        0, /* extra callback item */
        g_igViewportAttr_callbackList /* callback list */
    );
}

void thunk_igViewportAttr_GetMetaObject(void) {
    igViewportAttr_GetMetaObject();
}

igMetaObject *FUN_00130610(void) {
    return g_igVisualAttribute_metaObject[0];
}

void igViewportAttr_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igViewportAttr_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00485940[0], 7);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 0x27F);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 0x1BF);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    *(int *)((char *)(temp_s1) + 56) = FUN_0014bc80();
    *(char *)((char *)(temp_s1) + 38) = 0;
    *(char *)((char *)(temp_s1) + 40) = 1;
    *(char *)((char *)(temp_s1) + 39) = 1;
    *(char *)((char *)(temp_s1) + 44) = 3;
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6), 1.0f);
    igMetaObject_NameFields(temp_s0, &DAT_00485960[0], &DAT_00485980[0], &DAT_004859a0[0], temp_s2);
}

StringRefWord *StringRef_Destruct_00130720(StringRefWord *self,int delete_storage) {
    if(self) {
        char *value=self->value;
        if(value) {
            int *header=(int *)(value-8);
            if(--header[1]==0) StringChunk_ReleaseHeader((void *)header[0], (int)header);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

