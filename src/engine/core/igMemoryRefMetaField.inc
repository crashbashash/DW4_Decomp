void **igMemoryRefMetaField_Create(int pool) {
    void **instance;

    if (*g_objectSystem[0] != 0) {
        igMemoryRefMetaField_EnsureRegistered();
        instance = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)(((int *)g_igMemoryRefMetaField_metaObject)[0]), (igMemoryPoolView *)pool)));
    } else {
        instance = (void **)(((void **)igObject_AllocateRawStorage(0x50, 0, (igMemoryPoolView *)pool)));
        if (instance != 0) {
            instance = (void **)(((void **)igMemoryRefMetaField_Construct((igMemoryRefMetaField *)instance, 1)));
        }
        ((igObjectDispatchView *)(instance))->initDefaults();
        ((igObjectDispatchView *)(instance))->userConstruct((int)(0));
    }
    return instance;
}

igMemoryRefMetaField *igMemoryRefMetaField_Clone(igMemoryRefMetaField *source, int copyMode) {
    igMemoryRefMetaField *clone;

    if (*g_objectSystem[0] != 0) {
        igMemoryRefMetaField_EnsureRegistered();
        return (igMemoryRefMetaField *)igObject_CloneViaMetadata((void **)source, copyMode);
    }
    clone = (igMemoryRefMetaField *)igObject_AllocateRawStorageDefault(0x50, 0);
    if (clone != 0) {
        clone = igMemoryRefMetaField_CopyConstruct(clone, source);
    }
    return clone;
}

igMetaObject *igMemoryRefMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryRefMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryRefMetaField_EnsureRegistered();
    return g_igMemoryRefMetaField_metaObject[0];
}

int igMemoryRefMetaField_GetVTable(void) {
    igMemoryRefMetaField prototype;
    int vtable;

    igMemoryRefMetaField_Init((igMemoryRefMetaField *)&prototype);
    vtable = *(int *)((char *)&prototype + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    prototype._vtable = (int)&g_igMemoryRefMetaField_vtable[0];
    StringRef_Destruct_00130720((char *)&prototype._poolName, -1);
    FUN_0014ec50((char *)&prototype._memTypeRef, -1);
    igRefMetaField_Destroy((igRefMetaField *)&prototype, 0);
    return vtable;
}

void *igMemoryRefMetaField_Destroy(igMemoryRefMetaField *self, long long flags) {
    igObject *o;
    int *a1;
    int v0;
    if (self != 0) {
        self->_vtable = (int)&g_igMemoryRefMetaField_vtable[0];
        if (&self->_poolName != 0) {
            char *p = (char *)self->_poolName;
            if (p != 0) {
                a1 = (int *)(p - 8);
                v0 = *(int *)(p - 4) - 1;
                *(int *)(p - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)(*a1), (int)a1);
                }
            }
        }
        if (&self->_memTypeRef != 0) {
            o = (igObject *)self->_memTypeRef;
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if ((o->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(o);
                }
            }
        }
        if (self != 0) {
            self->_vtable = (int)&g_igRefMetaField_vtable[0];
            if (self != 0) {
                self->_vtable = (int)&g_igMetaField_vtable[0];
                if (&self->_fieldName != 0) {
                    char *p = (char *)self->_fieldName;
                    if (p != 0) {
                        a1 = (int *)(p - 8);
                        v0 = *(int *)(p - 4) - 1;
                        *(int *)(p - 4) = v0;
                        if (v0 == 0) {
                            StringChunk_ReleaseHeader((StringChunk *)(*a1), (int)a1);
                        }
                    }
                }
            }
        }
        if ((short)flags > 0) {
            thunk_Memory_FreeBuffer((int)self);
        }
    }
    return self;
}

void *igRefMetaField_Destroy(igRefMetaField *self, short flags) {
    void *p;
    int *h;
    int rc;

    if (self != 0) {
        self->_vtable = (int)&g_igRefMetaField_vtable[0];
        if (self != 0) {
            self->_vtable = (int)&g_igMetaField_vtable[0];
            if (&self->_fieldName) {
                p = (void *)self->_fieldName;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader((StringChunk *)(*h), (int)h);
                    }
                }
            }
        }
        if (flags > 0) {
            thunk_Memory_FreeBuffer((int)self);
        }
    }
    return self;
}

void igMemoryRefMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryRefMetaField_Register);
}

void igMemoryRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0,
        g_igMemoryRefMetaField_metaObject,
        (igMetaObjectRegisterFunction)igRefMetaField_Register,
        igRefMetaField_GetPublishedMetaObject,
        igMemoryRefMetaField_GetMetaObjectFunction,
        igMemoryRefMetaField_className,
        0x50,
        igMemoryRefMetaField_GetVTable,
        igMemoryRefMetaField_InitFields,
        0,
        (igMetaObjectCallback *)g_igMemoryRefMetaField_callbackList
    );
}

void igMemoryRefMetaField_GetMetaObjectFunction(void) {
    igMemoryRefMetaField_GetMetaObject();
}

void igMemoryRefMetaField_InitFields(void) {
    igMetaObject *meta = g_igMemoryRefMetaField_metaObject[0];
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    igObjectRefMetaField *ref;
    int index;
    int fields;
    igMetaObject_CreateFields(meta, (FieldFactory *)g_igMemoryRefMetaField_ctorTable, 8);
    field = (igMetaField *)igMetaObject_FindFieldByName(meta, (const char *)text_shallowCopyMethod);
    index = ObjectPointerList_FindIndex((char *)meta->_metaFields, (int)field);
    field = (igMetaField *)((igObjectDispatchView *)field)->cloneViaMetadata(1);
    igCharMetaField_SetDefaultValue((void **)field, 2);
    field->_externalEnumStorage = (int)g_igMemoryRefMetaField_shallowCopyMethodStorage;
    igMetaObject_FinalizeAndReplaceField(meta, index, field);
    releaseField(field);
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base))->_persistent = 0;
    ref = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 1);
    ref->_metaObject = (int)igMetaField_GetOrCreateMetaObject();
    ref->_refCounted = 0;
    ref->_deepCopyMethod = 1;
    igBoolMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt(meta, base + 2), 1);
    igBoolMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt(meta, base + 3), 1);
    fields = meta->_metaFields;
    index = ObjectPointerList_FindIndex((char *)fields, (int)igMetaObject_FindFieldByName(meta, (const char *)text_resetMethod));
    field = (igMetaField *)igEnumMetaField_Create((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    igMetaField_Configure(field, (const char *)text_resetMethod, g_igMemoryRefMetaField_resetMethodStorage, 0x24, meta);
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)field, g_igMemoryRefMetaField_resetMethodDefault);
    ((igEnumMetaField *)field)->_getMetaEnumFunction = (int)igMetaField_GetResetTypeMetaEnum;
    field->_externalEnumStorage = (int)g_igMemoryRefMetaField_resetMethodStorage;
    igMetaObject_FinalizeAndReplaceField(meta, index, field);
    releaseField(field);
    igBoolMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt(meta, base + 4), 1);
    igIntMetaField_SetDefault((void **)igMetaObject_GetFieldAt(meta, base + 5), -1);
    ref = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 6);
    ref->_metaObject = (int)igMetaField_GetOrCreateMetaObject();
    ref->_deepCopyMethod = 1;
    igMetaObject_NameFields(meta, (const char **)g_igMemoryRefMetaField_fieldTable, (igMetaField ***)g_igMemoryRefMetaField_fieldDescriptors, g_igMemoryRefMetaField_fieldOffsets, base);
}

void igMemoryRefMetaField_CreateDefaultDescriptor(void) {
    igMemoryRefMetaField *descriptor;
    igMemoryRefMetaField *p;

    if (g_igMemoryRefMetaField_descriptor[0] == 0) {
        g_igMemoryRefMetaField_descriptor[0] = ((igMemoryRefMetaField *)igMetaObject_CreateInstance((igMetaObject *)(((int *)g_igMemoryRefMetaField_metaObject)[0]), (igMemoryPoolView *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        descriptor = g_igMemoryRefMetaField_descriptor[0];
        if (descriptor != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)descriptor);
            p = g_igMemoryRefMetaField_descriptor[0];
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long)(long long)p->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(p);
            }
            g_igMemoryRefMetaField_descriptor[0]->_internalIndex = igMetaField_GetMetaFieldList()->_count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igMemoryRefMetaField_descriptor[0]);
        }
    }
}

int igMemoryRefMetaField_GetDefaultDescriptor(void) {
    if (((int *)g_igMemoryRefMetaField_descriptor)[0] == 0) {
        igMemoryRefMetaField_EnsureRegistered();
    }
    return ((int *)g_igMemoryRefMetaField_descriptor)[0];
}

