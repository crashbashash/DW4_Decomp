igMetaObject *igMemoryRefArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryRefArrayMetaField_metaObject_00585de0[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bfb50();
    return g_igMemoryRefArrayMetaField_metaObject_00585de0[0];
}

int igMemoryRefArrayMetaField_GetVTable(void) {
    igMemoryRefArrayMetaField obj;
    int temp_s0;

    igMemoryRefMetaField_Init((igMemoryRefMetaField *)&obj);
    obj._vtable = (int)&DAT_0052f330[0];
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj._vtable = (int)&DAT_0052f330[0];
    FUN_002bf4c0((igMemoryRefMetaField *)&obj, (long long)0);
    return temp_s0;
}

void FUN_002bfb50(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryRefArrayMetaField_Register);
}

void igMemoryRefArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMemoryRefArrayMetaField_metaObject_00585de0),
        igMemoryRefMetaField_Register,
        igMemoryRefMetaField_GetPublishedMetaObject,
        thunk_igMemoryRefArrayMetaField_GetMetaObject,
        igMemoryRefArrayMetaField_className,
        0x54, /* instance size */
        igMemoryRefArrayMetaField_GetVTable,
        &igMemoryRefArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igMemoryRefArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igMemoryRefArrayMetaField_GetMetaObject(void) {
    igMemoryRefArrayMetaField_GetMetaObject();
}

int FUN_002bfbf0(void) {
    return ((int *)g_igMemoryRefMetaField_metaObject)[0];
}

void igMemoryRefArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igMemoryRefArrayMetaField_metaObject_00585de0[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igMemoryRefArrayMetaField_ctorTable[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igMemoryRefArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004c0040[0], &DAT_004c0048[0], temp_s1);
}

void FUN_002bfc90(void) {
    igMemoryRefArrayMetaField *temp_s0;
    igMemoryRefArrayMetaField *t;
    if (DAT_00585de8[0] == 0) {
        DAT_00585de8[0] = ((igMemoryRefArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igMemoryRefArrayMetaField_metaObject_00585de0[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        temp_s0 = DAT_00585de8[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), (igObject *)temp_s0);
            t = DAT_00585de8[0];
            t->_refCount = t->_refCount - 1;
            if (((unsigned long long) ((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
            DAT_00585de8[0]->_internalIndex = FUN_002fc250()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00585de8[0]);
        }
    }
}

