void beSystem_CreateInstance(int arg0) {
    FUN_00342f30();
    igMetaObject_CreateInstance(*(int *)0x587D08, arg0);
}

igMetaObject *FUN_00342ce0(void) {
    if (g_beSystem_metaObject[0] == 0) {
        g_beSystem_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSystem_metaObject[0];
}

void *FUN_00342d30(void) {
    unsigned char b;
    if (((void * *)g_beSystem_metaObject)[0] != 0) {
        b = (*(int *)((char *)(((void * *)g_beSystem_metaObject)[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00342f30();
done:
    return ((void * *)g_beSystem_metaObject)[0];
}

int beSystem_GetVTable(void) {
    struct Obj_342d80 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_0053b510[0];
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.w20 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053b510[0];
    FUN_00229350(&obj.w20, -1);
    FUN_001d35d0(&obj.w19, -1);
    FUN_001489a0(&obj.w18, -1);
    FUN_001d36d0(&obj.w17, -1);
    StringRef_Destruct_00130720(&obj.w15, -1);
    StringRef_Destruct_00130720(&obj.w14, -1);
    ObjectRef_Destruct_001c6460(&obj.w13, -1);
    FUN_00342eb0((void **)&obj.w12, (short)(-1));
    FUN_00231030(&obj, 0);
    return t;
}

void **FUN_00342eb0(void **arg0, short arg1) {
    S_temp_a0_342eb0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_342eb0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_00342f30(void)
{
    igMetaObject_RunStaticInit(beSystem_Register);
}

void *beSystem_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSystem_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beSystem_GetMetaObject,
        beSystem_className,
        0x68, /* instance size */
        beSystem_GetVTable,
        beSystem_InitFields,
        0, /* extra callback item */
        g_beSystem_callbackList /* callback list */
    );
}

void beSystem_GetMetaObject(void)
{
    FUN_00342d30();
}

void beSystem_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSystem_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beSystem_ctorTable[0], 0x1A);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 1.0f);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_001e4240();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_002b9120();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA), 0);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB), 1);
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_002c7300();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_002b9540();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xE));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_002c3440();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xF));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_0019f210();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x15), 1);
    igMetaObject_NameFields(temp_s0, &g_beSystem_fieldTable[0], &DAT_004c3680[0], &DAT_004c36f0[0], temp_s1);
}

