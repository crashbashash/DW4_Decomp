void FUN_002cce40(int arg0) {
    FUN_002ccf60();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586998), (MemoryPool *)arg0);
}

igMetaObject *igBoolArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igBoolArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002ccf60();
    return g_igBoolArrayMetaField_metaObject[0];
}

int igBoolArrayMetaField_GetVTable(void) {
    igBoolArrayMetaField o;
    int r;
    char *p;
    int *hdr;
    int c;

    FUN_002d37f0((int **)&o);
    o._vtable = (int)&DAT_00530c80[0];
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        p = (char *)o._fieldName;
        if (p != 0) {
            hdr = (int *)(p - 8);
            c = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hdr), (int)hdr);
            }
        }
    }
    return r;
}

void FUN_002ccf60(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igBoolArrayMetaField_Register);
}

void igBoolArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igBoolArrayMetaField_metaObject),
        igBoolMetaField_Register,
        igBoolMetaField_GetPublishedMetaObject,
        thunk_igBoolArrayMetaField_GetMetaObject,
        igBoolArrayMetaField_className,
        0x38, /* instance size */
        igBoolArrayMetaField_GetVTable,
        &igBoolArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igBoolArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igBoolArrayMetaField_GetMetaObject(void) {
    igBoolArrayMetaField_GetMetaObject();
}

igMetaObject *FUN_002cd000(void) {
    return g_igBoolMetaField_metaObject[0];
}

void igBoolArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igBoolArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igBoolArrayMetaField_ctorTable[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igBoolArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004c1590[0], &DAT_004c1598[0], temp_s1);
}

void FUN_002cd0a0(void) {
    igBoolArrayMetaField *temp_s0;
    igBoolArrayMetaField *p;
    int len;

    if (DAT_005869a0[0] == 0) {
        DAT_005869a0[0] = ((igBoolArrayMetaField *)igMetaObject_CreateInstance((CreateMeta *)g_igBoolArrayMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        temp_s0 = DAT_005869a0[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)FUN_002fc250(), (RefHeader *)temp_s0);
            p = DAT_005869a0[0];
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            len = ((PointerList *)FUN_002fc250())->count;
            DAT_005869a0[0]->_internalIndex = len - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_005869a0[0]);
        }
    }
}

