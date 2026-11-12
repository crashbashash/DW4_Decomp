void FUN_00348f60(int arg0) {
    FUN_00349100();
    igMetaObject_CreateInstance(*(int *)0x588220, arg0);
}

S_348fa0 *FUN_00348fa0(void) {
    S_348fa0 *g = DAT_00588220[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_00349100();
done:
    return DAT_00588220[0];
}

int beSvWriteMediaApi_GetVTable(void) {
    struct Obj_348ff0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    obj.vt = &DAT_0053bdd0[0];
    obj.w16 = 0;
    obj.w17 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053bdd0[0];
    FUN_003484b0((struct Ref **)&obj.w17, (short)(-1));
    FUN_00349080((void **)&obj.w16, (long long)(-1));
    FUN_00348390((struct S_348390 *)&obj, (short)0);
    return t;
}

void **FUN_00349080(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_00349100(void)
{
    igMetaObject_RunStaticInit(beSvWriteMediaApi_Register);
}

void *beSvWriteMediaApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSvWriteMediaApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvWriteMediaApi_GetMetaObject,
        beSvWriteMediaApi_className,
        0x4c, /* instance size */
        beSvWriteMediaApi_GetVTable,
        beSvWriteMediaApi_InitFields,
        0, /* extra callback item */
        g_beSvWriteMediaApi_callbackList /* callback list */
    );
}

void beSvWriteMediaApi_GetMetaObject(void)
{
    FUN_00348fa0();
}

void beSvWriteMediaApi_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588220)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4078[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034a210();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0034ac90();
    igMetaObject_NameFields(temp_s0, &DAT_004c4080[0], &DAT_004c4088[0], &DAT_004c4090[0], temp_s2);
}

