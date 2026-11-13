igMetaObject *FUN_0045cf10(void) {
    if (g_igViewMode_metaObject[0] == 0) {
        g_igViewMode_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igViewMode_metaObject[0];
}

void *igViewMode_GetMetaObject(void) {
    igMetaObject *g = g_igViewMode_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0045d000();
    }
    return g_igViewMode_metaObject[0];
}

int igViewMode_GetVTable(void) {
    struct W o;
    igObject_InitHeader(&o);
    o.vt = DAT_00542960;
    igMatrix44f_SetIdentity(&o.f[2]);
    return *(int *)((char *)&o + *(int *)(((char *)g_objectSystem[0]) + 916));
}

void FUN_0045d000(void)
{
    igMetaObject_RunStaticInit(igViewMode_Register);
}

void igViewMode_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewMode_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igViewMode_GetMetaObject,
        igViewMode_className,
        0x4C, /* instance size */
        igViewMode_GetVTable,
        &igViewMode_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igViewMode_GetMetaObject(void) {
    igViewMode_GetMetaObject();
}

void igViewMode_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igViewMode_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igViewMode_ctorTable[0], 1);
    igMetaObject_NameFields(temp_s0, &g_igViewMode_fieldTable[0], &DAT_004d1690[0], &DAT_004d1698[0], temp_s1);
}

