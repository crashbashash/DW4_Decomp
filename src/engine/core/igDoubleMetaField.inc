void FUN_002c6ba0(int arg0) {
    FUN_002c6cc0();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586638), (MemoryPool *)arg0);
}

igMetaObject *igDoubleMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igDoubleMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c6cc0();
    return g_igDoubleMetaField_metaObject[0];
}

int igDoubleMetaField_GetVTable(void) {
    igDoubleMetaField u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igMetaField_Init((igMetaField *)&u);
    u._vtable = (int)&DAT_00530690[0];
    temp_s0 = *(int *)((char *)&u + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    u._vtable = (int)&g_igMetaField_vtable[0];
    ps = (char *)&u._fieldName;
    if (ps != 0) {
        temp_v1 = *(int **)ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_002c6cc0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDoubleMetaField_Register);
}

void igDoubleMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igDoubleMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igDoubleMetaField_GetMetaObject,
        igDoubleMetaField_className,
        0x34, /* instance size */
        igDoubleMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igDoubleMetaField_callbackList /* callback list */
    );
}

void thunk_igDoubleMetaField_GetMetaObject(void) {
    igDoubleMetaField_GetMetaObject();
}

void FUN_002c6d50(void) {
    void *temp_s0;

    if (DAT_00586640[0] == 0) {
        DAT_00586640[0] = (void *)(((void *)igMetaObject_CreateInstance((CreateMeta *)g_igDoubleMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = (void *)(DAT_00586640[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((void *)FUN_002fc250())), (RefHeader *)temp_s0);
            {
                void *held = (void *)DAT_00586640[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_00586640[0]) + 18) = (short) (*(int *)((char *)(((void *)FUN_002fc250())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00586640[0]);
        }
    }
}

int FUN_002c6e20(void) {
    if (((int *)DAT_00586640)[0] == 0) {
        FUN_002c6cc0();
    }
    return ((int *)DAT_00586640)[0];
}

