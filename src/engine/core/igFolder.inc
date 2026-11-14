void * igFolder_Create(int arg0) {
    igFolder_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586368), (igMemoryPoolView *)arg0));
}

igMetaObject *igFolder_GetMetaObject(void)
{
    igMetaObject *g = g_igFolder_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFolder_EnsureRegistered();
    return g_igFolder_metaObject[0];
}

int igFolder_GetVTable(void) {
    igFolder folder;
    void **q;
    int *temp_a1;
    int temp_s0;
    int temp_v0;
    void *temp_v1;

    igObject_InitHeader((igObject *)&folder);
    q = (void **)&folder._folderName;
    folder._vtable = (int)(&DAT_0052fee0[0]);
    *q = 0;
    temp_s0 = *(int *)((char *)&folder + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    folder._vtable = (int)(&DAT_0052fee0[0]);
    if (q != 0) {
        temp_v1 = *q;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return temp_s0;
}

void igFolder_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igFolder_Register);
}

void igFolder_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igFolder_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igFolder_GetMetaObjectFunction,
        igFolder_className,
        0xC, /* instance size */
        igFolder_GetVTable,
        &igFolder_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igFolder_GetMetaObjectFunction(void) {
    igFolder_GetMetaObject();
}

void igFolder_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(((void * *)g_igFolder_metaObject)[0]);
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igFolder_ctorTable[0], 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igFolder_fieldTable[0], (igMetaField ***)&DAT_004c0aa8[0], &DAT_004c0ab0[0], temp_s1);
    *(int *)((char *)(((void * *)g_igFolder_metaObject)[0]) + 60) = (int)(&igPsx2Folder_GetMetaObjectFunction);
}

