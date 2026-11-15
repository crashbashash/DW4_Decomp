igMetaObject *g_igPsx2Folder_metaObject;

igMetaObject *igPsx2Folder_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Folder_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2Folder_EnsureRegistered();
    return g_igPsx2Folder_metaObject;
}

int igPsx2Folder_GetVTable(void) {
    igPsx2Folder folder;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;
    igObject_InitHeader((igObject *)&folder);
    ps = (char *)&folder._folderName;
    *(int *)ps = 0;
    folder._vtable = (int)&g_igFolder_vtable[0];
    folder._vtable = (int)&g_igPsx2Folder_vtable[0];
    s0 = *(int *)((char *)&folder + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
    folder._vtable = (int)&g_igFolder_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*a1), (int)a1);
            }
        }
    }
    return s0;
}

void igPsx2Folder_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2Folder_Register);
}

void igPsx2Folder_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igPsx2Folder_metaObject,
        (igMetaObjectRegisterFunction)igFolder_Register,
        igFolder_GetPublishedMetaObject,
        igPsx2Folder_GetMetaObjectFunction,
        "igPsx2Folder",
        0xC,
        igPsx2Folder_GetVTable,
        0,
        0,
        0
    );
}

igMetaObject *igFolder_GetPublishedMetaObject(void) {
    return g_igFolder_metaObject;
}

