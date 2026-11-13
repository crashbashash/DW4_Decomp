void beNDMWStatusCtrlFolder_Create(int arg0) {
    FUN_003ba140();
    igMetaObject_CreateInstance(*(int *)0x58AF08, arg0);
}

igMetaObject *FUN_003ba070(void) {
    igMetaObject *g = g_beNDMWStatusCtrlFolder_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_003ba140();
done:
    return g_beNDMWStatusCtrlFolder_metaObject[0];
}

int beNDMWStatusCtrlFolder_GetVTable(void) {
    struct W_3ba0c0 o;
    int r;

    igObject_InitHeader(&o);
    o.w[12] = 0;
    o.w[13] = 0;
    o.w[14] = 0;
    o.w[15] = 0;
    o.w[16] = 0;
    o.w[17] = 0;
    o.w[18] = 0;
    o.vt = DAT_0053ee70;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = DAT_0053ee70;
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&o, (long long)0);
    return r;
}

void FUN_003ba140(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlFolder_Register);
}

void *beNDMWStatusCtrlFolder_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusCtrlFolder_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlFolder_GetMetaObject,
        beNDMWStatusCtrlFolder_className,
        0x58, /* instance size */
        beNDMWStatusCtrlFolder_GetVTable,
        beNDMWStatusCtrlFolder_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusCtrlFolder_GetMetaObject(void)
{
    FUN_003ba070();
}

void beNDMWStatusCtrlFolder_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWStatusCtrlFolder_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9e70[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c9e78[0], &DAT_004c9e80[0], &DAT_004c9e88[0], temp_s1);
}

