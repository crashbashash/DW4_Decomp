void FUN_00362f90(int arg0) {
    FUN_003630b0();
    igMetaObject_CreateInstance(*(int *)0x589780, arg0);
}

void *FUN_00362fd0(void) {
    igMetaObject *g = g_beFileChkObj_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003630b0();
    }
    return g_beFileChkObj_metaObject[0];
}

int beFileChkObj_GetVTable(void) {
    struct F_363020 f;
    int **pr;
    int temp_s0;
    int *o;

    igObject_InitHeader(&f);
    f.vt = &DAT_005357b0[0];
    pr = &f.ref;
    *pr = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.vt = &DAT_005357b0[0];
    if (pr != 0) {
        if (*pr != 0) {
            o = *pr;
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return temp_s0;
}

void FUN_003630b0(void)
{
    igMetaObject_RunStaticInit(beFileChkObj_Register);
}

void *beFileChkObj_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFileChkObj_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beFileChkObj_GetMetaObject,
        beFileChkObj_className,
        0xc, /* instance size */
        beFileChkObj_GetVTable,
        beFileChkObj_InitFields,
        0, /* extra callback item */
        g_beFileChkObj_callbackList /* callback list */
    );
}

void beFileChkObj_GetMetaObject(void)
{
    FUN_00362fd0();
}

void beFileChkObj_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beFileChkObj_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c6f80[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002c4ce0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c6f88[0], &DAT_004c6f90[0], &DAT_004c6f98[0], temp_s2);
}

