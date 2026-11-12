void * FUN_002c01f0(int arg0) {
    FUN_002c0360();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585E88), (MemoryPool *)arg0));
}

igMetaObject *igMemoryPoolContextInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPoolContextInfo_metaObject_00585e88[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c0360();
    return g_igMemoryPoolContextInfo_metaObject_00585e88[0];
}

int igMemoryPoolContextInfo_GetVTable(void) {
    struct Obj_2c0280 obj;
    char *o;
    igObject *r;
    int *a1;
    int v0;
    int t;
    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.w2 = 0;
    obj.vt = &DAT_0052f4a0[0];
    obj.w5 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj.vt = &DAT_0052f4a0[0];
    if (&obj.w5 != 0) {
        r = obj.w5;
        if (r != 0) {
            r->_refCount = r->_refCount - 1;
            if ((r->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(r);
            }
        }
    }
    obj.vt = &g_igNamedObject_vtable[0];
    if (&obj.w2 != 0) {
        o = obj.w2;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*a1), (int)a1);
            }
        }
    }
    return t;
}

void FUN_002c0360(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryPoolContextInfo_Register);
}

void igMemoryPoolContextInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMemoryPoolContextInfo_metaObject_00585e88),
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igMemoryPoolContextInfo_GetMetaObject,
        igMemoryPoolContextInfo_className,
        0x18, /* instance size */
        igMemoryPoolContextInfo_GetVTable,
        &igMemoryPoolContextInfo_InitFields,
        0, /* extra callback item */
        g_igMemoryPoolContextInfo_callbackList /* callback list */
    );
}

void thunk_igMemoryPoolContextInfo_GetMetaObject(void) {
    igMemoryPoolContextInfo_GetMetaObject();
}

void igMemoryPoolContextInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igMemoryPoolContextInfo_metaObject_00585e88[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004c0168[0], 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_002bfd60();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004c0170[0], (igMetaField ***)&DAT_004c0178[0], &DAT_004c0180[0], temp_s2);
}

