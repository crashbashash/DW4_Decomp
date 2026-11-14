void igCharArrayMetaField_Create(int arg0) {
    igCharArrayMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586940), (igMemoryPoolView *)arg0);
}

igMetaObject *igCharArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igCharArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igCharArrayMetaField_EnsureRegistered();
    return g_igCharArrayMetaField_metaObject[0];
}

int igCharArrayMetaField_GetVTable(void) {
    igCharArrayMetaField o;
    int r;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    igCharMetaField_Init((int **)&o);
    o._vtable = (int)&DAT_00530a80[0];
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        temp_v1 = (char *)o._fieldName;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return r;
}

void igCharArrayMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igCharArrayMetaField_Register);
}

void igCharArrayMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igCharArrayMetaField_metaObject),
        igCharMetaField_Register,
        igCharMetaField_GetPublishedMetaObject,
        igCharArrayMetaField_GetMetaObjectFunction,
        igCharArrayMetaField_className,
        0x38, /* instance size */
        igCharArrayMetaField_GetVTable,
        &igCharArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igCharArrayMetaField_callbackList /* callback list */
    );
}

void igCharArrayMetaField_GetMetaObjectFunction(void) {
    igCharArrayMetaField_GetMetaObject();
}

igMetaObject *igCharMetaField_GetPublishedMetaObject(void) {
    return g_igCharMetaField_metaObject[0];
}

void igCharArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igCharArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igCharArrayMetaField_ctorTable[0], 1);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igCharArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004c1508[0], &DAT_004c1510[0], temp_s1);
}

void igCharArrayMetaField_CreateDefaultDescriptor(void) {
    igCharArrayMetaField *temp_s0;
    igCharArrayMetaField *p;

    if (g_igCharArrayMetaField_descriptor[0] == 0) {
        g_igCharArrayMetaField_descriptor[0] = ((igCharArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igCharArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        temp_s0 = g_igCharArrayMetaField_descriptor[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)temp_s0);
            p = g_igCharArrayMetaField_descriptor[0];
            p->_refCount -= 1;
            if ((p->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(p);
            }
            g_igCharArrayMetaField_descriptor[0]->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igCharArrayMetaField_descriptor[0]);
        }
    }
}

