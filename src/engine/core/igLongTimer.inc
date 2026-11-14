igMetaObject *igLongTimer_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igLongTimer_metaObject[0] != 0) {
        ready = (g_igLongTimer_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igLongTimer_EnsureRegistered();
done:
    return g_igLongTimer_metaObject[0];
}

void igLongTimer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igLongTimer_Register);
}

void igLongTimer_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,
        g_igLongTimer_metaObject,
        (igMetaObjectRegisterFunction)igTimer_Register,
        igTimer_GetPublishedMetaObject,
        thunk_igLongTimer_GetMetaObject,
        igLongTimer_className,
        0x28,
        0,
        igLongTimer_InitFields,
        0,
        0
    );
}

igMetaObject *igTimer_GetPublishedMetaObject(void) {
    return g_igTimer_metaObject[0];
}

void igLongTimer_InitFields(void) {
    int base;
    void *meta;
    meta = (void *)(((void * *)g_igLongTimer_metaObject)[0]);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igLongTimer_ctorTable[0], 4);
    igBoolMetaField_SetDefaultValue((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igLongTimer_fieldTable[0], (igMetaField ***)&g_igLongTimer_fieldDescriptors[0], &g_igLongTimer_fieldOffsets[0], base);
    *(int *)((char *)(((void * *)g_igLongTimer_metaObject)[0]) + 60) = (int)igPsx2LongTimer_GetMetaObjectFunction;
}

