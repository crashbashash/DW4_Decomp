void igElfFile_GetMetaObjectFunction(void) {
    igElfFile_GetMetaObject();
}

void * igElfFile_Create(int pool) {
    igElfFile_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586C00), (igMemoryPoolView *)pool));
}

igMetaObject *igElfFile_GetMetaObject(void)
{
    igMetaObject *g = g_igElfFile_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igElfFile_EnsureRegistered();
    return g_igElfFile_metaObject[0];
}

int igElfFile_GetVTable(void) {
    igElfFile elf;
    int r;
    int *tv1, *ta1;
    int tc1;
    char *q1;
    igObject *q2;
    igObject_InitHeader((igObject *)&elf);
    elf._vtable = (int)&g_igProgramFile_vtable[0];
    q1 = (char *)&elf._fileName;
    *(int *)q1 = 0;
    q2 = (igObject *)&elf._file;
    *(int *)q2 = 0;
    elf._vtable = (int)&g_igElfFile_vtable[0];
    r = *(int *)((char *)&elf + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    elf._vtable = (int)&g_igProgramFile_vtable[0];
    if (q2 != 0) {
        q2 = *(igObject **)q2;
        if (q2 != 0) {
            q2->_refCount = (int)((int) (q2->_refCount - 1));
            if (((unsigned long long) ((long long)(int) q2->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    if (q1 != 0) {
        tv1 = *(int **)q1;
        if (tv1 != 0) {
            ta1 = tv1 - 2;
            tc1 = tv1[-1] - 1;
            tv1[-1] = tc1;
            if (tc1 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*ta1), (int)ta1);
            }
        }
    }
    return r;
}

void igElfFile_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igElfFile_Register);
}

void igElfFile_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igElfFile_metaObject,
        (igMetaObjectRegisterFunction)igProgramFile_Register,
        (igMetaObjectGetFunction)igProgramFile_GetPublishedMetaObject,
        igElfFile_GetMetaObjectFunction,
        igElfFile_className,
        0x64,
        igElfFile_GetVTable,
        igElfFile_InitFields,
        0,
        0
    );
}

int igProgramFile_GetPublishedMetaObject(void) {
    return ((int *)g_igProgramFile_metaObject)[0];
}

void igElfFile_InitFields(void) {
    void *headerField;
    void *sectionHeaderStringTableField;
    void *sectionHeadersField;
    void *symbolStringTableField;
    void *symbolsField;
    int first;
    void *meta;

    ((igMetaObject *)g_igElfFile_metaObject[0])->_persistent = 0;
    meta = (void *)(g_igElfFile_metaObject[0]);
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igElfFile_ctorTable[0], 9);
    headerField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first)));
    ((igMetaField *)headerField)->_size = 0x34;
    ((igMetaField *)headerField)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 1)))->_persistent = 0;
    sectionHeaderStringTableField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 2)));
    ((igMetaField *)sectionHeaderStringTableField)->_size = 4;
    ((igMetaField *)sectionHeaderStringTableField)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 3)))->_persistent = 0;
    sectionHeadersField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 4)));
    ((igMetaField *)sectionHeadersField)->_size = 4;
    ((igMetaField *)sectionHeadersField)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 5)))->_persistent = 0;
    symbolStringTableField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 6)));
    ((igMetaField *)symbolStringTableField)->_size = 4;
    ((igMetaField *)symbolStringTableField)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 7)))->_persistent = 0;
    symbolsField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 8)));
    ((igMetaField *)symbolsField)->_size = 4;
    ((igMetaField *)symbolsField)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igElfFile_fieldTable[0], (igMetaField ***)&g_igElfFile_fieldDescriptors[0], &g_igElfFile_fieldOffsets[0], first);
}

