void *FUN_0036b790(void) {
    struct G *g = DAT_00589e38[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036b8c0();
    }
    return DAT_00589e38[0];
}

int beAsTargetModelData_GetVTable(void) {
    union U_36b7e0 u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;
    int *q8;
    int *q12;

    igObject_InitHeader(u.b);
    q8 = (int *)&u.b[8];
    *q8 = 0;
    u.vt = (int)&DAT_00534540[0];
    q12 = (int *)&u.b[12];
    *q12 = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00534540[0];
    if (q12 != 0) {
        o = (char *)*q12;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    u.vt = (int)&DAT_00524950[0];
    if (q8 != 0) {
        temp_v1 = (int *)*q8;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return t;
}

void FUN_0036b8c0(void)
{
    igMetaObject_RunStaticInit(beAsTargetModelData_Register);
}

void *beAsTargetModelData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAsTargetModelData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAsTargetModelData_GetMetaObject,
        beAsTargetModelData_className,
        0x10, /* instance size */
        beAsTargetModelData_GetVTable,
        beAsTargetModelData_InitFields,
        0, /* extra callback item */
        g_beAsTargetModelData_callbackList /* callback list */
    );
}

void beAsTargetModelData_GetMetaObject(void)
{
    FUN_0036b790();
}

void beAsTargetModelData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00589e38)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7dd8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0036bc60();
    igMetaObject_NameFields(temp_s0, &DAT_004c7de0[0], &DAT_004c7de8[0], &DAT_004c7df0[0], temp_s2);
}

