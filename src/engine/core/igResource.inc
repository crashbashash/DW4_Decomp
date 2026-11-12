void FUN_002ba9f0(int arg0) {
    FUN_002bad40();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585978), (MemoryPool *)arg0);
}

igMetaObject *FUN_002baa30(void) {
    if (g_igResource_metaObject[0] == 0) {
        g_igResource_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    }
    return g_igResource_metaObject[0];
}

igMetaObject *igResource_GetMetaObject(void)
{
    igMetaObject *g = g_igResource_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bad40();
    return g_igResource_metaObject[0];
}

int igResource_GetVTable(void) {
    struct Obj_2baad0 obj;
    int t;
    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_0052eb90[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj.vt = &DAT_0052eb90[0];
    FUN_001509f0(&obj.w16, -1);
    FUN_001509f0(&obj.w15, -1);
    FUN_001509f0(&obj.w14, -1);
    ObjectRef_Destruct_00150eb0(&obj.w12, -1);
    FUN_001a0790(&obj.w11, -1);
    FUN_001432d0(&obj.w9, -1);
    FUN_002bacc0((O *)&obj.w8, -1);
    StringRef_Destruct_00130720(&obj.w6, -1);
    StringRef_Destruct_00130720(&obj.w5, -1);
    FUN_002bac40((void **)&obj.w4, -1);
    FUN_001d36d0(&obj.w3, -1);
    return t;
}

void **FUN_002bac40(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

O *FUN_002bacc0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

void FUN_002bad40(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igResource_Register);
}

void igResource_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igResource_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igResource_GetMetaObject,
        igResource_className,
        0x4C, /* instance size */
        igResource_GetVTable,
        &igResource_InitFields,
        0, /* extra callback item */
        g_igResource_callbackList /* callback list */
    );
}

void thunk_igResource_GetMetaObject(void) {
    igResource_GetMetaObject();
}

void igResource_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_s1;

    temp_s1 = (void *)g_igResource_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, (igMetaField * (**)(void *))&DAT_004bf740[0], 0x11);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_002c7300();
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_002c7150();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    ((igMetaField *)temp_s2_2)->_persistent = 0;
    igStringMetaField_SetDefaultText((int *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2))), 0);
    igStringMetaField_SetDefaultText((int *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3))), 0);
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_002bc110();
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_002b7f80();
    FUN_002d3890((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 7))), 1);
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 8)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_002b9390();
    ((igMetaField *)temp_s2_5)->_persistent = 0;
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 9)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igMetaField *)temp_s2_6)->_persistent = 0;
    FUN_002d3890((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xA))), 1);
    temp_s2_7 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xB)));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)FUN_002c04a0();
    temp_s2_8 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xC)));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = (int)FUN_002c04a0();
    temp_s2_9 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xD)));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = (int)FUN_002c04a0();
    FUN_002d3890((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xE))), 1);
    FUN_002ea4b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xF))), 0x20000);
    FUN_002d3890((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0x10))), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s1, (const char **)&DAT_004bf790[0], (igMetaField ***)&DAT_004bf7e0[0], &DAT_004bf830[0], temp_s0);
}

