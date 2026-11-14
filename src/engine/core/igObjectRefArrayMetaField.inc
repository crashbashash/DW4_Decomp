void FUN_002bd320(int arg0) {
    FUN_002bd470();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585B48), (igMemoryPoolView *)arg0);
}

igMetaObject *igObjectRefArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectRefArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bd470();
    return g_igObjectRefArrayMetaField_metaObject[0];
}

int igObjectRefArrayMetaField_GetVTable(void) {
    igObjectRefArrayMetaField o;
    int r;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;
    int *temp_a1_2;
    int temp_v0_2;
    void *temp_v1_2;

    igObjectRefMetaField_Init((igObjectRefMetaField *)&o);
    o._vtable = (int)&DAT_0052ef40[0];
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o._vtable = (int)&g_igObjectRefMetaField_vtable[0];
    if (&o._poolName != 0) {
        temp_v1 = (char *)o._poolName;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        temp_v1_2 = (char *)o._fieldName;
        if (temp_v1_2 != 0) {
            temp_a1_2 = (int *)((char *)temp_v1_2 - 8);
            temp_v0_2 = *(int *)((char *)(temp_v1_2) - 4) - 1;
            *(int *)((char *)(temp_v1_2) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1_2), (int)temp_a1_2);
            }
        }
    }
    return r;
}

void FUN_002bd470(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igObjectRefArrayMetaField_Register);
}

void igObjectRefArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igObjectRefArrayMetaField_metaObject),
        igObjectRefMetaField_Register,
        igObjectRefMetaField_GetPublishedMetaObject,
        thunk_igObjectRefArrayMetaField_GetMetaObject,
        igObjectRefArrayMetaField_className,
        0x48, /* instance size */
        igObjectRefArrayMetaField_GetVTable,
        &igObjectRefArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igObjectRefArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igObjectRefArrayMetaField_GetMetaObject(void) {
    igObjectRefArrayMetaField_GetMetaObject();
}

igMetaObject *FUN_002bd510(void) {
    return g_igObjectRefMetaField_metaObject[0];
}

void igObjectRefArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igObjectRefArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igObjectRefArrayMetaField_ctorTable[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igObjectRefArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004bfb10[0], &DAT_004bfb18[0], temp_s1);
}

void FUN_002bd5b0(void) {
    igObjectRefArrayMetaField *temp_s0;
    igObjectRefArrayMetaField *o;
    int t;

    if (DAT_00585b50[0] == 0) {
        DAT_00585b50[0] = ((igObjectRefArrayMetaField *)igMetaObject_CreateInstance((igMetaObject *)g_igObjectRefArrayMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        temp_s0 = DAT_00585b50[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), (igObject *)temp_s0);
            o = DAT_00585b50[0];
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
            t = FUN_002fc250()->_count - 1;
            DAT_00585b50[0]->_internalIndex = t;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00585b50[0]);
        }
    }
}

