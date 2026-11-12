void FUN_0034f8e0(int arg0) {
    FUN_0034fa30();
    igMetaObject_CreateInstance(*(int *)0x588800, arg0);
}

void *FUN_0034f920(void) {
    struct G *g = DAT_00588800[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0034fa30();
    }
    return DAT_00588800[0];
}

int beModelCtrlSCEffect_GetVTable(void) {
    beModelCtrlSCEffect obj;
    char *o;
    int *a1;
    int v0;
    int t;
    int *p0, *p1;

    igObject_InitHeader(&obj);
    p0 = &obj._modelName;
    p1 = &obj._seqName;
    obj._vtable = (int)&DAT_0053aef0[0];
    *p0 = 0;
    *p1 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj._vtable = (int)&DAT_0053aef0[0];
    if (p1 != 0) {
        o = (char *)*p1;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    if (p0 != 0) {
        o = (char *)*p0;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void FUN_0034fa30(void)
{
    igMetaObject_RunStaticInit(beModelCtrlSCEffect_Register);
}

void *beModelCtrlSCEffect_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlSCEffect_metaObject,
        beModelCtrlSubComBase_Register,
        beModelCtrlSubComBase_GetPublishedMetaObject,
        beModelCtrlSCEffect_GetMetaObject,
        beModelCtrlSCEffect_className,
        0x3c, /* instance size */
        beModelCtrlSCEffect_GetVTable,
        beModelCtrlSCEffect_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlSCEffect_GetMetaObject(void)
{
    FUN_0034f920();
}

void beModelCtrlSCEffect_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588800)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4c80[0], 7);
    FUN_002ea4b0(((int)igMetaObject_GetFieldAt(temp_s0, temp_s1)), -1);
    igMetaObject_NameFields(temp_s0, &DAT_004c4ca0[0], &DAT_004c4cc0[0], &DAT_004c4ce0[0], temp_s1);
}

