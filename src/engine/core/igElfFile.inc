void thunk_igElfFile_GetMetaObject(void) {
    igElfFile_GetMetaObject();
}

void * FUN_002cec00(int arg0) {
    FUN_002ced70();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586C00), (igMemoryPoolView *)arg0));
}

igMetaObject *igElfFile_GetMetaObject(void)
{
    igMetaObject *g = g_igElfFile_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002ced70();
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
    elf._vtable = (int)&DAT_0052e010[0];
    q1 = (char *)&elf._fileName;
    *(int *)q1 = 0;
    q2 = (igObject *)&elf._file;
    *(int *)q2 = 0;
    elf._vtable = (int)&DAT_0052e0a0[0];
    r = *(int *)((char *)&elf + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    elf._vtable = (int)&DAT_0052e010[0];
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

void FUN_002ced70(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igElfFile_Register);
}

void igElfFile_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igElfFile_metaObject),
        igProgramFile_Register,
        igProgramFile_GetPublishedMetaObject,
        thunk_igElfFile_GetMetaObject,
        igElfFile_className,
        0x64, /* instance size */
        igElfFile_GetVTable,
        &igElfFile_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

int FUN_002cedf0(void) {
    return ((int *)g_igProgramFile_metaObject)[0];
}

void igElfFile_InitFields(void) {
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    int temp_s1;
    void *temp_s0;

    ((igMetaObject *)g_igElfFile_metaObject[0])->_persistent = 0;
    temp_s0 = (void *)(g_igElfFile_metaObject[0]);
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igElfFile_ctorTable[0], 9);
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)));
    ((igMetaField *)temp_v0)->_size = 0x34;
    ((igMetaField *)temp_v0)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1)))->_persistent = 0;
    temp_v0_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2)));
    ((igMetaField *)temp_v0_2)->_size = 4;
    ((igMetaField *)temp_v0_2)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3)))->_persistent = 0;
    temp_v0_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4)));
    ((igMetaField *)temp_v0_3)->_size = 4;
    ((igMetaField *)temp_v0_3)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5)))->_persistent = 0;
    temp_v0_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6)));
    ((igMetaField *)temp_v0_4)->_size = 4;
    ((igMetaField *)temp_v0_4)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7)))->_persistent = 0;
    temp_v0_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8)));
    ((igMetaField *)temp_v0_5)->_size = 4;
    ((igMetaField *)temp_v0_5)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igElfFile_fieldTable[0], (igMetaField ***)&DAT_004c1b90[0], &DAT_004c1bc0[0], temp_s1);
}

