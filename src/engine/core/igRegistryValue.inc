void * FUN_002bb500(int arg0) {
    FUN_002bb670();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585A40), (MemoryPool *)arg0));
}

igMetaObject *igRegistryValue_GetMetaObject(void)
{
    igMetaObject *g = g_igRegistryValue_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bb670();
    return g_igRegistryValue_metaObject[0];
}

int igRegistryValue_GetVTable(void) {
    struct Obj_2bb590 o;
    int r;
    int *t;
    int *p;
    int c;
    igObject_InitHeader((struct ObjectHeader *)&o);
    o.vt = &DAT_00532fb0[0];
    o.m12 = 0;
    o.m16 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o.vt = &DAT_00532fb0[0];
    if (&o.m16 != 0) {
        t = o.m16;
        if (t != 0) {
            t[1] = t[1] - 1;
            if ((t[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    if (&o.m12 != 0) {
        t = o.m12;
        if (t != 0) {
            t[1] = t[1] - 1;
            if ((t[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    return r;
}

void FUN_002bb670(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igRegistryValue_Register);
}

void igRegistryValue_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igRegistryValue_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRegistryValue_GetMetaObject,
        igRegistryValue_className,
        0x14, /* instance size */
        igRegistryValue_GetVTable,
        &igRegistryValue_InitFields,
        0, /* extra callback item */
        g_igRegistryValue_callbackList /* callback list */
    );
}

void thunk_igRegistryValue_GetMetaObject(void) {
    igRegistryValue_GetMetaObject();
}

void igRegistryValue_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igRegistryValue_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igRegistryValue_ctorTable[0], 3);
    FUN_002ea4b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2))), -1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_002b9540();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_002b9540();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igRegistryValue_fieldTable[0], (igMetaField ***)&DAT_004bf938[0], &DAT_004bf948[0], temp_s2);
}

