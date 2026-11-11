void **igMemoryRefMetaField_Create(int arg0) {
    void **var_s0;

    if (*DAT_00586dc8[0] != 0) {
        igMemoryRefMetaField_EnsureRegistered();
        var_s0 = (void **)(((void **)igMetaObject_CreateInstance((CreateMeta *)(((int *)DAT_00585d80)[0]), (MemoryPool *)arg0)));
    } else {
        var_s0 = (void **)(((void **)igObject_AllocateRawStorage(0x50, 0, (void **)arg0)));
        if (var_s0 != 0) {
            var_s0 = (void **)(((void **)igMemoryRefMetaField_Construct((igMemoryRefMetaField *)var_s0, 1)));
        }
        ((DW4VC_44_0 *)(var_s0))->vX();
        ((DW4VC_36_1 *)(var_s0))->vX((int)(0));
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
    union U_2bf450 u;
    int temp_s0;

    igMemoryRefMetaField_Init((igMemoryRefMetaField *)u.b);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916)];
    u.vt = (int)&DAT_00532a50[0];
    StringRef_Destruct_00130720(&u.b[76], -1);
    FUN_0014ec50(&u.b[72], -1);
    FUN_002bf5e0((S *)u.b, 0);
    return temp_s0;
}

void *FUN_002bf4c0(igMemoryRefMetaField *arg0, long long arg1) {
    igObject *o;
    int *a1;
    int v0;
    if (arg0 != 0) {
        arg0->_vtable = (int)&DAT_00532a50[0];
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
            arg0->_vtable = (int)&DAT_0052ec50[0];
            if (arg0 != 0) {
                arg0->_vtable = (int)&DAT_0052f230[0];
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

void *FUN_002bf5e0(struct S *arg0, short arg1) {
    void *p;
    int *h;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_0052ec50[0];
        if (arg0 != 0) {
            arg0->f0 = &DAT_0052f230[0];
            if (&arg0->fc) {
                p = arg0->fc;
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
        &igMemoryRefMetaField_InitFields_002bf710[0],   /* field adder (igMetaObject_CreateFields) */
        0, /* extra callback item */
        g_igMemoryRefMetaField_callbackList /* callback list */
    );
}

void thunk_igMemoryRefMetaField_GetMetaObject(void) {
    igMemoryRefMetaField_GetMetaObject();
}

void FUN_002bf990(void) {
    T_2bf990 *temp_s0;
    T_2bf990 *p;

    if (DAT_00585d88[0] == 0) {
        DAT_00585d88[0] = ((T_2bf990 *)igMetaObject_CreateInstance((CreateMeta *)(((int *)DAT_00585d80)[0]), (MemoryPool *)(((int)Memory_GetAllocatorBySelector(DAT_00587040[0])))));
        temp_s0 = DAT_00585d88[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((C *)FUN_002fc250())), (RefHeader *)temp_s0);
            p = DAT_00585d88[0];
            p->references = p->references - 1;
            if (((unsigned long long)(long long)p->references & 0x7fffffULL) == 0) {
                igObject_Destroy(p);
            }
            DAT_00585d88[0]->s18 = ((C *)FUN_002fc250())->cnt - 1;
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

