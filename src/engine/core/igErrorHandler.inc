int igErrorHandler_Create(int arg0) {
    igErrorHandler_EnsureRegistered();
    return igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586590), (igMemoryPoolView *)arg0);
}

igMetaObject *igErrorHandler_GetMetaObject(void)
{
    igMetaObject *g = g_igErrorHandler_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igErrorHandler_EnsureRegistered();
    return g_igErrorHandler_metaObject[0];
}

int igErrorHandler_GetVTable(void) {
    igErrorHandler handler;

    igObject_InitHeader((igObject *)&handler);
    handler._vtable = (int)&DAT_00532530[0];
    return *(int *)((char *)&handler + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igErrorHandler_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igErrorHandler_Register);
}

void igErrorHandler_Register(void) {
    CoreLibrary_MarkRegistered();  /* Set-once guard that first runs the sibling registrars it chains to. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igErrorHandler_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igErrorHandler_GetMetaObjectFunction,
        igErrorHandler_className,
        8, /* instance size */
        igErrorHandler_GetVTable,
        igErrorHandler_RegisterExitCallback,
        igErrorHandler_StaticInitCallback,              /* static-initializer callback item (appended on fresh configuration) */
        0                                      /* 0-terminated dependency-callback list */
    );
}

void igErrorHandler_GetMetaObjectFunction(void) {
    igErrorHandler_GetMetaObject();
}

void igErrorHandler_RegisterExitCallback(void) {
    igMetaObject_AddExitCallback((int)&igErrorHandler_ExitCallback);
}

void igErrorHandler_StaticInitCallback(void) {
    thunk_igErrorHandler_GetInstance();
}

void igErrorHandler_ExitCallback(void) {
    igErrorHandler_ReleaseInstance();
}

