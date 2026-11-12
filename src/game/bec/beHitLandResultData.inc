void FUN_0035e400(int arg0) {
    FUN_0035e520();
    igMetaObject_CreateInstance(*(int *)0x5893E8, arg0);
}

void *FUN_0035e440(void) {
    unsigned char b;
    if (DAT_005893e8[0] != 0) {
        b = (*(int *)((char *)(DAT_005893e8[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_0035e520();
done:
    return DAT_005893e8[0];
}

int beHitLandResultData_GetVTable(void) {
    union U_35e490 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00536290[0];
    ps = &u.b[8];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00536290[0];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
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

void FUN_0035e520(void)
{
    igMetaObject_RunStaticInit(beHitLandResultData_Register);
}

void *beHitLandResultData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandResultData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beHitLandResultData_GetMetaObject,
        beHitLandResultData_className,
        0x58, /* instance size */
        beHitLandResultData_GetVTable,
        beHitLandResultData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beHitLandResultData_GetMetaObject(void)
{
    FUN_0035e440();
}

void beHitLandResultData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_005893e8)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6760[0], 2);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1)), &DAT_00502a98[0]);
    igMetaObject_NameFields(temp_s0, &DAT_004c6768[0], &DAT_004c6770[0], &DAT_004c6778[0], temp_s1);
}

