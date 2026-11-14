void FUN_002c19f0(int arg0) {
    FUN_002c1b10();
    igMetaObject_CreateInstance((igMetaObject *)g_igLongMetaField_metaObject[0], (igMemoryPoolView *)arg0);
}

igMetaObject *igLongMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igLongMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c1b10();
    return g_igLongMetaField_metaObject[0];
}

int igLongMetaField_GetVTable(void) {
    igLongMetaField u;
    int *temp_a1;
    int temp_s0;
    int temp_v0;
    void *temp_v1;

    igMetaField_Init((igMetaField *)&u);
    u._vtable = (int)&DAT_0052fa50[0];
    temp_s0 = *(int *)((char *)&u + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    u._vtable = (int)&g_igMetaField_vtable[0];
    if ((void **)&u._fieldName != 0) {
        temp_v1 = (void *)((void *)u._fieldName);
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_002c1b10(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igLongMetaField_Register);
}

void igLongMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igLongMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igLongMetaField_GetMetaObject,
        igLongMetaField_className,
        0x34, /* instance size */
        igLongMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igLongMetaField_callbackList /* callback list */
    );
}

void thunk_igLongMetaField_GetMetaObject(void) {
    igLongMetaField_GetMetaObject();
}

void FUN_002c1ba0(void) {
    void *temp_s0;

    if (g_igLongMetaField_descriptor[0] == 0) {
        g_igLongMetaField_descriptor[0] = (void *)(((void *)igMetaObject_CreateInstance((igMetaObject *)g_igLongMetaField_metaObject[0], (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = (void *)(g_igLongMetaField_descriptor[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), (igObject *)temp_s0);
            {
                void *held = (void *)g_igLongMetaField_descriptor[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(g_igLongMetaField_descriptor[0]) + 18) = (short) (*(int *)((char *)(((void *)FUN_002fc250())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igLongMetaField_descriptor[0]);
        }
    }
}

int FUN_002c1c70(void) {
    if (((int *)g_igLongMetaField_descriptor)[0] == 0) {
        FUN_002c1b10();
    }
    return ((int *)g_igLongMetaField_descriptor)[0];
}

