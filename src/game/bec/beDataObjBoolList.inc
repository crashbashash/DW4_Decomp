void FUN_00364d30(int arg0) {
    FUN_00364ea0();
    igMetaObject_CreateInstance(*(int *)0x589888, arg0);
}

void *FUN_00364d70(void) {
    unsigned char b;
    if (DAT_00589888[0] != 0) {
        b = (*(int *)((char *)(DAT_00589888[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00364ea0();
done:
    return DAT_00589888[0];
}

int beDataObjBoolList_GetVTable(void) {
    union U_364dc0 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00535350[0];
    q0 = (S_ref *)&u.b[12];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00535350[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&DAT_00524950[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
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

void FUN_00364ea0(void)
{
    igMetaObject_RunStaticInit(beDataObjBoolList_Register);
}

void *beDataObjBoolList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjBoolList_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjBoolList_GetMetaObject,
        beDataObjBoolList_className,
        0x10, /* instance size */
        beDataObjBoolList_GetVTable,
        beDataObjBoolList_InitFields,
        0, /* extra callback item */
        g_beDataObjBoolList_callbackList /* callback list */
    );
}

void beDataObjBoolList_GetMetaObject(void)
{
    FUN_00364d70();
}

void beDataObjBoolList_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00589888)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c71b0[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002cb110();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c71b8[0], &DAT_004c71c0[0], &DAT_004c71c8[0], temp_s2);
}

