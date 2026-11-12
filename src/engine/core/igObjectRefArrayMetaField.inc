void FUN_002bd320(int arg0) {
    FUN_002bd470();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585B48), (MemoryPool *)arg0);
}

igMetaObject *igObjectRefArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectRefArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bd470();
    return g_igObjectRefArrayMetaField_metaObject[0];
}

int igObjectRefArrayMetaField_GetVTable(void) {
    Obj_2bd3b0 o;
    int r;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;
    int *temp_a1_2;
    int temp_v0_2;
    void *temp_v1_2;

    igObjectRefMetaField_Init((igObjectRefMetaField *)&o);
    o.vt = &DAT_0052ef40[0];
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o.vt = &g_igObjectRefMetaField_vtable[0];
    if (&o.str2 != 0) {
        temp_v1 = o.str2;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    o.vt = &g_igMetaField_vtable[0];
    if (&o.str != 0) {
        temp_v1_2 = o.str;
        if (temp_v1_2 != 0) {
            temp_a1_2 = (int *)((char *)temp_v1_2 - 8);
            temp_v0_2 = *(int *)((char *)(temp_v1_2) - 4) - 1;
            *(int *)((char *)(temp_v1_2) - 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1_2), (int)temp_a1_2);
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
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004bfb00[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004bfb08[0], (igMetaField ***)&DAT_004bfb10[0], &DAT_004bfb18[0], temp_s1);
}

void FUN_002bd5b0(void) {
    R_2bd5b0 *temp_s0;
    R_2bd5b0 *o;
    int t;

    if (DAT_00585b50[0] == 0) {
        DAT_00585b50[0] = ((R_2bd5b0 *)igMetaObject_CreateInstance((CreateMeta *)g_igObjectRefArrayMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])))));
        temp_s0 = DAT_00585b50[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((Q_2bd5b0 *)FUN_002fc250())), (RefHeader *)temp_s0);
            o = DAT_00585b50[0];
            o->f4 = o->f4 - 1;
            if ((o->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
            t = ((Q_2bd5b0 *)FUN_002fc250())->f12 - 1;
            DAT_00585b50[0]->f18 = t;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00585b50[0]);
        }
    }
}

