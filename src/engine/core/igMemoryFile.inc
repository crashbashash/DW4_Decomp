void FUN_002c0690(int arg0) {
    FUN_002c0890();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585F18), (igMemoryPoolView *)arg0);
}

igMetaObject *igMemoryFile_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryFile_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c0890();
    return g_igMemoryFile_metaObject[0];
}

int igMemoryFile_GetVTable(void) {
    igMemoryFile file;
    int temp_s0;

    igObject_InitHeader((igObject *)&file);
    file._name = 0;
    file._fileName = 0;
    file._completeFilename = 0;
    file._vtable = (int)(&DAT_0052f7b0[0]);
    temp_s0 = *(int *)((char *)&file + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    file._vtable = (int)(&DAT_0052f7b0[0]);
    FUN_002c0790((igFile *)&file, 0);
    return temp_s0;
}

void *FUN_002c0790(igFile *arg0, short arg1) {
    void *p;
    int *h;
    int rc;

    if (arg0 != 0) {
        arg0->_vtable = (int)&DAT_00530150[0];
        if (&arg0->_completeFilename) {
            p = (void *)arg0->_completeFilename;
            if (p != 0) {
                h = (int *)((char *)(p) - 8);
                rc = *(int *)((char *)(p) - 4) - 1;
                *(int *)((char *)(p) - 4) = rc;
                if (rc == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)(*h), (int)h);
                }
            }
        }
        if (&arg0->_fileName) {
            p = (void *)arg0->_fileName;
            if (p != 0) {
                h = (int *)((char *)(p) - 8);
                rc = *(int *)((char *)(p) - 4) - 1;
                *(int *)((char *)(p) - 4) = rc;
                if (rc == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)(*h), (int)h);
                }
            }
        }
        if (arg0 != 0) {
            arg0->_vtable = (int)&g_igNamedObject_vtable[0];
            if (&arg0->_name) {
                p = (void *)arg0->_name;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader((StringChunk *)(*h), (int)h);
                    }
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810((int)arg0);
        }
    }
    return arg0;
}

void FUN_002c0890(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryFile_Register);
}

void igMemoryFile_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMemoryFile_metaObject),
        igFile_Register,
        igFile_GetPublishedMetaObject,
        thunk_igMemoryFile_GetMetaObject,
        igMemoryFile_className,
        0x3C, /* instance size */
        igMemoryFile_GetVTable,
        &igMemoryFile_InitFields,
        thunk_FUN_002ef9a0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMemoryFile_GetMetaObject(void) {
    igMemoryFile_GetMetaObject();
}

igMetaObject *FUN_002c0930(void) {
    return g_igFile_metaObject[0];
}

void igMemoryFile_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(g_igMemoryFile_metaObject[0]);
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igMemoryFile_ctorTable[0], 4);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igMemoryFile_fieldTable[0], (igMetaField ***)&DAT_004c02b0[0], &DAT_004c02c0[0], temp_s1);
    *(int *)((char *)(g_igMemoryFile_metaObject[0]) + 64) = (int)(&thunk_igFile_GetMetaObject);
    FUN_002fe480((int)&thunk_FUN_002ef9d0);
}

