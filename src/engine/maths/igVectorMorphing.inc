igMetaObject *FUN_00186db0(void)
{
    igMetaObject *meta = g_igVectorMorphing_metaObject[0];
    bool ready;

    if (meta) {
        ready = meta->_validity & 4;
        if (ready != false)
            goto end;
    }
    FUN_00186e40();
end:
    return g_igVectorMorphing_metaObject[0];
}

int igVectorMorphing_GetVTable(void) {
    struct Obj2 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_005280a0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00186e40(void)
{
    igMetaObject_RunStaticInit(igVectorMorphing_Register);
}

void igVectorMorphing_Register(void) {
    FUN_00186a40();  /* Set-once guard (gp-relative byte flag) that chains to sibling registrars. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVectorMorphing_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igVectorMorphing_GetMetaObject_00186ec0,
        igVectorMorphing_className,
        8, /* instance size */
        igVectorMorphing_GetVTable,
        0,
        FUN_00186ed0,                                  /* static-initializer callback item (appended on fresh configuration) */
        0                                              /* 0-terminated dependency-callback list */
    );
}

void thunk_FUN_00186db0(void) {
    FUN_00186db0();
}

void FUN_00186ed0(void) {
    FUN_0018ec10();
}

