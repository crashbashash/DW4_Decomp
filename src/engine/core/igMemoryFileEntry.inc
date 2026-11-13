void * FUN_002c0b60(int arg0) {
    FUN_002c0c80();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585F48), (MemoryPool *)arg0));
}

igMetaObject *igMemoryFileEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryFileEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c0c80();
    return g_igMemoryFileEntry_metaObject[0];
}

int igMemoryFileEntry_GetVTable(void) {
    union U_2c0bf0 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;
    igObject_InitHeader((ObjectHeader *)u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_00532910[0];
    s0 = *(int *)&u.b[*(int *)((char *)(((void * *)g_objectSystem)[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*a1), (int)a1);
            }
        }
    }
    return s0;
}

void FUN_002c0c80(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryFileEntry_Register);
}

void igMemoryFileEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMemoryFileEntry_metaObject),
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igMemoryFileEntry_GetMetaObject,
        igMemoryFileEntry_className,
        0x14, /* instance size */
        igMemoryFileEntry_GetVTable,
        &igMemoryFileEntry_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMemoryFileEntry_GetMetaObject(void) {
    igMemoryFileEntry_GetMetaObject();
}

void igMemoryFileEntry_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igMemoryFileEntry_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igMemoryFileEntry_ctorTable[0], 2);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igMemoryFileEntry_fieldTable[0], (igMetaField ***)&DAT_004c02e8[0], &DAT_004c02f0[0], temp_s1);
}

