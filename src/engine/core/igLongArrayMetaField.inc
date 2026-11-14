igMetaObject *igLongArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igLongArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igLongArrayMetaField_EnsureRegistered();
    return g_igLongArrayMetaField_metaObject[0];
}

int igLongArrayMetaField_GetVTable(void) {
    igLongArrayMetaField o;
    int r;
    char *p;
    int *hdr;
    int c;

    igMetaField_Init((igMetaField *)&o);
    o._vtable = (int)&g_igLongArrayMetaField_vtable[0];
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

void igLongArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igLongArrayMetaField_Register);
}

void igLongArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igLongArrayMetaField_metaObject,
        (igMetaObjectRegisterFunction)igLongMetaField_Register,
        igLongMetaField_GetPublishedMetaObject,
        igLongArrayMetaField_GetMetaObjectFunction,
        igLongArrayMetaField_className,
        0x38,
        igLongArrayMetaField_GetVTable,
        igLongArrayMetaField_InitFields,
        0,
        (igMetaObjectCallback *)g_igLongArrayMetaField_callbackList
    );
}

void igLongArrayMetaField_GetMetaObjectFunction(void) {
    igLongArrayMetaField_GetMetaObject();
}

igMetaObject *igLongMetaField_GetPublishedMetaObject(void) {
    return g_igLongMetaField_metaObject[0];
}

void igLongArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igLongArrayMetaField_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igLongArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igLongArrayMetaField_fieldTable[0], (igMetaField ***)&g_igLongArrayMetaField_fieldDescriptors[0], &g_igLongArrayMetaField_fieldOffsets[0], base);
}

void igLongArrayMetaField_CreateDefaultDescriptor(void) {
    igLongArrayMetaField *descriptor;
    igLongArrayMetaField *p;

    if (g_igLongArrayMetaField_descriptor[0] == 0) {
        g_igLongArrayMetaField_descriptor[0] = ((igLongArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igLongArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        descriptor = g_igLongArrayMetaField_descriptor[0];
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            p = g_igLongArrayMetaField_descriptor[0];
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            ((igMetaField *)g_igLongArrayMetaField_descriptor[0])->_internalIndex = (short) (igMetaField_GetMetaFieldList()->_count - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igLongArrayMetaField_descriptor[0]);
        }
    }
}

