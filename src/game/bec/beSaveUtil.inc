void FUN_00346c80(int arg0) {
    FUN_00346ef0();
    igMetaObject_CreateInstance(*(int *)0x588020, arg0);
}

int FUN_00346cc0(void) {
    if (((int *)DAT_00588020)[0] == 0) {
        ((int *)DAT_00588020)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00588020)[0];
}

void *FUN_00346d10(void) {
    struct G *g = DAT_00588020[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00346ef0();
    }
    return DAT_00588020[0];
}

int beSaveUtil_GetVTable(void) {
    struct Obj_346d60 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_0053c140[0];
    obj.w8 = 0;
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053c140[0];
    FUN_00346e70((void **)&obj.w9, (short)(-1));
    FUN_00346df0((void **)&obj.w8, -1);
    FUN_0033f5e0((O_33f5e0 *)&obj, (short)0);
    return t;
}

void **FUN_00346df0(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_00346e70(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_00346ef0(void)
{
    igMetaObject_RunStaticInit(beSaveUtil_Register);
}

void *beSaveUtil_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSaveUtil_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beSaveUtil_GetMetaObject,
        beSaveUtil_className,
        0x28, /* instance size */
        beSaveUtil_GetVTable,
        beSaveUtil_InitFields,
        0, /* extra callback item */
        g_beSaveUtil_callbackList /* callback list */
    );
}

void beSaveUtil_GetMetaObject(void)
{
    FUN_00346d10();
}

void beSaveUtil_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588020)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c3cf8[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034a000();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_003481b0();
    igMetaObject_NameFields(temp_s0, &DAT_004c3d00[0], &DAT_004c3d08[0], &DAT_004c3d10[0], temp_s2);
}

