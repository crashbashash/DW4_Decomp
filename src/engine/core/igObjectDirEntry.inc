int FUN_002bd8f0(int arg0) {
    FUN_002bda10();
    return igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585B70), (MemoryPool *)arg0);
}

igMetaObject *igObjectDirEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectDirEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bda10();
    return g_igObjectDirEntry_metaObject[0];
}

int igObjectDirEntry_GetVTable(void) {
    Obj_2bd980 o;
    int r;

    igObject_InitHeader((struct ObjectHeader *)&o);
    o.f8 = 0;
    o.vt = &DAT_0052f040[0];
    o.a = 0;
    o.b = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
    o.vt = &DAT_0052f040[0];
    StringRef_Destruct_00130720(&o.b, -1);
    FUN_0019c840(&o.a, -1);
    FUN_0014f4e0(&o, 0);
    return r;
}

void FUN_002bda10(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igObjectDirEntry_Register);
}

void igObjectDirEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igObjectDirEntry_metaObject),
        igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        thunk_igObjectDirEntry_GetMetaObject,
        igObjectDirEntry_className,
        0x34, /* instance size */
        igObjectDirEntry_GetVTable,
        &igObjectDirEntry_InitFields,
        0, /* extra callback item */
        g_igObjectDirEntry_callbackList /* callback list */
    );
}

void thunk_igObjectDirEntry_GetMetaObject(void) {
    igObjectDirEntry_GetMetaObject();
}

int FUN_002bdab0(void) {
    return DAT_00586710[0];
}

