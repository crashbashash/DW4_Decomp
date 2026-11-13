void FUN_002c45f0(int arg0) {
    FUN_002c4710();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586378), (MemoryPool *)arg0);
}

igMetaObject *igFloatMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c4710();
    return g_igFloatMetaField_metaObject[0];
}

int igFloatMetaField_GetVTable(void) {
    Obj_2c4680 o;
    int r;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    igMetaField_Init((igMetaField *)&o);
    o.vt = &DAT_0052ff50[0];
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o.vt = &g_igMetaField_vtable[0];
    if (&o.str != 0) {
        temp_v1 = o.str;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return r;
}

void FUN_002c4710(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igFloatMetaField_Register);
}

void igFloatMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igFloatMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igFloatMetaField_GetMetaObject,
        igFloatMetaField_className,
        0x34, /* instance size */
        igFloatMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igFloatMetaField_callbackList /* callback list */
    );
}

void thunk_igFloatMetaField_GetMetaObject(void) {
    igFloatMetaField_GetMetaObject();
}

void FUN_002c47a0(void) {
    void *temp_s0;

    if (DAT_00586380[0] == 0) {
        DAT_00586380[0] = (void *)(((void *)igMetaObject_CreateInstance((CreateMeta *)g_igFloatMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData))))));
        temp_s0 = (void *)(DAT_00586380[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((void *)FUN_002fc250())), (RefHeader *)temp_s0);
            {
                void *held = (void *)DAT_00586380[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_00586380[0]) + 18) = (short) (*(int *)((char *)(((void *)FUN_002fc250())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00586380[0]);
        }
    }
}

int FUN_002c4870(void) {
    if (((int *)DAT_00586380)[0] == 0) {
        FUN_002c4710();
    }
    return ((int *)DAT_00586380)[0];
}

