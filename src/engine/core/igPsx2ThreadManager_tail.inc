igMetaObject *igPsx2ThreadManager_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ThreadManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cf360();
    return g_igPsx2ThreadManager_metaObject[0];
}

int igPsx2ThreadManager_GetVTable(void) {
    struct Obj_2cf320 o;
    igObject_InitHeader((struct ObjectHeader *)&o);
    o.vt = &DAT_0052d750[0];
    return *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002cf360(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2ThreadManager_Register);
}

void igPsx2ThreadManager_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPsx2ThreadManager_metaObject),
        igThreadManager_Register,
        igThreadManager_GetPublishedMetaObject,
        thunk_igPsx2ThreadManager_GetMetaObject,
        igPsx2ThreadManager_className,
        0x10, /* instance size */
        igPsx2ThreadManager_GetVTable,
        &igPsx2ThreadManager_InitFields_002cf3f0[0],     /* Field adder. */
        0,                                               /* extra callback-vector item (none) */
        0                                                /* zero-terminated callback-vector item list (none) */
    );
}

int FUN_002cf3e0(void) {
    return ((int *)g_igThreadManager_metaObject)[0];
}

void FUN_002cf3f0(void) {
    *(int *)((char *)(g_igPsx2ThreadManager_metaObject[0]) + 64) = (int)(&thunk_igThreadManager_GetMetaObject);
}

