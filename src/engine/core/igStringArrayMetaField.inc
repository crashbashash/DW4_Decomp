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
    o._vtable = (int)&DAT_0052e990[0];
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
        0, /* abstract */
        ((char *)g_igStringArrayMetaField_metaObject),
        igStringMetaField_Register,
        igStringMetaField_GetPublishedMetaObject,
        igStringArrayMetaField_GetMetaObjectFunction,
        igStringArrayMetaField_className,
        0x40, /* instance size */
        igStringArrayMetaField_GetVTable,
        &igStringArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igStringArrayMetaField_callbackList /* callback list */
    );
}

void igStringArrayMetaField_GetMetaObjectFunction(void) {
    igStringArrayMetaField_GetMetaObject();
}

igMetaObject *igStringMetaField_GetPublishedMetaObject(void) {
    return g_igStringMetaField_metaObject[0];
}

void igStringArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igStringArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igStringArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igStringArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004bf6d8[0], &DAT_004bf6e0[0], temp_s1);
}

void igStringArrayMetaField_CreateDefaultDescriptor(void) {
    int *s0;
    int *g;

    if (DAT_00585938[0] == 0) {
        DAT_00585938[0] = ((int *)igMetaObject_CreateInstance((igMetaObject *)g_igStringArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        s0 = DAT_00585938[0];
        if (s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)s0);
            g = DAT_00585938[0];
            g[1] = g[1] - 1;
            if ((g[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(g);
            }
            *(short *)((char *)DAT_00585938[0] + 18) = (short)(((int *)igMetaField_GetMetaFieldList())[3] - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00585938[0]);
        }
    }
}

