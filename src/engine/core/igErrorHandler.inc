int FUN_002c5e10(int arg0) {
    FUN_002c5ee0();
    return igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586590), (MemoryPool *)arg0);
}

igMetaObject *igErrorHandler_GetMetaObject(void)
{
    igMetaObject *g = g_igErrorHandler_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c5ee0();
    return g_igErrorHandler_metaObject[0];
}

int igErrorHandler_GetVTable(void) {
    struct Obj_2c5ea0 obj;
    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00532530[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
}

void FUN_002c5ee0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igErrorHandler_Register);
}

void igErrorHandler_Register(void) {
    FUN_002b5d50();  /* Set-once guard that first runs the sibling registrars it chains to. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igErrorHandler_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igErrorHandler_GetMetaObject,
        igErrorHandler_className,
        8, /* instance size */
        igErrorHandler_GetVTable,
        FUN_002c5f80,
        thunk_thunk_FUN_002dca20,              /* static-initializer callback item (appended on fresh configuration) */
        0                                      /* 0-terminated dependency-callback list */
    );
}

void thunk_igErrorHandler_GetMetaObject(void) {
    igErrorHandler_GetMetaObject();
}

void FUN_002c5f80(void) {
    FUN_002fe480((int)&thunk_FUN_002dc9c0);
}

void thunk_thunk_FUN_002dca20(void) {
    thunk_FUN_002dca20();
}

void thunk_FUN_002dc9c0(void) {
    FUN_002dc9c0();
}

