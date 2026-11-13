igMetaObject *igMediaFile_GetMetaObject(void)
{
    igMetaObject *g = g_igMediaFile_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c1430();
    return g_igMediaFile_metaObject[0];
}

int igMediaFile_GetVTable(void) {
    union U_2c1330 u;
    int temp_s0;
    char *ps;
    igObject_InitHeader((ObjectHeader *)u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[40] = 0;
    u.vt = (int)&DAT_0052f9a0[0];
    ps = &u.b[64];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(((void * *)g_objectSystem)[0]) + 916)];
    u.vt = (int)&DAT_0052f9a0[0];
    FUN_002c13b0((void **)ps, -1);
    FUN_002c0790((igFile *)u.b, 0);
    return temp_s0;
}

void **FUN_002c13b0(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_002c1430(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMediaFile_Register);
}

void igMediaFile_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMediaFile_metaObject),
        igFile_Register,
        igFile_GetPublishedMetaObject,
        thunk_igMediaFile_GetMetaObject,
        igMediaFile_className,
        0x44, /* instance size */
        igMediaFile_GetVTable,
        &igMediaFile_InitFields,
        0, /* extra callback item */
        g_igMediaFile_callbackList /* callback list */
    );
}

void thunk_igMediaFile_GetMetaObject(void) {
    igMediaFile_GetMetaObject();
}

void igMediaFile_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igMediaFile_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004c03e0[0], 9);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 7)));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 8)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_002c16e0();
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004c0410[0], (igMetaField ***)&DAT_004c0440[0], &DAT_004c0470[0], temp_s2);
}

