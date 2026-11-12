int FUN_00150060(int arg0) {
    FUN_00150200();
    return igMetaObject_CreateInstance(*(int *)0x55FF10, arg0);
}

igMetaObject *igTgaLoader_GetMetaObject(void)
{
    igMetaObject *g = g_igTgaLoader_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00150200();
    return g_igTgaLoader_metaObject[0];
}

int igTgaLoader_GetVTable(void) {
    Obj_1500f0 o;
    int **ps;
    int *temp_a0;
    int temp_s0;

    igObject_InitHeader(&o);
    ps = &o.ref;
    o.vt = &DAT_00525cc0[0];
    *ps = 0;
    temp_s0 = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_00525cc0[0];
    if (ps != 0) {
        temp_a0 = *ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

void **FUN_00150180(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_00150200(void)
{
    igMetaObject_RunStaticInit(igTgaLoader_Register);
}

void igTgaLoader_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTgaLoader_metaObject,
        igImageLoader_Register,
        igImageLoader_GetPublishedMetaObject,
        thunk_igTgaLoader_GetMetaObject,
        igTgaLoader_className,
        0x30, /* instance size */
        igTgaLoader_GetVTable,
        &igTgaLoader_InitFields,
        0, /* extra callback item */
        g_igTgaLoader_callbackList /* callback list */
    );
}

void thunk_igTgaLoader_GetMetaObject(void) {
    igTgaLoader_GetMetaObject();
}

igMetaObject *FUN_001502a0(void) {
    return g_igImageLoader_metaObject[0];
}

void igTgaLoader_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igTgaLoader_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00489150[0], 0xA);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002c4ce0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igMemoryRefMetaField *)temp_s1_2)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igMemoryRefMetaField *)temp_s1_3)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igMemoryRefMetaField *)temp_s1_4)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    igMetaObject_NameFields(temp_s0, &DAT_00489180[0], &DAT_004891b0[0], &DAT_004891e0[0], temp_s2);
}

