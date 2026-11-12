void FUN_003c4be0(int arg0) {
    FUN_003c4f00();
    igMetaObject_CreateInstance(*(int *)0x58BB00, arg0);
}

int FUN_003c4c20(void) {
    if (DAT_0058bb00[0] == 0) {
        DAT_0058bb00[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058bb00[0];
}

igMetaObject *beNDMWLoadCtrl2CommonIntf_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWLoadCtrl2CommonIntf_metaObject[0] != 0) {
        ready = (g_beNDMWLoadCtrl2CommonIntf_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_003c4f00();
done:
    return g_beNDMWLoadCtrl2CommonIntf_metaObject[0];
}

int beNDMWLoadCtrl2CommonIntf_GetVTable(void) {
    struct Obj_3c4cc0 obj;
    int temp_s3;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.vt = (&DAT_0053ce00[0]);
    obj.f20 = 0;
    obj.f24 = 0;
    obj.f28 = 0;
    obj.f34 = 0;
    temp_s3 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_0053ce00[0]);
    FUN_003b2a10((ObjectRefWord *)&obj.f34, -1);
    FUN_003c4e80((void **)&obj.f28, (short)(-1));
    FUN_003c4e00((void **)&obj.f24, (short)(-1));
    FUN_003c4d80((O *)&obj.f20, (short)(-1));
    FUN_00344030(&obj, 0);
    return temp_s3;
}

O *FUN_003c4d80(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

void **FUN_003c4e00(void **arg0, short arg1) {
    S_temp_a0_3c4e00 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_3c4e00 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_003c4e80(void **arg0, short arg1) {
    S_temp_a0_3c4e80 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_3c4e80 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_003c4f00(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadCtrl2CommonIntf_Register);
}

void *beNDMWLoadCtrl2CommonIntf_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        ((igMetaObject_3c4f20 * *)g_beNDMWLoadCtrl2CommonIntf_metaObject),
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadCtrl2CommonIntf_GetMetaObject,
        beNDMWLoadCtrl2CommonIntf_className,
        0x48, /* instance size */
        beNDMWLoadCtrl2CommonIntf_GetVTable,
        beNDMWLoadCtrl2CommonIntf_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadCtrl2CommonIntf_callbackList /* callback list */
    );
}

void beNDMWLoadCtrl2CommonIntf_GetMetaObject(void)
{
    beNDMWLoadCtrl2CommonIntf_ResolveMetaObject();
}

void beNDMWLoadCtrl2CommonIntf_InitFields(void) {
    void **temp_v0;
    int temp_s3;
    int temp_s2;
    void *temp_s1;
    igStringMetaField *temp_v0_2;

    temp_s1 = (void *)(((void * *)DAT_0058bb00)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004cb800[0], 0xE);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00510cd8[0]));
    temp_s3 = ObjectPointerList_FindIndex(((igMetaObject *)temp_s1)->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00512c90[0]);
    temp_v0_2->_externalEnumStorage = (int)(&DAT_0058bb08[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = temp_v0_2->_refCount - 1;
    if (((unsigned long long)(long long)temp_v0_2->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    void *temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    ((igObjectRefMetaField *)temp_s0)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s0)->_refCounted = 0;
    void *temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s0_2)->_metaObject = FUN_00342ce0();
    ((igObjectRefMetaField *)temp_s0_2)->_refCounted = 0;
    void *temp_s0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s0_3)->_metaObject = FUN_0036a230();
    ((igObjectRefMetaField *)temp_s0_3)->_refCounted = 0;
    void *temp_s0_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s0_4)->_metaObject = FUN_00232840();
    ((igObjectRefMetaField *)temp_s0_4)->_refCounted = 0;
    void *temp_s0_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s0_5)->_metaObject = FUN_003c61d0();
    ((igRefMetaField *)temp_s0_5)->_construct = 1;
    void *temp_s0_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 5));
    ((igObjectRefMetaField *)temp_s0_6)->_metaObject = FUN_003c66a0();
    ((igRefMetaField *)temp_s0_6)->_construct = 1;
    void *temp_s0_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 6));
    ((igObjectRefMetaField *)temp_s0_7)->_metaObject = FUN_003c5520();
    ((igRefMetaField *)temp_s0_7)->_construct = 1;
    void *temp_s0_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 9));
    ((igObjectRefMetaField *)temp_s0_8)->_metaObject = FUN_003c5200();
    ((igRefMetaField *)temp_s0_8)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004cb840[0], &DAT_004cb880[0], &DAT_004cb8c0[0], temp_s2);
}

