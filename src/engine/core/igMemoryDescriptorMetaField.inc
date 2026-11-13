igMetaObject *igMemoryDescriptorMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryDescriptorMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002ce6d0();
    return g_igMemoryDescriptorMetaField_metaObject[0];
}

int igMemoryDescriptorMetaField_GetVTable(void) {
    union U_2ce600 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igMetaField_Init((igMetaField *)u.b);
    u.vt = (int)&DAT_00531740[0];
    q0 = (S_ref *)&u.b[52];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00530d90[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(((void * *)g_objectSystem)[0]) + 916)];
    u.vt = (int)&DAT_00531740[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    q1 = &u.b[12];
    u.vt = (int)&g_igMetaField_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
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

void FUN_002ce6d0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryDescriptorMetaField_Register);
}

void igMemoryDescriptorMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMemoryDescriptorMetaField_metaObject),
        igCompoundMetaField_Register,
        igCompoundMetaField_GetPublishedMetaObject,
        thunk_igMemoryDescriptorMetaField_GetMetaObject,
        igMemoryDescriptorMetaField_className,
        0x38, /* instance size */
        igMemoryDescriptorMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igMemoryDescriptorMetaField_callbackList /* callback list */
    );
}

void thunk_igMemoryDescriptorMetaField_GetMetaObject(void) {
    igMemoryDescriptorMetaField_GetMetaObject();
}

void FUN_002ce760(void) {
    void *temp_s0;

    if (g_igMemoryDescriptorMetaField_descriptor[0] == 0) {
        g_igMemoryDescriptorMetaField_descriptor[0] = (void *)(((void *)igMetaObject_CreateInstance((CreateMeta *)g_igMemoryDescriptorMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]))))));
        temp_s0 = (void *)(g_igMemoryDescriptorMetaField_descriptor[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((void *)FUN_002fc250())), (RefHeader *)temp_s0);
            {
                void *held = (void *)g_igMemoryDescriptorMetaField_descriptor[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(g_igMemoryDescriptorMetaField_descriptor[0]) + 18) = (short) (*(int *)((char *)(((void *)FUN_002fc250())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igMemoryDescriptorMetaField_descriptor[0]);
        }
    }
}

/* Vtable slot 25 of igMemoryDescriptorMetaField: the byte size of the field's storage. The array
 * metafields return `_num * element size` from this slot (truncated to the reflected 16-bit
 * `_size`); a memory descriptor stores a single 32-bit reference, so it returns 4. The receiver is
 * not touched, hence no parameters. */
int Gap__Core__igMemoryDescriptorMetaField__vfunc_25(void) {
    return 4;
}

void Gap__Core__igMemoryDescriptorMetaField__vfunc_11(void *arg0) {
    FUN_002ce850(*(int *)((char *)arg0 + 52));
}

void FUN_002ce850(int arg0) {
    void *sp3C;
    int *temp_a1;
    int temp_v0;
    int var_v0_2;
    void *temp_s0;
    void *var_v0;

    temp_s0 = (void *)(((void *)igUnsignedIntMetaField_Create(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])))));
    if (&DAT_004f8cc0[0] == 0) {
        var_v0 = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_2 = ((int)StringPool_Allocate(0x10));
            if (var_v0_2 != 0) {
                var_v0_2 = ((int)StringPool_Construct((S_2eadf0 *)var_v0_2));
            }
            g_stringPool[0] = var_v0_2;
        }
        var_v0 = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)&DAT_004f8cc0[0])));
    }
    sp3C = (void *)(var_v0);
    igMetaField_SetFieldName((igMetaField *)temp_s0, &sp3C);
    if (sp3C != 0) {
        temp_a1 = (int *)((char *)sp3C - 8);
        temp_v0 = *(int *)((char *)(sp3C) - 4) - 1;
        *(int *)((char *)(sp3C) - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
        }
    }
    *(int *)((char *)(temp_s0) + 8) = 0;
    igMetaField_FinalizeDescriptor((igMetaField *)temp_s0);
    ObjectList_AppendRetained((igObjectList *)arg0, (igObject *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

