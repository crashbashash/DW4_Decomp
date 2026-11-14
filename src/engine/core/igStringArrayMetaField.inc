igMetaObject *igStringArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igStringArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igStringArrayMetaField_EnsureRegistered();
    return g_igStringArrayMetaField_metaObject[0];
}

int igStringArrayMetaField_GetVTable(void) {
    igStringArrayMetaField o;
    int r;
    char *p;
    int *hdr;
    int c;

    igStringMetaField_Init((igStringMetaField *)&o);
    o._vtable = (int)&g_igStringArrayMetaField_vtable[0];
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

void igStringArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStringArrayMetaField_Register);
}

void igStringArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igStringArrayMetaField_metaObject,
        (igMetaObjectRegisterFunction)igStringMetaField_Register,
        igStringMetaField_GetPublishedMetaObject,
        igStringArrayMetaField_GetMetaObjectFunction,
        igStringArrayMetaField_className,
        0x40,
        igStringArrayMetaField_GetVTable,
        igStringArrayMetaField_InitFields,
        0,
        (igMetaObjectCallback *)g_igStringArrayMetaField_callbackList
    );
}

void igStringArrayMetaField_GetMetaObjectFunction(void) {
    igStringArrayMetaField_GetMetaObject();
}

igMetaObject *igStringMetaField_GetPublishedMetaObject(void) {
    return g_igStringMetaField_metaObject[0];
}

void igStringArrayMetaField_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igStringArrayMetaField_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igStringArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, base)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igStringArrayMetaField_fieldTable[0], (igMetaField ***)&g_igStringArrayMetaField_fieldDescriptors[0], &g_igStringArrayMetaField_fieldOffsets[0], base);
}

void igStringArrayMetaField_CreateDefaultDescriptor(void) {
    int *s0;
    int *g;

    if (g_igStringArrayMetaField_descriptor[0] == 0) {
        g_igStringArrayMetaField_descriptor[0] = ((int *)igMetaObject_CreateInstance((igMetaObject *)g_igStringArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        s0 = g_igStringArrayMetaField_descriptor[0];
        if (s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)s0);
            g = g_igStringArrayMetaField_descriptor[0];
            g[1] = g[1] - 1;
            if ((g[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(g);
            }
            *(short *)((char *)g_igStringArrayMetaField_descriptor[0] + 18) = (short)(((int *)igMetaField_GetMetaFieldList())[3] - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igStringArrayMetaField_descriptor[0]);
        }
    }
}

