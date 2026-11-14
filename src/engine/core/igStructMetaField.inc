void igStructMetaField_Create(int arg0) {
    igStructMetaField_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585880), (igMemoryPoolView *)arg0);
}

igMetaObject *igStructMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igStructMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igStructMetaField_EnsureRegistered();
    return g_igStructMetaField_metaObject[0];
}

int igStructMetaField_GetVTable(void) {
    igStructMetaField o;
    int r;
    int *s;
    int *h;
    int c;
    igMetaField_Init((igMetaField *)&o);
    o._vtable = (int)&DAT_0052e7c0[0];
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o._vtable = (int)&g_igMetaField_vtable[0];
    if (&o._fieldName != 0) {
        s = (int *)o._fieldName;
        if (s != 0) {
            h = s - 2;
            c = s[-1] - 1;
            s[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader((StringChunk *)(*h), (int)h);
        }
    }
    return r;
}

void igStructMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igStructMetaField_Register);
}

void igStructMetaField_Register(void) {
    CoreLibrary_MarkRegistered();  /* one-shot static-init guard (byte flag), chaining to sibling init stubs */
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igStructMetaField_metaObject),
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        igStructMetaField_GetMetaObjectFunction,
        igStructMetaField_className,
        0x40, /* instance size */
        igStructMetaField_GetVTable,
        &igStructMetaField_InitFields_002b8b50[0],                            /* field adder: InitFields, registers the reflected fields */
        0, /* extra callback item */
        g_igStructMetaField_callbackList /* callback list */
    );
}

void igStructMetaField_GetMetaObjectFunction(void) {
    igStructMetaField_GetMetaObject();
}

static inline void releaseField(igMetaField *f) {
    f->_refCount = (int)f->_refCount - 1;
    if (((unsigned long long)((long long)(int)f->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(f);
    }
}

void igStructMetaField_InitFields(void) {
    igMetaObject *meta = g_igStructMetaField_metaObject[0];
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    int index;
    igMetaObject_CreateFields(meta, (FieldFactory *)g_igStructMetaField_ctorTable, 3);
    field = ((igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)text_size));
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    field = (igMetaField *)((igObjectDispatchView *)field)->cloneViaMetadata(1);
    igUnsignedShortMetaField_SetDefaultValue((void **)field, (short)1);
    field->_persistent = 0;
    field->_externalEnumStorage = (int)DAT_00585890;
    igMetaObject_FinalizeAndReplaceField(meta, index, field);
    releaseField(field);
    field = ((igMetaField *)igMetaObject_GetFieldAt(meta, base));
    igIntMetaField_SetDefault((void **)field, 1);
    field->_persistent = 0;
    igMetaObject_NameFields(meta, (const char **)g_igStructMetaField_fieldTable, (igMetaField ***)DAT_004bf600, (int *)DAT_004bf610, base);
}

void igStructMetaField_CreateDefaultDescriptor(void) {
    igStructMetaField *temp_s0;
    igStructMetaField *temp_a0;
    int n;

    if (DAT_00585888[0] == 0) {
        DAT_00585888[0] = ((igStructMetaField *)igMetaObject_CreateInstance((igMetaObject *)(((int *)g_igStructMetaField_metaObject)[0]), (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        temp_s0 = DAT_00585888[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)temp_s0);
            temp_a0 = DAT_00585888[0];
            temp_a0->_refCount = (int)((int) (temp_a0->_refCount - 1));
            if (((unsigned long long) ((long long)(int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
            n = igMetaField_GetMetaFieldList()->_count - 1;
            DAT_00585888[0]->_internalIndex = n;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00585888[0]);
        }
    }
}

