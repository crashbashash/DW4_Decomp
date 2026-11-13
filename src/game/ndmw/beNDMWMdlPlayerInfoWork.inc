void beNDMWMdlPlayerInfoWork_Create(int arg0) {
    FUN_003c0280();
    igMetaObject_CreateInstance(*(int *)0x58B3C8, arg0);
}

igMetaObject *FUN_003bfcc0(void) {
    if (g_beNDMWMdlPlayerInfoWork_metaObject[0] == 0) {
        g_beNDMWMdlPlayerInfoWork_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWMdlPlayerInfoWork_metaObject[0];
}

igMetaObject *beNDMWMdlPlayerInfoWork_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWMdlPlayerInfoWork_metaObject[0] != 0) {
        ready = (g_beNDMWMdlPlayerInfoWork_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_003c0280();
done:
    return g_beNDMWMdlPlayerInfoWork_metaObject[0];
}

int beNDMWMdlPlayerInfoWork_GetVTable(void) {
    PlayerInfoWorkView work;
    return *(int *)((char *)&work + *(int *)((char *)g_objectSystem[0] + 916));
}

Obj_3bfde0 *FUN_003bfde0(Obj_3bfde0 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = g_beNDMWMdlPEBaseInfoWork_vtable;
        arg0->rel(&arg0->m268);
        arg0->rel(&arg0->m264);
        arg0->rel(&arg0->m252);
        arg0->rel(&arg0->m248);
        arg0->rel(&arg0->m244);
        arg0->rel(&arg0->m240);
        if (arg0) {
            arg0->vt = g_beModelCtrlInfoWork_vtable;
            FUN_00198190((char *)arg0 + 232, -1);
            FUN_00350e90((char *)arg0 + 228, -1);
            StringRef_Destruct_00130720((char *)arg0 + 220, -1);
            FUN_00350e10((char *)arg0 + 212, -1);
            FUN_00229350((char *)arg0 + 208, -1);
            FUN_00350d90((char *)arg0 + 204, -1);
            FUN_00350d10((char *)arg0 + 200, -1);
            StringRef_Destruct_00130720((char *)arg0 + 184, -1);
            StringRef_Destruct_00130720((char *)arg0 + 180, -1);
            FUN_00350c90((char *)arg0 + 176, -1);
            FUN_0034c1b0((char *)arg0 + 172, -1);
            StringRef_Destruct_00130720((char *)arg0 + 116, -1);
            StringRef_Destruct_00130720((char *)arg0 + 96, -1);
            StringRef_Destruct_00130720((char *)arg0 + 92, -1);
            StringRef_Destruct_00130720((char *)arg0 + 88, -1);
            FUN_00350c10((char *)arg0 + 80, -1);
            StringRef_Destruct_00130720((char *)arg0 + 76, -1);
            FUN_001354b0((char *)arg0 + 72, -1);
            StringRef_Destruct_00130720((char *)arg0 + 56, -1);
            StringRef_Destruct_00130720((char *)arg0 + 52, -1);
            StringRef_Destruct_00130720((char *)arg0 + 48, -1);
            ObjectRef_Destruct_00150eb0((char *)arg0 + 44, -1);
            ObjectRef_Destruct_001c6460((char *)arg0 + 40, -1);
            ObjectRef_Destruct_001c6460((char *)arg0 + 36, -1);
            FUN_00350b90((char *)arg0 + 24, -1);
            StringRef_Destruct_00130720((char *)arg0 + 20, -1);
            FUN_00350b10((char *)arg0 + 12, -1);
            FUN_00350b10((char *)arg0 + 8, -1);
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void FUN_003c0280(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPlayerInfoWork_Register);
}

void *beNDMWMdlPlayerInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        ((igMetaObject_3c02a0 * *)g_beNDMWMdlPlayerInfoWork_metaObject),
        beNDMWMdlPEBaseInfoWork_Register,
        beNDMWMdlPEBaseInfoWork_GetPublishedMetaObject,
        beNDMWMdlPlayerInfoWork_GetMetaObject,
        beNDMWMdlPlayerInfoWork_className,
        0x130, /* instance size */
        beNDMWMdlPlayerInfoWork_GetVTable,
        beNDMWMdlPlayerInfoWork_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlPlayerInfoWork_callbackList /* callback list */
    );
}

void beNDMWMdlPlayerInfoWork_GetMetaObject(void)
{
    beNDMWMdlPlayerInfoWork_ResolveMetaObject();
}

igMetaObject *FUN_003c0340(void) {
    return g_beNDMWMdlPEBaseInfoWork_metaObject[0];
}

void beNDMWMdlPlayerInfoWork_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWMdlPlayerInfoWork_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNDMWMdlPlayerInfoWork_ctorTable[0], 8);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, &g_beNDMWMdlPlayerInfoWork_fieldTable[0], &DAT_004ca900[0], &DAT_004ca920[0], temp_s2);
}

int DamageSeq_GetMetaEnum(void) {
    if (DAT_0058b410[0] == 0) {
        DAT_0058b410[0] = igMetaEnum_Create(&DamageSeq[0], &DAT_004ca940[0], &DAT_004ca970[0], 0xA);
    }
    return DAT_0058b410[0];
}

int StatusName_GetMetaEnum(void) {
    if (DAT_0058b418[0] == 0) {
        DAT_0058b418[0] = igMetaEnum_Create(&StatusName[0], &DAT_004ca9a0[0], &DAT_004ca9d0[0], 0xB);
    }
    return DAT_0058b418[0];
}

int MsgAction_GetMetaEnum(void) {
    if (DAT_0058b420[0] == 0) {
        DAT_0058b420[0] = igMetaEnum_Create(&MsgAction_2[0], &DAT_004caa00[0], &DAT_004caa40[0], 0x10);
    }
    return DAT_0058b420[0];
}

