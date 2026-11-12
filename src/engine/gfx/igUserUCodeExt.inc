igMetaObject *igUserUCodeExt_GetMetaObject(void)
{
    igMetaObject *g = g_igUserUCodeExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014bbb0();
    return g_igUserUCodeExt_metaObject[0];
}

void FUN_0014bbb0(void)
{
    igMetaObject_RunStaticInit(igUserUCodeExt_Register);
}

void igUserUCodeExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igUserUCodeExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_igUserUCodeExt_GetMetaObject,
        igUserUCodeExt_className,
        0x14, /* instance size */
        0,
        FUN_0014bc50,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igUserUCodeExt_GetMetaObject(void) {
    igUserUCodeExt_GetMetaObject();
}

int FUN_0014bc40(void) {
    return g_igContextExt_metaObject[0];
}

void FUN_0014bc50(void) {
    *(int *)((char *)(g_igUserUCodeExt_metaObject[0]) + 60) = (int)(&thunk_igPsx2UserUCodeExt_GetMetaObject);
}

