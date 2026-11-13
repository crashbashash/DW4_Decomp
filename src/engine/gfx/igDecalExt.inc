igMetaObject *FUN_0014f8d0(void)
{
    igMetaObject *meta = g_igDecalExt_metaObject[0];
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    FUN_0014f920();
end:
    return g_igDecalExt_metaObject[0];
}

void FUN_0014f920(void)
{
    igMetaObject_RunStaticInit(igDecalExt_Register);
}

void igDecalExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igDecalExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_FUN_0014f8d0,
        igDecalExt_className,
        0x18, /* instance size */
        0,
        &igDecalExt_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_FUN_0014f8d0(void) {
    FUN_0014f8d0();
}

void igDecalExt_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(g_igDecalExt_metaObject[0]);
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igDecalExt_ctorTable[0], 1);
    igMetaObject_NameFields(temp_s0, &g_igDecalExt_fieldTable[0], &DAT_00489080[0], &DAT_00489088[0], temp_s1);
    *(int *)((char *)(g_igDecalExt_metaObject[0]) + 60) = (int)(&thunk_igPsx2DecalExt_GetMetaObject);
}

