void FUN_003b5ec0(int arg0) {
    FUN_003b6110();
    igMetaObject_CreateInstance(*(int *)0x58AC48, arg0);
}

igMetaObject *FUN_003b5f00(void) {
    if (g_beNDMWStatusInfoWork_metaObject[0] == 0) {
        g_beNDMWStatusInfoWork_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWStatusInfoWork_metaObject[0];
}

void *FUN_003b5f50(void) {
    bool ok;
    if (g_beNDMWStatusInfoWork_metaObject[0] == 0) goto make;
    ok = !!(g_beNDMWStatusInfoWork_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_003b6110();
done:;
    return g_beNDMWStatusInfoWork_metaObject[0];
}

int beNDMWStatusInfoWork_GetVTable(void) {
    struct Obj_3b5fa0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053db00[0];
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.w[6] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053db00[0];
    FUN_003b6090((void **)(&obj.w[6]), (long long)(-1));
    FUN_003b6090((void **)(&obj.w[5]), (long long)(-1));
    FUN_003b6090((void **)(&obj.w[4]), (long long)(-1));
    FUN_003b6090((void **)(&obj.w[3]), (long long)(-1));
    ObjectRef_Destruct_00150eb0(&obj.w[2], -1);
    ObjectRef_Destruct_00150eb0(&obj.w[1], -1);
    return r;
}

void **FUN_003b6090(void **arg0, long long arg1) {
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

void FUN_003b6110(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusInfoWork_Register);
}

void *beNDMWStatusInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWStatusInfoWork_GetMetaObject,
        beNDMWStatusInfoWork_className,
        0x24, /* instance size */
        beNDMWStatusInfoWork_GetVTable,
        beNDMWStatusInfoWork_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusInfoWork_callbackList /* callback list */
    );
}

void beNDMWStatusInfoWork_GetMetaObject(void)
{
    FUN_003b5f50();
}

void beNDMWStatusInfoWork_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)g_beNDMWStatusInfoWork_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c9870[0], 7);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_003c9130();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_003c9130();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_003c9130();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)FUN_003c9130();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004c9890[0], &DAT_004c98b0[0], &DAT_004c98d0[0], temp_s0);
}

