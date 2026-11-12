void *FUN_0034da80(void) {
    struct G *g = DAT_00588690[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034db60();
    }
    return DAT_00588690[0];
}

int beNumVerData_GetVTable(void) {
    struct Obj_34dad0 obj;
    char *o;
    int t;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538400[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00538400[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

void FUN_0034db60(void)
{
    igMetaObject_RunStaticInit(beNumVerData_Register);
}

void *beNumVerData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNumVerData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNumVerData_GetMetaObject,
        beNumVerData_className,
        0x10, /* instance size */
        beNumVerData_GetVTable,
        beNumVerData_InitFields,
        0, /* extra callback item */
        g_beNumVerData_callbackList /* callback list */
    );
}

void beNumVerData_GetMetaObject(void)
{
    FUN_0034da80();
}

void beNumVerData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588690)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c49d8[0], 2);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2), -1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034dcd0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c49e0[0], &DAT_004c49e8[0], &DAT_004c49f0[0], temp_s2);
}

