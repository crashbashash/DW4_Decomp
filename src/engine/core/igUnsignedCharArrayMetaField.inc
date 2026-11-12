void FUN_002b76a0(int arg0) {
    FUN_002b77c0();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585770), (MemoryPool *)arg0);
}

igMetaObject *igUnsignedCharArrayMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedCharArrayMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b77c0();
    return g_igUnsignedCharArrayMetaField_metaObject[0];
}

int igUnsignedCharArrayMetaField_GetVTable(void) {
    Obj_2b7730 o;
    int *temp_a1;
    int temp_s0;
    int temp_v0;
    void *temp_v1;

    igMetaField_Init((igMetaField *)&o);
    o.vt = &DAT_0052e630[0];
    temp_s0 = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o.vt = &g_igMetaField_vtable[0];
    if (&o.str != 0) {
        temp_v1 = (void *)(o.str);
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_002b77c0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedCharArrayMetaField_Register);
}

void igUnsignedCharArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedCharArrayMetaField_metaObject),
        igUnsignedCharMetaField_Register,
        igUnsignedCharMetaField_GetPublishedMetaObject,
        thunk_igUnsignedCharArrayMetaField_GetMetaObject,
        igUnsignedCharArrayMetaField_className,
        0x38, /* instance size */
        igUnsignedCharArrayMetaField_GetVTable,
        &igUnsignedCharArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igUnsignedCharArrayMetaField_callbackList /* callback list */
    );
}

void thunk_igUnsignedCharArrayMetaField_GetMetaObject(void) {
    igUnsignedCharArrayMetaField_GetMetaObject();
}

igMetaObject *FUN_002b7860(void) {
    return g_igUnsignedCharMetaField_metaObject[0];
}

void igUnsignedCharArrayMetaField_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igUnsignedCharArrayMetaField_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004bf348[0], 1);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004bf350[0], (igMetaField ***)&DAT_004bf358[0], &DAT_004bf360[0], temp_s1);
}

void FUN_002b7900(void) {
    struct R *temp_s0;
    struct R *g;

    if (g_igUnsignedCharArrayMetaField_descriptor[0] == 0) {
        g_igUnsignedCharArrayMetaField_descriptor[0] = (R *)(((void *)igMetaObject_CreateInstance((CreateMeta *)g_igUnsignedCharArrayMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]))))));
        temp_s0 = g_igUnsignedCharArrayMetaField_descriptor[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((struct M *)FUN_002fc250())), (RefHeader *)temp_s0);
            g = g_igUnsignedCharArrayMetaField_descriptor[0];
            g->rc = g->rc - 1;
            if ((g->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(g);
            }
            g_igUnsignedCharArrayMetaField_descriptor[0]->s18 = ((struct M *)FUN_002fc250())->f12 - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igUnsignedCharArrayMetaField_descriptor[0]);
        }
    }
}

