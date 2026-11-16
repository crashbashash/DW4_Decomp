igMetaObject *g_beChangePosTransformInfo_metaObject;

igMetaObject *beChangePosTransformInfo_GetMetaObject(void) {
    igMetaObject *g = g_beChangePosTransformInfo_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beChangePosTransformInfo_EnsureRegistered();
done:
    return g_beChangePosTransformInfo_metaObject;
}

int beChangePosTransformInfo_GetVTable(void) {
    struct Obj_3685f0 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f14 = 0;
    obj.f18 = 0;
    obj.vt = (&g_beChangePosTransformInfo_vtable[0]);
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&g_beChangePosTransformInfo_vtable[0]);
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return temp_s0;
}

void beChangePosTransformInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beChangePosTransformInfo_Register);
}

void *beChangePosTransformInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beChangePosTransformInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beChangePosTransformInfo_GetMetaObjectFunction,
        "beChangePosTransformInfo",
        0x1c, /* instance size */
        beChangePosTransformInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beChangePosTransformInfo_GetMetaObjectFunction(void)
{
    beChangePosTransformInfo_GetMetaObject();
}

