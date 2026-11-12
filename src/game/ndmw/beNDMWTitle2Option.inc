void FUN_003b2250(int arg0) {
    FUN_003b2370();
    igMetaObject_CreateInstance(*(int *)0x58AA58, arg0);
}

void *FUN_003b2290(void) {
    bool ok;
    if (g_beNDMWTitle2Option_metaObject[0] == 0) goto make;
    ok = !!(g_beNDMWTitle2Option_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_003b2370();
done:;
    return g_beNDMWTitle2Option_metaObject[0];
}

int beNDMWTitle2Option_GetVTable(void) {
    union U_3b22e0 u;
    int temp_s0;
    int temp_v0;
    int *temp_a1;
    int *temp_v1;
    char *q0;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_igNamedObject_vtable[0];
    q0 = &u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_0053dcf0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q0 != 0) {
        temp_v1 = *(int **)q0;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_003b2370(void)
{
    igMetaObject_RunStaticInit(beNDMWTitle2Option_Register);
}

void *beNDMWTitle2Option_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWTitle2Option_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWTitle2Option_GetMetaObject,
        beNDMWTitle2Option_className,
        0x38, /* instance size */
        beNDMWTitle2Option_GetVTable,
        beNDMWTitle2Option_InitFields,
        0, /* extra callback item */
        g_beNDMWTitle2Option_callbackList /* callback list */
    );
}

void beNDMWTitle2Option_GetMetaObject(void)
{
    FUN_003b2290();
}

void beNDMWTitle2Option_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;
    T_temp_v0_2 *temp_v0_2;

    temp_s1 = (void *)(((void * *)g_beNDMWTitle2Option_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c95d0[0], 0xA);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00510cd8[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (T_temp_v0_2 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00510ce0[0]);
    temp_v0_2->f28 = (int)(&DAT_0058aa60[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->references = temp_v0_2->references - 1;
    if (((unsigned long long)(long long)temp_v0_2->references & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    *(int *)((char *)(temp_s0) + 56) = FUN_00357910();
    *(char *)((char *)(temp_s0) + 60) = 0;
    igMetaObject_NameFields(temp_s1, &DAT_004c9600[0], &DAT_004c9630[0], &DAT_004c9660[0], temp_s2);
}

