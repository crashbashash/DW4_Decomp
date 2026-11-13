void beMatCtrl_CreateInstance(int arg0) {
    FUN_0035a880();
    igMetaObject_CreateInstance(*(int *)0x589160, arg0);
}

igMetaObject *FUN_0035a750(void) {
    if (g_beMatCtrl_metaObject[0] == 0) {
        g_beMatCtrl_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beMatCtrl_metaObject[0];
}

void *FUN_0035a7a0(void) {
    struct G *g = ((struct G * *)g_beMatCtrl_metaObject)[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035a880();
    }
    return ((struct G * *)g_beMatCtrl_metaObject)[0];
}

int beMatCtrl_GetVTable(void) {
    struct Obj_35a7f0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[5] = 0;
    obj.vt = &DAT_0053aad0[0];
    obj.w[13] = 0;
    obj.w[14] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053aad0[0];
    ObjectRef_Destruct_00150eb0(&obj.w[14], -1);
    ObjectRef_Destruct_00150eb0(&obj.w[13], -1);
    FUN_0033f5e0((O_33f5e0 *)&obj, (short)0);
    return r;
}

void FUN_0035a880(void)
{
    igMetaObject_RunStaticInit(beMatCtrl_Register);
}

void *beMatCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMatCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beMatCtrl_GetMetaObject,
        beMatCtrl_className,
        0x44, /* instance size */
        beMatCtrl_GetVTable,
        beMatCtrl_InitFields,
        0, /* extra callback item */
        g_beMatCtrl_callbackList /* callback list */
    );
}

void beMatCtrl_GetMetaObject(void)
{
    FUN_0035a7a0();
}

void beMatCtrl_InitFields(void) {
    igMetaObject *temp_s0;
    int temp_s2;
    struct F_35a940 *temp_s1;
    struct F_35a940 *temp_s1_2;
    struct F_35a940 *temp_s1_3;
    struct F_35a940 *t;

    temp_s0 = g_beMatCtrl_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beMatCtrl_ctorTable[0], 9);
    t = ((struct F_35a940 *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    t->f52 = 4;
    temp_s1 = ((struct F_35a940 *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    temp_s1->f56 = igIntList_GetOrCreateMetaObject();
    temp_s1_2 = ((struct F_35a940 *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    temp_s1_2->f56 = igIntList_GetOrCreateMetaObject();
    temp_s1_3 = ((struct F_35a940 *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    temp_s1_3->f56 = (int)FUN_0035b770();
    temp_s1_3->f60 = 0;
    igMetaObject_NameFields(temp_s0, &g_beMatCtrl_fieldTable[0], &DAT_004c61e0[0], &DAT_004c6210[0], temp_s2);
}

