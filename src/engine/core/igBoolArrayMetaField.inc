void igBoolArrayMetaField_Create(int arg0) {
    igBoolArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586998), (igMemoryPoolView *)arg0);
}

igMetaObject *igBoolArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igBoolArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igBoolArrayMetaField_EnsureRegistered();
    return g_igBoolArrayMetaField_metaObject[0];
}

int igBoolArrayMetaField_GetVTable(void) {
    igBoolArrayMetaField o;
    int r;
    char *p;
    int *hdr;
    int c;

    igBoolMetaField_Init((int **)&o);
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
                StringChunk_ReleaseHeader((StringChunk *)(*hdr), (int)hdr);
            }
        }
    }
    return r;
}

void igBoolArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igBoolArrayMetaField_Register);
}

void igBoolArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igBoolArrayMetaField_metaObject),
        igBoolMetaField_Register,
        igBoolMetaField_GetPublishedMetaObject,
        igBoolArrayMetaField_GetMetaObjectFunction,
        igBoolArrayMetaField_className,
        0x38, /* instance size */
        igBoolArrayMetaField_GetVTable,
        &igBoolArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igBoolArrayMetaField_callbackList /* callback list */
    );
}

void igBoolArrayMetaField_GetMetaObjectFunction(void) {
    igBoolArrayMetaField_GetMetaObject();
}

igMetaObject *igBoolMetaField_GetPublishedMetaObject(void) {
    return g_igBoolMetaField_metaObject[0];
}

void igBoolArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igBoolArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igBoolArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igBoolArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004c1590[0], &DAT_004c1598[0], temp_s1);
}

void igBoolArrayMetaField_CreateDefaultDescriptor(void) {
    igBoolArrayMetaField *temp_s0;
    igBoolArrayMetaField *p;
    int len;

    if (DAT_005869a0[0] == 0) {
        DAT_005869a0[0] = ((igBoolArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igBoolArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        temp_s0 = DAT_005869a0[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)temp_s0);
            p = DAT_005869a0[0];
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            len = igMetaField_GetMetaFieldList()->_count;
            DAT_005869a0[0]->_internalIndex = len - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_005869a0[0]);
        }
    }
}

