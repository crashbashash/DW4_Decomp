void *FUN_00366ca0(void) {
    bool ok;
    if (g_beCriFxInfo_metaObject[0] == 0) goto make;
    ok = !!(g_beCriFxInfo_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_00366e00();
done:;
    return g_beCriFxInfo_metaObject[0];
}

int beCriFxInfo_GetVTable(void) {
    struct Obj obj;
    int r;
    int *pb;
    int *pa;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.vt = &DAT_00534ef0[0];
    pa = &obj.f14;
    *pa = 0;
    pb = &obj.f20;
    *pb = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00534ef0[0];
    FUN_00366d80((void **)pb, -1);
    StringRef_Destruct_00130720(pa, -1);
    FUN_00131b20(&obj, 0);
    return r;
}

void **FUN_00366d80(void **arg0, int arg1) {
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
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_00366e00(void)
{
    igMetaObject_RunStaticInit(beCriFxInfo_Register);
}

void *beCriFxInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCriFxInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        beCriFxInfo_GetMetaObject,
        beCriFxInfo_className,
        0x24, /* instance size */
        beCriFxInfo_GetVTable,
        beCriFxInfo_InitFields,
        0, /* extra callback item */
        g_beCriFxInfo_callbackList /* callback list */
    );
}

void beCriFxInfo_GetMetaObject(void)
{
    FUN_00366ca0();
}

void beCriFxInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beCriFxInfo_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c74b0[0], 4);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2), 0);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), -1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), -1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00366fa0();
    igMetaObject_NameFields(temp_s0, &DAT_004c74c0[0], &DAT_004c74d0[0], &DAT_004c74e0[0], temp_s2);
}

