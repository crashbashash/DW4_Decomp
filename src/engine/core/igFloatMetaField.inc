void igFloatMetaField_Create(int arg0) {
    igFloatMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586378), (igMemoryPoolView *)arg0);
}

igMetaObject *igFloatMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFloatMetaField_EnsureRegistered();
    return g_igFloatMetaField_metaObject[0];
}

int igFloatMetaField_GetVTable(void) {
    igFloatMetaField o;
    int r;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    igMetaField_Init((igMetaField *)&o);
    o._vtable = (int)&DAT_0052ff50[0];
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

void igFloatMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igFloatMetaField_Register);
}

void igFloatMetaField_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igFloatMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        igFloatMetaField_GetMetaObjectFunction,
        igFloatMetaField_className,
        0x34, /* instance size */
        igFloatMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igFloatMetaField_callbackList /* callback list */
    );
}

void igFloatMetaField_GetMetaObjectFunction(void) {
    igFloatMetaField_GetMetaObject();
}

void igFloatMetaField_CreateDefaultDescriptor(void) {
    void *temp_s0;

    if (DAT_00586380[0] == 0) {
        DAT_00586380[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igFloatMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = (void *)(DAT_00586380[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)temp_s0);
            {
                void *held = (void *)DAT_00586380[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_00586380[0]) + 18) = (short) (*(int *)((char *)(((void *)igMetaField_GetMetaFieldList())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00586380[0]);
        }
    }
}

int igFloatMetaField_GetDefaultDescriptor(void) {
    if (((int *)DAT_00586380)[0] == 0) {
        igFloatMetaField_EnsureRegistered();
    }
    return ((int *)DAT_00586380)[0];
}

