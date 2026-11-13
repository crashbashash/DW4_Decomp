void beHitLandModel_CreateInstance(int arg0) {
    FUN_0035da30();
    igMetaObject_CreateInstance(*(int *)0x589350, arg0);
}

igMetaObject *FUN_0035d7c0(void) {
    if (g_beHitLandModel_metaObject[0] == 0) {
        g_beHitLandModel_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beHitLandModel_metaObject[0];
}

void *FUN_0035d810(void) {
    igMetaObject *g = g_beHitLandModel_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035da30();
    }
    return g_beHitLandModel_metaObject[0];
}

int beHitLandModel_GetVTable(void) {
    HitLandModelView model;
    return *(int *)((char *)&model + *(int *)((char *)g_objectSystem[0] + 916));
}

void **FUN_0035d930(void **arg0, int arg1) {
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
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_0035d9b0(void **arg0, short arg1) {
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
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_0035da30(void)
{
    igMetaObject_RunStaticInit(beHitLandModel_Register);
}

void *beHitLandModel_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandModel_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beHitLandModel_GetMetaObject,
        beHitLandModel_className,
        0x70, /* instance size */
        beHitLandModel_GetVTable,
        beHitLandModel_InitFields,
        0, /* extra callback item */
        g_beHitLandModel_callbackList /* callback list */
    );
}

void beHitLandModel_GetMetaObject(void)
{
    FUN_0035d810();
}

void beHitLandModel_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_beHitLandModel_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beHitLandModel_ctorTable[0], 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0035ded0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0035dc10();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0019e6c0();
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 1);
    igMetaObject_NameFields(temp_s0, &g_beHitLandModel_fieldTable[0], &DAT_004c6630[0], &DAT_004c6650[0], temp_s2);
}

