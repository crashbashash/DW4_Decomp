void * FUN_002befe0(int arg0) {
    FUN_002bf190();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585D60), (MemoryPool *)arg0));
}

igMetaObject *igMetaEnum_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaEnum_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bf190();
    return g_igMetaEnum_metaObject[0];
}

int igMetaEnum_GetVTable(void) {
    union U_2bf070 u;
    int t;
    struct Rc *a;
    int *a1;
    int v0;
    char *c;
    void **q4c;
    void **q48;
    void **q50;
    igObject_InitHeader((ObjectHeader *)u.b);
    q48 = &u.p[2];
    q4c = &u.p[3];
    q50 = &u.p[4];
    u.w[0] = (int)(&DAT_00532b50[0]);
    *q48 = 0;
    *q4c = 0;
    *q50 = 0;
    t = *(int *)&u.b[*(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916)];
    u.w[0] = (int)(&DAT_00532b50[0]);
    if (q50 != 0) {
        a = (struct Rc *)*q50;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (q4c != 0) {
        a = (struct Rc *)*q4c;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (q48 != 0) {
        c = (char *)*q48;
        if (c != 0) {
            a1 = (int *)(c - 8);
            v0 = *(int *)(c - 4) - 1;
            *(int *)(c - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*a1), (int)a1);
            }
        }
    }
    return t;
}

void FUN_002bf190(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMetaEnum_Register);
}

void igMetaEnum_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMetaEnum_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMetaEnum_GetMetaObject,
        igMetaEnum_className,
        0x14, /* instance size */
        igMetaEnum_GetVTable,
        &igMetaEnum_InitFields,
        0, /* extra callback item */
        g_igMetaEnum_callbackList /* callback list */
    );
}

void thunk_igMetaEnum_GetMetaObject(void) {
    igMetaEnum_GetMetaObject();
}

void igMetaEnum_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00585d60[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004bff48[0], 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002b9120();
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004bff58[0], (igMetaField ***)&DAT_004bff68[0], &DAT_004bff78[0], temp_s2);
}

