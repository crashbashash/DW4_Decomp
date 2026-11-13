void FUN_002b6370(int arg0) {
    FUN_002b6490();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x5856F8), (MemoryPool *)arg0);
}

igMetaObject *igUnsignedShortArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedShortArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b6490();
    return g_igUnsignedShortArrayMetaField_metaObject[0];
}

int igUnsignedShortArrayMetaField_GetVTable(void) {
    Obj_2b6400 o;
    int r;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    FUN_0030ee10((int **)&o);
    o.vt = &DAT_0052e230[0];
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

void FUN_002b6490(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedShortArrayMetaField_Register);
}

void igUnsignedShortArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedShortArrayMetaField_metaObject),
        igUnsignedShortMetaField_Register,
        igUnsignedShortMetaField_GetPublishedMetaObject,
        thunk_igUnsignedShortArrayMetaField_GetMetaObject,
        igUnsignedShortArrayMetaField_className,
        0x38, /* instance size */
        igUnsignedShortArrayMetaField_GetVTable,
        &igUnsignedShortArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igUnsignedShortArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igUnsignedShortArrayMetaField_GetMetaObject(void) {
    igUnsignedShortArrayMetaField_GetMetaObject();
}

igMetaObject *FUN_002b6530(void) {
    return g_igUnsignedShortMetaField_metaObject[0];
}

void igUnsignedShortArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igUnsignedShortArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igUnsignedShortArrayMetaField_ctorTable[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igUnsignedShortArrayMetaField_fieldTable[0], (igMetaField ***)&DAT_004bf2c8[0], &DAT_004bf2d0[0], temp_s1);
}

void FUN_002b65d0(void) {
    T_2b65d0 *temp_s0;
    T_2b65d0 *p;

    if (g_igUnsignedShortArrayMetaField_descriptor[0] == 0) {
        g_igUnsignedShortArrayMetaField_descriptor[0] = ((T_2b65d0 *)igMetaObject_CreateInstance((CreateMeta *)g_igUnsignedShortArrayMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        temp_s0 = g_igUnsignedShortArrayMetaField_descriptor[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((C *)FUN_002fc250())), (RefHeader *)temp_s0);
            p = g_igUnsignedShortArrayMetaField_descriptor[0];
            p->references = p->references - 1;
            if (((unsigned long long)(long long)p->references & 0x7fffffULL) == 0) {
                igObject_Destroy(p);
            }
            g_igUnsignedShortArrayMetaField_descriptor[0]->s18 = ((C *)FUN_002fc250())->cnt - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igUnsignedShortArrayMetaField_descriptor[0]);
        }
    }
}

