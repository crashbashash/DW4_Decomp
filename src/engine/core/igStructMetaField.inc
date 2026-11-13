void FUN_002b8990(int arg0) {
    FUN_002b8ab0();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585880), (MemoryPool *)arg0);
}

igMetaObject *igStructMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igStructMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b8ab0();
    return g_igStructMetaField_metaObject[0];
}

int igStructMetaField_GetVTable(void) {
    struct F_2b8a20 o;
    int r;
    int *s;
    int *h;
    int c;
    igMetaField_Init((igMetaField *)&o);
    o.vt = DAT_0052e7c0;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_igMetaField_vtable;
    if (&o.str != 0) {
        s = o.str;
        if (s != 0) {
            h = s - 2;
            c = s[-1] - 1;
            s[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader((StringChunkOwnerView *)(*h), (int)h);
        }
    }
    return r;
}

void FUN_002b8ab0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStructMetaField_Register);
}

void igStructMetaField_Register(void) {
    FUN_002b5d50();  /* one-shot static-init guard (byte flag), chaining to sibling init stubs */
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igStructMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igStructMetaField_GetMetaObject,
        igStructMetaField_className,
        0x40, /* instance size */
        igStructMetaField_GetVTable,
        &igStructMetaField_InitFields_002b8b50[0],                            /* field adder: InitFields, registers the reflected fields */
        0, /* extra callback item */
        g_igStructMetaField_callbackList /* callback list */
    );
}

void thunk_igStructMetaField_GetMetaObject(void) {
    igStructMetaField_GetMetaObject();
}

static inline void releaseField(igMetaField *f) {
    f->_refCount = (int)f->_refCount - 1;
    if (((unsigned long long)((long long)(int)f->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(f);
    }
}

void FUN_002b8b50(void) {
    igMetaObject *meta = g_igStructMetaField_metaObject[0];
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    int index;
    igMetaObject_CreateFields(meta, (FieldFactory *)g_igStructMetaField_ctorTable, 3);
    field = ((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)text_size));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    field = ((DescriptorCloneView *)field)->Clone(1);
    FUN_0030eda0((void **)field, (short)1);
    field->_persistent = 0;
    field->_externalEnumStorage = (int)DAT_00585890;
    igMetaObject_FinalizeAndReplaceField(meta, index, field);
    releaseField(field);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base));
    FUN_002ea4b0((void **)field, 1);
    field->_persistent = 0;
    igMetaObject_NameFields(meta, (const char **)g_igStructMetaField_fieldTable, (igMetaField ***)DAT_004bf600, (int *)DAT_004bf610, base);
}

void FUN_002b8c80(void) {
    S1 *temp_s0;
    S1 *temp_a0;
    int n;

    if (DAT_00585888[0] == 0) {
        DAT_00585888[0] = ((S1 *)igMetaObject_CreateInstance((CreateMeta *)(((int *)g_igStructMetaField_metaObject)[0]), (MemoryPool *)(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])))));
        temp_s0 = DAT_00585888[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((L *)FUN_002fc250())), (RefHeader *)temp_s0);
            temp_a0 = DAT_00585888[0];
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
            n = ((L *)FUN_002fc250())->fc - 1;
            DAT_00585888[0]->f12 = n;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00585888[0]);
        }
    }
}

