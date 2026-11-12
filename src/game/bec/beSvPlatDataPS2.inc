void *FUN_00347820(void) {
    igMetaObject *g = g_beSvPlatDataPS2_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00347970();
    }
    return g_beSvPlatDataPS2_metaObject[0];
}

int beSvPlatDataPS2_GetVTable(void) {
    union U_347870 u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[12] = 0;
    u.vt = (int)&DAT_00538bc0[0];
    *(int *)&u.b[24] = 0;
    *(int *)&u.b[28] = 0;
    *(int *)&u.b[184] = 0;
    *(int *)&u.b[188] = 0;
    *(int *)&u.b[192] = 0;
    *(int *)&u.b[212] = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00538bc0[0];
    FUN_0014aa70(&u.b[212], -1);
    StringRef_Destruct_00130720(&u.b[192], -1);
    StringRef_Destruct_00130720(&u.b[188], -1);
    StringRef_Destruct_00130720(&u.b[184], -1);
    StringRef_Destruct_00130720(&u.b[28], -1);
    StringRef_Destruct_00130720(&u.b[24], -1);
    FUN_00347150((O_347150 *)u.b, (short)0);
    return t;
}

void FUN_00347970(void)
{
    igMetaObject_RunStaticInit(beSvPlatDataPS2_Register);
}

void *beSvPlatDataPS2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvPlatDataPS2_metaObject,
        beSvPlatBaseData_Register,
        beSvPlatBaseData_GetPublishedMetaObject,
        beSvPlatDataPS2_GetMetaObject,
        beSvPlatDataPS2_className,
        0xd8, /* instance size */
        beSvPlatDataPS2_GetVTable,
        beSvPlatDataPS2_InitFields,
        0, /* extra callback item */
        g_beSvPlatDataPS2_callbackList /* callback list */
    );
}

void beSvPlatDataPS2_GetMetaObject(void)
{
    FUN_00347820();
}

void beSvPlatDataPS2_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    igEnumMetaField *temp_s0;
    igMetaObject *temp_s1;
    igEnumMetaField *temp_v0_2;

    temp_s1 = (igMetaObject *)(((void * *)g_beSvPlatDataPS2_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c3d90[0], 0x16);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00502570[0]));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->_metaFields, temp_v0);
    temp_v0_2 = (igEnumMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    FUN_002ea4b0(temp_v0_2, 5);
    temp_v0_2->_externalEnumStorage = (int)(&DAT_00588090[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = (int)temp_v0_2->_refCount - 1;
    if (((unsigned long long) ((long long)(int)temp_v0_2->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 4); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 5); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 6); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 7); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 8); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 9); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xA); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xB); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xC); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xD); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xE); temp_s0->_getMetaEnumFunction = 4;
    temp_s0 = (igEnumMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x13); temp_s0->_getMetaEnumFunction = 2;
    igObjectRefMetaField *temp_s4 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0x15));
    temp_s4->_metaObject = igObjectList_GetOrCreateMetaObject();
    temp_s4->_construct = 1;
    igMetaObject_NameFields(temp_s1, &DAT_004c3df0[0], &DAT_004c3e50[0], &DAT_004c3eb0[0], temp_s2);
}

