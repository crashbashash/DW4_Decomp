igMetaObject *FUN_0014d680(void)
{
    igMetaObject *meta = g_igLineWidthExt_metaObject[0];
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    FUN_0014d6d0();
end:
    return g_igLineWidthExt_metaObject[0];
}

void FUN_0014d6d0(void)
{
    igMetaObject_RunStaticInit(igLineWidthExt_Register);
}

void igLineWidthExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igLineWidthExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_igLineWidthExt_GetMetaObject_0014d750,
        igLineWidthExt_className,
        0x18, /* instance size */
        0,
        &igLineWidthExt_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_FUN_0014d680(void) {
    FUN_0014d680();
}

void igLineWidthExt_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igLineWidthExt_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00488d10[0], 1);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1.0f);
    igMetaObject_NameFields(temp_s0, &DAT_00488d18[0], &DAT_00488d20[0], &DAT_00488d28[0], temp_s1);
}

