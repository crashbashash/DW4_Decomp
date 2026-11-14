igMetaObject *igDoubleArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igDoubleArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDoubleArrayMetaField_EnsureRegistered();
    return g_igDoubleArrayMetaField_metaObject[0];
}

int igDoubleArrayMetaField_GetVTable(void) {
    igDoubleArrayMetaField o;
    int r;
    int *s;
    int *h;
    int c;
    igMetaField_Init((igMetaField *)&o);
    o._vtable = (int)&g_igDoubleArrayMetaField_vtable[0];
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        s = (int *)o._fieldName;
        if (s != 0) {
            h = s - 2;
            c = s[-1] - 1;
            s[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader((StringChunk *)(*h), (int)h);
        }
    }
    return r;
}

void igDoubleArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDoubleArrayMetaField_Register);
}

void igDoubleArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igDoubleArrayMetaField_metaObject,
        (igMetaObjectRegisterFunction)igDoubleMetaField_Register,
        igDoubleMetaField_GetPublishedMetaObject,
        igDoubleArrayMetaField_GetMetaObjectFunction,
        igDoubleArrayMetaField_className,
        0x38,
        igDoubleArrayMetaField_GetVTable,
        igDoubleArrayMetaField_InitFields,
        0,
        (igMetaObjectCallback *)g_igDoubleArrayMetaField_callbackList
    );
}

void igDoubleArrayMetaField_GetMetaObjectFunction(void) {
    igDoubleArrayMetaField_GetMetaObject();
}

igMetaObject *igDoubleMetaField_GetPublishedMetaObject(void) {
    return g_igDoubleMetaField_metaObject[0];
}

void igDoubleArrayMetaField_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)g_igDoubleArrayMetaField_metaObject[0];
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igDoubleArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, first)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igDoubleArrayMetaField_fieldTable[0], (igMetaField ***)&g_igDoubleArrayMetaField_fieldDescriptors[0], &g_igDoubleArrayMetaField_fieldOffsets[0], first);
}

void igDoubleArrayMetaField_CreateDefaultDescriptor(void) {
    igDoubleArrayMetaField *descriptor;
    igDoubleArrayMetaField *p;
    int len;

    if (g_igDoubleArrayMetaField_descriptor[0] == 0) {
        g_igDoubleArrayMetaField_descriptor[0] = ((igDoubleArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igDoubleArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        descriptor = g_igDoubleArrayMetaField_descriptor[0];
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            p = g_igDoubleArrayMetaField_descriptor[0];
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            len = igMetaField_GetMetaFieldList()->_count;
            g_igDoubleArrayMetaField_descriptor[0]->_internalIndex = len - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igDoubleArrayMetaField_descriptor[0]);
        }
    }
}

