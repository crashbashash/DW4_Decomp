igMetaObject *igUnsignedLongArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedLongArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedLongArrayMetaField_EnsureRegistered();
    return g_igUnsignedLongArrayMetaField_metaObject[0];
}

int igUnsignedLongArrayMetaField_GetVTable(void) {
    igUnsignedLongArrayMetaField obj;
    char *chars;
    int *header;
    int refCount;
    int vtable;
    igUnsignedLongMetaField_Init((int **)&obj);
    obj._vtable = (int)&g_igUnsignedLongArrayMetaField_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj._vtable = (int)&g_igMetaField_vtable[0];
    if (&obj._fieldName != 0) {
        chars = (char *)obj._fieldName;
        if (chars != 0) {
            header = (int *)(chars - 8);
            refCount = *(int *)(chars - 4) - 1;
            *(int *)(chars - 4) = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return vtable;
}

void igUnsignedLongArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedLongArrayMetaField_Register);
}

void igUnsignedLongArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igUnsignedLongArrayMetaField_metaObject,
        (igMetaObjectRegisterFunction)igUnsignedLongMetaField_Register,
        igUnsignedLongMetaField_GetPublishedMetaObject,
        igUnsignedLongArrayMetaField_GetMetaObjectFunction,
        igUnsignedLongArrayMetaField_className,
        0x38,
        igUnsignedLongArrayMetaField_GetVTable,
        igUnsignedLongArrayMetaField_InitFields,
        0,
        (igMetaObjectCallback *)g_igUnsignedLongArrayMetaField_callbackList
    );
}

void igUnsignedLongArrayMetaField_GetMetaObjectFunction(void) {
    igUnsignedLongArrayMetaField_GetMetaObject();
}

igMetaObject *igUnsignedLongMetaField_GetPublishedMetaObject(void) {
    return g_igUnsignedLongMetaField_metaObject[0];
}

void igUnsignedLongArrayMetaField_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)g_igUnsignedLongArrayMetaField_metaObject[0];
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igUnsignedLongArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, first)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igUnsignedLongArrayMetaField_fieldTable[0], (igMetaField ***)&g_igUnsignedLongArrayMetaField_fieldDescriptors[0], &g_igUnsignedLongArrayMetaField_fieldOffsets[0], first);
}

void igUnsignedLongArrayMetaField_CreateDefaultDescriptor(void) {
    igUnsignedLongArrayMetaField *created;
    igUnsignedLongArrayMetaField *p;

    if (g_igUnsignedLongArrayMetaField_descriptor[0] == 0) {
        g_igUnsignedLongArrayMetaField_descriptor[0] = ((igUnsignedLongArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igUnsignedLongArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        created = g_igUnsignedLongArrayMetaField_descriptor[0];
        if (created != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)created);
            p = g_igUnsignedLongArrayMetaField_descriptor[0];
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long)(long long)p->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(p);
            }
            g_igUnsignedLongArrayMetaField_descriptor[0]->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igUnsignedLongArrayMetaField_descriptor[0]);
        }
    }
}

