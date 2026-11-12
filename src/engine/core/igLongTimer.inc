igMetaObject *FUN_002c1860(void)
{
    unsigned char ready;
    if (g_igLongTimer_metaObject[0] != 0) {
        ready = (g_igLongTimer_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_002c18b0();
done:
    return g_igLongTimer_metaObject[0];
}

void FUN_002c18b0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igLongTimer_Register);
}

void igLongTimer_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igLongTimer_metaObject,
        igTimer_Register,
        igTimer_GetPublishedMetaObject,
        thunk_igLongTimer_GetMetaObject_002b7b60,
        igLongTimer_className,
        0x28, /* instance size */
        0,
        &igLongTimer_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

igMetaObject *FUN_002c1930(void) {
    return g_igTimer_metaObject[0];
}

void igLongTimer_InitFields(void) {
    int temp_s1;
    void *temp_s0;
    temp_s0 = (void *)(((void * *)g_igLongTimer_metaObject)[0]);
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004c04a0[0], 4);
    FUN_002d3890((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004c04b0[0], (igMetaField ***)&DAT_004c04c0[0], &DAT_004c04d0[0], temp_s1);
    *(int *)((char *)(((void * *)g_igLongTimer_metaObject)[0]) + 60) = (int)thunk_igPsx2LongTimer_GetMetaObject;
}

