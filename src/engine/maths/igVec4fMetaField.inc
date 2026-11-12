void FUN_001872a0(int arg0) {
    FUN_001873c0();
    igMetaObject_CreateInstance(*(int *)0x560F38, arg0);
}

igMetaObject *igVec4fMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igVec4fMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001873c0();
    return g_igVec4fMetaField_metaObject[0];
}

int igVec4fMetaField_GetVTable(void) {
    struct F f;
    int temp_s0;
    int *temp_a1;
    int temp_v0;

    FUN_002fbfe0(&f);
    f.obj.vt = &DAT_005272e0[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.obj.vt = &g_igMetaField_vtable[0];
    if (&f.ref != 0) {
        if (f.ref != 0) {
            temp_a1 = f.ref - 2;
            temp_v0 = f.ref[-1] - 1;
            f.ref[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_001873c0(void)
{
    igMetaObject_RunStaticInit(igVec4fMetaField_Register);
}

void igVec4fMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVec4fMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igVec4fMetaField_GetMetaObject,
        igVec4fMetaField_className,
        0x34, /* instance size */
        igVec4fMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igVec4fMetaField_callbackList /* callback list */
    );
}

void thunk_igVec4fMetaField_GetMetaObject(void) {
    igVec4fMetaField_GetMetaObject();
}

void FUN_00187450(void) {
    void *temp_s0;

    if (g_igVec4fMetaField_descriptor[0] == 0) {
        g_igVec4fMetaField_descriptor[0] = (int)(igMetaObject_CreateInstance(g_igVec4fMetaField_metaObject[0], Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
        temp_s0 = (void *)(g_igVec4fMetaField_descriptor[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            {
                void *held = (void *)g_igVec4fMetaField_descriptor[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(g_igVec4fMetaField_descriptor[0]) + 18) = (short) (*(int *)((char *)(FUN_002fc250()) + 12) - 1);
            igMetaField_FinalizeDescriptor(g_igVec4fMetaField_descriptor[0]);
        }
    }
}

int FUN_00187520(void) {
    if (g_igVec4fMetaField_descriptor[0] == 0) {
        FUN_001873c0();
    }
    return g_igVec4fMetaField_descriptor[0];
}

