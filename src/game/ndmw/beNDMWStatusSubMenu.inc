void beNDMWStatusSubMenu_Create(int arg0) {
    FUN_003b9120();
    igMetaObject_CreateInstance(*(int *)0x58AE38, arg0);
}

void *FUN_003b8f90(void) {
    igMetaObject *g = g_beNDMWStatusSubMenu_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b9120();
    }
    return g_beNDMWStatusSubMenu_metaObject[0];
}

int beNDMWStatusSubMenu_GetVTable(void) {
    union U_3b8fe0 u;
    int temp_s2;

    igObject_InitHeader(u.b);
    u.w[13] = 0;
    u.w[14] = 0;
    u.w[15] = 0;
    u.w[16] = 0;
    u.w[17] = 0;
    u.w[18] = 0;
    u.w[19] = 0;
    u.w[0] = (int)(&DAT_0053ec20[0]);
    u.w[22] = 0;
    u.w[24] = 0;
    u.w[25] = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_0053ec20[0]);
    ObjectRef_Destruct_00150eb0(&u.w[25], -1);
    ObjectRef_Destruct_00150eb0(&u.w[24], -1);
    FUN_003b90a0((void **)(&u.w[22]), (short)(-1));
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)u.b, (long long)0);
    return temp_s2;
}

void **FUN_003b90a0(void **arg0, short arg1) {
    S_temp_a0_3b90a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_3b90a0 *)(*arg0);
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

void FUN_003b9120(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSubMenu_Register);
}

void *beNDMWStatusSubMenu_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusSubMenu_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusSubMenu_GetMetaObject,
        beNDMWStatusSubMenu_className,
        0x68, /* instance size */
        beNDMWStatusSubMenu_GetVTable,
        beNDMWStatusSubMenu_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusSubMenu_callbackList /* callback list */
    );
}

void beNDMWStatusSubMenu_GetMetaObject(void)
{
    FUN_003b8f90();
}

void beNDMWStatusSubMenu_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWStatusSubMenu_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNDMWStatusSubMenu_ctorTable[0], 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003bb570();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beNDMWStatusSubMenu_fieldTable[0], &DAT_004c9cc0[0], &DAT_004c9ce0[0], temp_s2);
}

