void FUN_003689f0(int arg0) {
    FUN_00368bc0();
    igMetaObject_CreateInstance(*(int *)0x589B90, arg0);
}

int FUN_00368a30(void) {
    if (((int *)DAT_00589b90)[0] == 0) {
        ((int *)DAT_00589b90)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589b90)[0];
}

void *FUN_00368a80(void) {
    struct G *g = DAT_00589b90[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00368bc0();
    }
    return DAT_00589b90[0];
}

int beCameraMode_GetVTable(void) {
    struct Obj_368ad0 o;
    int r;
    int *t;

    igObject_InitHeader(&o);
    o.vt = &DAT_00542960[0];
    igMatrix44f_SetIdentity(o.sub);
    o.vt = &DAT_0053a2b0[0];
    o.r1 = 0;
    o.r2 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0053a2b0[0];
    if (&o.r2 != 0) {
        t = o.r2;
        if (t != 0) {
            t[1] = t[1] - 1;
            if ((t[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    if (&o.r1 != 0) {
        t = o.r1;
        if (t != 0) {
            t[1] = t[1] - 1;
            if ((t[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    return r;
}

void FUN_00368bc0(void)
{
    igMetaObject_RunStaticInit(beCameraMode_Register);
}

void *beCameraMode_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCameraMode_metaObject,
        igViewMode_Register,
        igViewMode_GetPublishedMetaObject,
        beCameraMode_GetMetaObject,
        beCameraMode_className,
        0x78, /* instance size */
        beCameraMode_GetVTable,
        beCameraMode_InitFields,
        0, /* extra callback item */
        g_beCameraMode_callbackList /* callback list */
    );
}

void beCameraMode_GetMetaObject(void)
{
    FUN_00368a80();
}

int FUN_00368c80(void) {
    return DAT_0058ccf8[0];
}

void beCameraMode_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00589b90)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c77d0[0], 8);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019f670();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_001a4560();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_00232840();
    ((igObjectRefMetaField *)temp_s1_3)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c77f0[0], &DAT_004c7810[0], &DAT_004c7830[0], temp_s2);
}

