igMetaObject *igVirtualCFuncMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igVirtualCFuncMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b5e80();
    return g_igVirtualCFuncMetaField_metaObject[0];
}

int igVirtualCFuncMetaField_GetVTable(void) {
    igVirtualCFuncMetaField f;
    int temp_s0;
    int *temp_a1;
    int temp_v0;

    igMetaField_Init((igMetaField *)&f);
    f._vtable = (int)&DAT_0052e130[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    f._vtable = (int)&g_igMetaField_vtable[0];
    if (&f._fieldName != 0) {
        if (((int *)f._fieldName) != 0) {
            temp_a1 = ((int *)f._fieldName) - 2;
            temp_v0 = ((int *)f._fieldName)[-1] - 1;
            ((int *)f._fieldName)[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_002b5e80(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igVirtualCFuncMetaField_Register);
}

void igVirtualCFuncMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igVirtualCFuncMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igVirtualCFuncMetaField_GetMetaObject,
        igVirtualCFuncMetaField_className,
        0x34, /* instance size */
        igVirtualCFuncMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igVirtualCFuncMetaField_callbackList /* callback list */
    );
}

void thunk_igVirtualCFuncMetaField_GetMetaObject(void) {
    igVirtualCFuncMetaField_GetMetaObject();
}

void FUN_002b5f10(void) {
    void *temp_s0;

    if (DAT_005856e0[0] == 0) {
        DAT_005856e0[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igVirtualCFuncMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = (void *)(DAT_005856e0[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), (igObject *)temp_s0);
            {
                void *held = (void *)DAT_005856e0[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_005856e0[0]) + 18) = (short) (*(int *)((char *)(((void *)FUN_002fc250())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_005856e0[0]);
        }
    }
}

