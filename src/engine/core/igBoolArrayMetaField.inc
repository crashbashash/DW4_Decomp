void igBoolArrayMetaField_Create(int pool) {
    igBoolArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586998), (igMemoryPoolView *)pool);
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
    o._vtable = (int)&g_igBoolArrayMetaField_vtable[0];
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
        0,
        g_igBoolArrayMetaField_metaObject,
        (igMetaObjectRegisterFunction)igBoolMetaField_Register,
        igBoolMetaField_GetPublishedMetaObject,
        igBoolArrayMetaField_GetMetaObjectFunction,
        igBoolArrayMetaField_className,
        0x38,
        igBoolArrayMetaField_GetVTable,
        igBoolArrayMetaField_InitFields,
        0,
        (igMetaObjectCallback *)g_igBoolArrayMetaField_callbackList
    );
}

void igBoolArrayMetaField_GetMetaObjectFunction(void) {
    igBoolArrayMetaField_GetMetaObject();
}

igMetaObject *igBoolMetaField_GetPublishedMetaObject(void) {
    return g_igBoolMetaField_metaObject[0];
}

void igBoolArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igBoolArrayMetaField_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igBoolArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igBoolArrayMetaField_fieldTable[0], (igMetaField ***)&g_igBoolArrayMetaField_fieldDescriptors[0], &g_igBoolArrayMetaField_fieldOffsets[0], base);
}

void igBoolArrayMetaField_CreateDefaultDescriptor(void) {
    igBoolArrayMetaField *descriptor;
    igBoolArrayMetaField *p;
    int len;

    if (g_igBoolArrayMetaField_descriptor[0] == 0) {
        g_igBoolArrayMetaField_descriptor[0] = ((igBoolArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igBoolArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        descriptor = g_igBoolArrayMetaField_descriptor[0];
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            p = g_igBoolArrayMetaField_descriptor[0];
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            len = igMetaField_GetMetaFieldList()->_count;
            g_igBoolArrayMetaField_descriptor[0]->_internalIndex = len - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igBoolArrayMetaField_descriptor[0]);
        }
    }
}

