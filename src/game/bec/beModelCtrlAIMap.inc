void *FUN_00354340(void) {
    igMetaObject *g = g_beModelCtrlAIMap_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00354510();
    }
    return g_beModelCtrlAIMap_metaObject[0];
}

int beModelCtrlAIMap_GetVTable(void) {
    union U_354390 u;
    int temp_s5;

    igObject_InitHeader(u.b);
    u.w[2] = 0;
    u.w[0] = (int)(&DAT_00537900[0]);
    u.w[7] = 0;
    u.w[8] = 0;
    u.w[9] = 0;
    u.w[10] = 0;
    u.w[11] = 0;
    u.w[12] = 0;
    temp_s5 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00537900[0]);
    StringRef_Destruct_00130720(&u.w[12], -1);
    StringRef_Destruct_00130720(&u.w[11], -1);
    FUN_00354490((struct R **)(&u.w[10]), (short)(-1));
    FUN_00354490((struct R **)(&u.w[9]), (short)(-1));
    FUN_00354490((struct R **)(&u.w[8]), (short)(-1));
    FUN_00354490((struct R **)(&u.w[7]), (short)(-1));
    FUN_00131bc0(u.b, 0);
    return temp_s5;
}

struct R **FUN_00354490(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_00354510(void)
{
    igMetaObject_RunStaticInit(beModelCtrlAIMap_Register);
}

void *beModelCtrlAIMap_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlAIMap_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlAIMap_GetMetaObject,
        beModelCtrlAIMap_className,
        0x34, /* instance size */
        beModelCtrlAIMap_GetVTable,
        beModelCtrlAIMap_InitFields,
        0, /* extra callback item */
        g_beModelCtrlAIMap_callbackList /* callback list */
    );
}

void beModelCtrlAIMap_GetMetaObject(void)
{
    FUN_00354340();
}

void beModelCtrlAIMap_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)g_beModelCtrlAIMap_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_beModelCtrlAIMap_ctorTable[0], 0xA);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_003546d0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_003546d0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_003546d0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_003546d0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &g_beModelCtrlAIMap_fieldTable[0], &DAT_004c5660[0], &DAT_004c5690[0], temp_s0);
}

