igMetaObject *igRawRefArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igRawRefArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRawRefArrayMetaField_EnsureRegistered();
    return g_igRawRefArrayMetaField_metaObject[0];
}

int igRawRefArrayMetaField_GetVTable(void) {
    igRawRefArrayMetaField f;
    int result;
    int *header;
    int refs;

    igRawRefMetaField_Init((int **)&f);
    f._vtable = (int)&g_igRawRefArrayMetaField_vtable[0];
    result = *(int *)((char *)&f + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    f._vtable = (int)&g_igMetaField_vtable[0];
    if (&f._fieldName != 0) {
        if (((int *)f._fieldName) != 0) {
            header = ((int *)f._fieldName) - 2;
            refs = ((int *)f._fieldName)[-1] - 1;
            ((int *)f._fieldName)[-1] = refs;
            if (refs == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return result;
}

void igRawRefArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igRawRefArrayMetaField_Register);
}

void igRawRefArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igRawRefArrayMetaField_metaObject,
        (igMetaObjectRegisterFunction)igRawRefMetaField_Register,
        igRawRefMetaField_GetPublishedMetaObject,
        igRawRefArrayMetaField_GetMetaObjectFunction,
        igRawRefArrayMetaField_className,
        0x3C,
        igRawRefArrayMetaField_GetVTable,
        igRawRefArrayMetaField_InitFields,
        0,
        (igMetaObjectCallback *)g_igRawRefArrayMetaField_callbackList
    );
}

void igRawRefArrayMetaField_GetMetaObjectFunction(void) {
    igRawRefArrayMetaField_GetMetaObject();
}

igMetaObject *igRawRefMetaField_GetPublishedMetaObject(void) {
    return g_igRawRefMetaField_metaObject[0];
}

void igRawRefArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igRawRefArrayMetaField_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igRawRefArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igRawRefArrayMetaField_fieldTable[0], (igMetaField ***)&g_igRawRefArrayMetaField_fieldDescriptors[0], &g_igRawRefArrayMetaField_fieldOffsets[0], base);
}

void igRawRefArrayMetaField_CreateDefaultDescriptor(void) {
    igRawRefArrayMetaField *descriptor;
    igRawRefArrayMetaField *p;

    if (g_igRawRefArrayMetaField_descriptor[0] == 0) {
        g_igRawRefArrayMetaField_descriptor[0] = ((igRawRefArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igRawRefArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        descriptor = g_igRawRefArrayMetaField_descriptor[0];
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            p = g_igRawRefArrayMetaField_descriptor[0];
            p->_refCount -= 1;
            if ((p->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(p);
            }
            g_igRawRefArrayMetaField_descriptor[0]->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igRawRefArrayMetaField_descriptor[0]);
        }
    }
}

