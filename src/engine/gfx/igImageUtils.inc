igMetaObject *igImageUtils_GetMetaObject(void)
{
    igMetaObject *g = g_igImageUtils_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014dcc0();
    return g_igImageUtils_metaObject[0];
}

void FUN_0014dcc0(void)
{
    igMetaObject_RunStaticInit(igImageUtils_Register);
}

void igImageUtils_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igImageUtils_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igImageUtils_GetMetaObject,
        igImageUtils_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igImageUtils_GetMetaObject(void) {
    igImageUtils_GetMetaObject();
}

struct R **FUN_0014dd40(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

