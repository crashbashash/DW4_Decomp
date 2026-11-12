igMetaObject *igExternalDirEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igExternalDirEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c5550();
    return g_igExternalDirEntry_metaObject[0];
}

int igExternalDirEntry_GetVTable(void) {
    union U_2c54a0 u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;
    igObject_InitHeader((ObjectHeader *)u.b);
    *(int *)&u.b[8] = 0;
    u.vt = (int)&DAT_00530360[0];
    *(int *)&u.b[28] = 0;
    *(int *)&u.b[32] = 0;
    *(int *)&u.b[40] = 0;
    t = *(int *)&u.b[*(int *)((char *)(((void * *)g_objectSystem)[0]) + 916)];
    u.vt = (int)&DAT_00530360[0];
    StringRef_Destruct_00130720(&u.b[40], -1);
    StringRef_Destruct_00130720(&u.b[32], -1);
    StringRef_Destruct_00130720(&u.b[28], -1);
    FUN_0014f4e0(u.b, 0);
    return t;
}

void FUN_002c5550(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igExternalDirEntry_Register);
}

void igExternalDirEntry_Register(void) {
    FUN_002b5d50();  /* Set-once guard that first runs the sibling registrars it chains to. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igExternalDirEntry_metaObject),
        igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        thunk_igExternalDirEntry_GetMetaObject,
        igExternalDirEntry_className,
        0x2C, /* instance size */
        igExternalDirEntry_GetVTable,
        FUN_002c55f0,
        0,                                          /* static-initializer callback item (appended on fresh configuration) */
        g_igExternalDirEntry_callbackList  /* 0-terminated dependency-callback list */
    );
}

void thunk_igExternalDirEntry_GetMetaObject(void) {
    igExternalDirEntry_GetMetaObject();
}

