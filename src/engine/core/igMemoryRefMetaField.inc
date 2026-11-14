void **igMemoryRefMetaField_Create(int arg0) {
    void **var_s0;

    if (*g_objectSystem[0] != 0) {
        igMemoryRefMetaField_EnsureRegistered();
        var_s0 = (void **)(((void **)igMetaObject_CreateInstance((CreateMeta *)(((int *)g_igMemoryRefMetaField_metaObject)[0]), (MemoryPool *)arg0)));
    } else {
        var_s0 = (void **)(((void **)igObject_AllocateRawStorage(0x50, 0, (igMemoryPoolView *)arg0)));
        if (var_s0 != 0) {
            var_s0 = (void **)(((void **)igMemoryRefMetaField_Construct((igMemoryRefMetaField *)var_s0, 1)));
        }
        ((igObjectDispatchView *)(var_s0))->vfunc_09();
        ((igObjectDispatchView *)(var_s0))->userConstruct((int)(0));
    }
    return var_s0;
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
    igMemoryRefMetaField u;
    int temp_s0;

    igMemoryRefMetaField_Init((igMemoryRefMetaField *)&u);
    temp_s0 = *(int *)((char *)&u + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    u._vtable = (int)&g_igMemoryRefMetaField_vtable[0];
    StringRef_Destruct_00130720((char *)&u._poolName, -1);
    FUN_0014ec50((char *)&u._memTypeRef, -1);
    FUN_002bf5e0((igRefMetaField *)&u, 0);
    return temp_s0;
}

void *FUN_002bf4c0(igMemoryRefMetaField *arg0, long long arg1) {
    igObject *o;
    int *a1;
    int v0;
    if (arg0 != 0) {
        arg0->_vtable = (int)&g_igMemoryRefMetaField_vtable[0];
        if (&arg0->_poolName != 0) {
            char *p = (char *)arg0->_poolName;
            if (p != 0) {
                a1 = (int *)(p - 8);
                v0 = *(int *)(p - 4) - 1;
                *(int *)(p - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader((StringChunkOwnerView *)(*a1), (int)a1);
                }
            }
        }
        if (&arg0->_memTypeRef != 0) {
            o = (igObject *)arg0->_memTypeRef;
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if ((o->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(o);
                }
            }
        }
        if (arg0 != 0) {
            arg0->_vtable = (int)&g_igRefMetaField_vtable[0];
            if (arg0 != 0) {
                arg0->_vtable = (int)&g_igMetaField_vtable[0];
                if (&arg0->_fieldName != 0) {
                    char *p = (char *)arg0->_fieldName;
                    if (p != 0) {
                        a1 = (int *)(p - 8);
                        v0 = *(int *)(p - 4) - 1;
                        *(int *)(p - 4) = v0;
                        if (v0 == 0) {
                            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*a1), (int)a1);
                        }
                    }
                }
            }
        }
        if ((short)arg1 > 0) {
            thunk_FUN_002ed460__002ff810((int)arg0);
        }
    }
    return arg0;
}

void *FUN_002bf5e0(igRefMetaField *arg0, short arg1) {
    void *p;
    int *h;
    int rc;

    if (arg0 != 0) {
        arg0->_vtable = (int)&g_igRefMetaField_vtable[0];
        if (arg0 != 0) {
            arg0->_vtable = (int)&g_igMetaField_vtable[0];
            if (&arg0->_fieldName) {
                p = (void *)arg0->_fieldName;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader((StringChunkOwnerView *)(*h), (int)h);
                    }
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810((int)arg0);
        }
    }
    return arg0;
}

void igMemoryRefMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryRefMetaField_Register);
}

void igMemoryRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMemoryRefMetaField_metaObject),
        igRefMetaField_Register,
        igRefMetaField_GetPublishedMetaObject,
        thunk_igMemoryRefMetaField_GetMetaObject,
        igMemoryRefMetaField_className,
        0x50, /* instance size */
        igMemoryRefMetaField_GetVTable,
        igMemoryRefMetaField_InitFields,   /* field adder (igMetaObject_CreateFields) */
        0, /* extra callback item */
        g_igMemoryRefMetaField_callbackList /* callback list */
    );
}

void thunk_igMemoryRefMetaField_GetMetaObject(void) {
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
    FUN_002d4e40((void **)field, 2);
    field->_externalEnumStorage = (int)DAT_00585d90;
    igMetaObject_FinalizeAndReplaceField(meta, index, field);
    releaseField(field);
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base))->_persistent = 0;
    ref = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 1);
    ref->_metaObject = (int)FUN_002beca0();
    ref->_refCounted = 0;
    ref->_deepCopyMethod = 1;
    FUN_002d3890((void **)igMetaObject_GetFieldAt(meta, base + 2), 1);
    FUN_002d3890((void **)igMetaObject_GetFieldAt(meta, base + 3), 1);
    fields = meta->_metaFields;
    index = ObjectPointerList_FindIndex((char *)fields, (int)igMetaObject_FindFieldByName(meta, (const char *)text_resetMethod));
    field = (igMetaField *)FUN_002c5fb0((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    igMetaField_Configure(field, (const char *)text_resetMethod, DAT_00585db8, 0x24, meta);
    FUN_002dc7a0((igMetaFieldView *)field, DAT_004c0020);
    ((igEnumMetaField *)field)->_getMetaEnumFunction = (int)FUN_002bec40;
    field->_externalEnumStorage = (int)DAT_00585db8;
    igMetaObject_FinalizeAndReplaceField(meta, index, field);
    releaseField(field);
    FUN_002d3890((void **)igMetaObject_GetFieldAt(meta, base + 4), 1);
    FUN_002ea4b0((void **)igMetaObject_GetFieldAt(meta, base + 5), -1);
    ref = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 6);
    ref->_metaObject = (int)FUN_002beca0();
    ref->_deepCopyMethod = 1;
    igMetaObject_NameFields(meta, (const char **)g_igMemoryRefMetaField_fieldTable, (igMetaField ***)DAT_004bffe0, DAT_004c0000, base);
}

void FUN_002bf990(void) {
    igMemoryRefMetaField *temp_s0;
    igMemoryRefMetaField *p;

    if (DAT_00585d88[0] == 0) {
        DAT_00585d88[0] = ((igMemoryRefMetaField *)igMetaObject_CreateInstance((CreateMeta *)(((int *)g_igMemoryRefMetaField_metaObject)[0]), (MemoryPool *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
        temp_s0 = DAT_00585d88[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)FUN_002fc250(), (RefHeader *)temp_s0);
            p = DAT_00585d88[0];
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long)(long long)p->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy(p);
            }
            DAT_00585d88[0]->_internalIndex = ((PointerList *)FUN_002fc250())->count - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00585d88[0]);
        }
    }
}

int FUN_002bfa60(void) {
    if (((int *)DAT_00585d88)[0] == 0) {
        igMemoryRefMetaField_EnsureRegistered();
    }
    return ((int *)DAT_00585d88)[0];
}

