void FUN_00365000(int arg0) {
    FUN_00365120();
    igMetaObject_CreateInstance(*(int *)0x589898, arg0);
}

void *FUN_00365040(void) {
    struct G *g = DAT_00589898[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00365120();
    }
    return DAT_00589898[0];
}

int beDataObjBool_GetVTable(void) {
    struct F_365090 o;
    int r;
    int *s;
    int *h;
    int c;

    igObject_InitHeader(&o);
    o.vt = DAT_00524950;
    o.str = 0;
    o.vt = DAT_005352f0;
    r = *(int *)((char *)&o + *(int *)(((char * *)DAT_00586dc8)[0] + 916));
    o.vt = DAT_00524950;
    if (&o.str != 0) {
        s = o.str;
        if (s != 0) {
            h = s - 2;
            c = s[-1] - 1;
            s[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader(*h, h);
        }
    }
    return r;
}

void FUN_00365120(void)
{
    igMetaObject_RunStaticInit(beDataObjBool_Register);
}

void *beDataObjBool_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataObjBool_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beDataObjBool_GetMetaObject,
        beDataObjBool_className,
        0x10, /* instance size */
        beDataObjBool_GetVTable,
        beDataObjBool_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beDataObjBool_GetMetaObject(void)
{
    FUN_00365040();
}

void beDataObjBool_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00589898)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c71d0[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c71d8[0], &DAT_004c71e0[0], &DAT_004c71e8[0], temp_s1);
}

