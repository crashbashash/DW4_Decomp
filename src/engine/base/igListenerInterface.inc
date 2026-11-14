igMetaObject *FUN_00226c60(void) {
    if (g_igListenerInterface_metaObject[0] == 0) {
        g_igListenerInterface_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igListenerInterface_metaObject[0];
}

igMetaObject *igListenerInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igListenerInterface_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00226e30();
    return g_igListenerInterface_metaObject[0];
}

int igListenerInterface_GetVTable(void) {
    struct Obj_5 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c080[0];
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0052c080[0];
    FUN_00226db0((T_2 **)&obj.w11, -1);
    FUN_0013a880(&obj.w10, -1);
    FUN_00226db0((T_2 **)&obj.w9, -1);
    FUN_0014aa70(&obj.w8, -1);
    return t;
}

struct T_2 **FUN_00226db0(struct T_2 **arg0, short arg1) {
    struct T_2 *o;
    if (arg0 != 0) {
        o = *arg0;
        if (o != 0) {
            o->refs = o->refs - 1;
            if ((o->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_00226e30(void)
{
    igMetaObject_RunStaticInit(igListenerInterface_Register);
}

void igListenerInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igListenerInterface_metaObject,
        igInterface_Register,
        igInterface_GetPublishedMetaObject,
        thunk_igListenerInterface_GetMetaObject,
        igListenerInterface_className,
        0x30, /* instance size */
        igListenerInterface_GetVTable,
        &igListenerInterface_InitFields,
        0, /* extra callback item */
        g_igListenerInterface_callbackList /* callback list */
    );
}

void thunk_igListenerInterface_GetMetaObject(void) {
    igListenerInterface_GetMetaObject();
}

void igListenerInterface_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)g_igListenerInterface_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igListenerInterface_ctorTable[0], 4);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_00226fd0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = igMetaObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_00226fd0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &g_igListenerInterface_fieldTable[0], &DAT_00497d00[0], &DAT_00497d10[0], temp_s0);
}

