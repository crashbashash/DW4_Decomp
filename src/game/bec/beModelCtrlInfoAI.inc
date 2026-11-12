void FUN_00352140(int arg0) {
    FUN_003522b0();
    igMetaObject_CreateInstance(*(int *)0x588AD0, arg0);
}

int FUN_00352180(void) {
    if (((int *)DAT_00588ad0)[0] == 0) {
        ((int *)DAT_00588ad0)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00588ad0)[0];
}

void *FUN_003521d0(void) {
    struct G *g = DAT_00588ad0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003522b0();
    }
    return DAT_00588ad0[0];
}

int beModelCtrlInfoAI_GetVTable(void) {
    struct F_352220 f;
    int **pr;
    int temp_s0;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(&f);
    f.vt = &DAT_00537e20[0];
    pr = &f.ref;
    *pr = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_00537e20[0];
    if (pr != 0) {
        if (*pr != 0) {
            temp_a1 = *pr - 2;
            temp_v0 = (*pr)[-1] - 1;
            (*pr)[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_003522b0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoAI_Register);
}

void *beModelCtrlInfoAI_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoAI_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlInfoAI_GetMetaObject,
        beModelCtrlInfoAI_className,
        0x24, /* instance size */
        beModelCtrlInfoAI_GetVTable,
        beModelCtrlInfoAI_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlInfoAI_GetMetaObject(void)
{
    FUN_003521d0();
}

void beModelCtrlInfoAI_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588ad0)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5270[0], 5);
    igMetaObject_NameFields(temp_s0, &DAT_004c5290[0], &DAT_004c52b0[0], &DAT_004c52d0[0], temp_s1);
}

