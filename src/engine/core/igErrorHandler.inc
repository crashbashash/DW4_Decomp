igMetaObject *g_igErrorHandler_metaObject;

int igErrorHandler_Create(int allocator) {
    igErrorHandler_EnsureRegistered();
    return igMetaObject_CreateInstance(g_igErrorHandler_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igErrorHandler_GetMetaObject(void)
{
    igMetaObject *g = g_igErrorHandler_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igErrorHandler_EnsureRegistered();
    return g_igErrorHandler_metaObject;
}

int igErrorHandler_GetVTable(void) {
    igErrorHandler handler;

    igObject_InitHeader((igObject *)&handler);
    handler._vtable = (int)&g_igErrorHandler_vtable[0];
    return *(int *)((char *)&handler + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
}

void igErrorHandler_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igErrorHandler_Register);
}

void igErrorHandler_Register(void) {
    CoreLibrary_MarkRegistered();  /* Set-once guard that first runs the sibling registrars it chains to. */
    igMetaObject_RegisterClass(
        0,
        &g_igErrorHandler_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igErrorHandler_GetMetaObjectFunction,
        "igErrorHandler",
        8,
        igErrorHandler_GetVTable,
        igErrorHandler_RegisterExitCallback,
        igErrorHandler_StaticInitCallback,
        0
    );
}

void igErrorHandler_GetMetaObjectFunction(void) {
    igErrorHandler_GetMetaObject();
}

void igErrorHandler_RegisterExitCallback(void) {
    igMetaObject_AddExitCallback((int)&igErrorHandler_ExitCallback);
}

void igErrorHandler_StaticInitCallback(void) {
    igErrorHandler_GetInstanceAlias();
}

void igErrorHandler_ExitCallback(void) {
    igErrorHandler_ReleaseInstance();
}

