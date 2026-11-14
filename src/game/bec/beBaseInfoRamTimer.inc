void beBaseInfoRamTimer_Create(int arg0) {
    FUN_0036a630();
    igMetaObject_CreateInstance(*(int *)0x589D78, arg0);
}

void *FUN_0036a550(void) {
    igMetaObject *g = g_beBaseInfoRamTimer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0036a630();
    }
    return g_beBaseInfoRamTimer_metaObject[0];
}

int beBaseInfoRamTimer_GetVTable(void) {
    struct Obj_36a5a0 o;
    int temp_s0;
    void **q;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    igObject_InitHeader(&o);
    q = &o.s;
    *q = 0;
    o.vt = &g_igNamedObject_vtable[0];
    o.vt = &DAT_00534830[0];
    temp_s0 = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_igNamedObject_vtable[0];
    if (q != 0) {
        temp_v1 = *q;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_0036a630(void)
{
    igMetaObject_RunStaticInit(beBaseInfoRamTimer_Register);
}

void *beBaseInfoRamTimer_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beBaseInfoRamTimer_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beBaseInfoRamTimer_GetMetaObject,
        beBaseInfoRamTimer_className,
        0x40, /* instance size */
        beBaseInfoRamTimer_GetVTable,
        beBaseInfoRamTimer_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beBaseInfoRamTimer_GetMetaObject(void)
{
    FUN_0036a550();
}

void beBaseInfoRamTimer_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beBaseInfoRamTimer_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beBaseInfoRamTimer_ctorTable[0], 6);
    igFloatMetaField_SetDefault((void *)(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1))), 1.0f);
    igFloatMetaField_SetDefault((void *)(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5))), 0.0f);
    igMetaObject_NameFields(temp_s0, &g_beBaseInfoRamTimer_fieldTable[0], &DAT_004c7cb0[0], &DAT_004c7cd0[0], temp_s1);
}

