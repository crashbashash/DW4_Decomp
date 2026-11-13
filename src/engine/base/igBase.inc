igMetaObject *igBase_GetMetaObject(void)
{
    igMetaObject *g = g_igBase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002292d0();
    return g_igBase_metaObject[0];
}

void FUN_002292d0(void)
{
    igMetaObject_RunStaticInit(igBase_Register);
}

void igBase_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igBase_metaObject,
        igInterfaced_Register,
        igInterfaced_GetPublishedMetaObject,
        thunk_igBase_GetMetaObject,
        igBase_className,
        0x20, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBase_GetMetaObject(void) {
    igBase_GetMetaObject();
}

void **FUN_00229350(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_002293d0(void **arg0, int arg1) {
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
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

