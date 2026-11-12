void FUN_002cce40(int arg0) {
    FUN_002ccf60();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586998), (MemoryPool *)arg0);
}

igMetaObject *igBoolArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igBoolArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002ccf60();
    return g_igBoolArrayMetaField_metaObject[0];
}

int igBoolArrayMetaField_GetVTable(void) {
    Obj_2cced0 o;
    int r;
    char *p;
    int *hdr;
    int c;

    FUN_002d37f0((int **)&o);
    o.vt = &DAT_00530c80[0];
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o.vt = &g_igMetaField_vtable[0];
    if (&o.str != 0) {
        p = o.str;
        if (p != 0) {
            hdr = (int *)(p - 8);
            c = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hdr), (int)hdr);
            }
        }
    }
    return r;
}

void FUN_002ccf60(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igBoolArrayMetaField_Register);
}

void igBoolArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igBoolArrayMetaField_metaObject),
        igBoolMetaField_Register,
        igBoolMetaField_GetPublishedMetaObject,
        thunk_igBoolArrayMetaField_GetMetaObject,
        igBoolArrayMetaField_className,
        0x38, /* instance size */
        igBoolArrayMetaField_GetVTable,
        &igBoolArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igBoolArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igBoolArrayMetaField_GetMetaObject(void) {
    igBoolArrayMetaField_GetMetaObject();
}

igMetaObject *FUN_002cd000(void) {
    return g_igBoolMetaField_metaObject[0];
}

void igBoolArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igBoolArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004c1580[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004c1588[0], (igMetaField ***)&DAT_004c1590[0], &DAT_004c1598[0], temp_s1);
}

void FUN_002cd0a0(void) {
    M_2cd0a0 *temp_s0;
    M_2cd0a0 *p;
    int len;

    if (DAT_005869a0[0] == 0) {
        DAT_005869a0[0] = ((M_2cd0a0 *)igMetaObject_CreateInstance((CreateMeta *)g_igBoolArrayMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])))));
        temp_s0 = DAT_005869a0[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((R_2cd0a0 *)FUN_002fc250())), (RefHeader *)temp_s0);
            p = DAT_005869a0[0];
            p->f4 = p->f4 - 1;
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
            len = ((R_2cd0a0 *)FUN_002fc250())->f12;
            DAT_005869a0[0]->f18 = len - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_005869a0[0]);
        }
    }
}

