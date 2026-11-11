int FUN_0045cf10(void) {
    if (DAT_0058ccf8[0] == 0) {
        DAT_0058ccf8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058ccf8[0];
}

void *igViewMode_GetMetaObject(void) {
    struct G *g = ((G *)DAT_0058ccf8[0]);
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045d000();
    }
    return ((G *)DAT_0058ccf8[0]);
}

int igViewMode_GetVTable(void) {
    struct W o;
    igObject_InitHeader(&o);
    o.vt = DAT_00542960;
    igMatrix44f_SetIdentity(&o.f[2]);
    return *(int *)((char *)&o + *(int *)(((char *)DAT_00586dc8[0]) + 916));
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

    temp_s0 = (void *)DAT_0058ccf8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d1680[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004d1688[0], &DAT_004d1690[0], &DAT_004d1698[0], temp_s1);
}

