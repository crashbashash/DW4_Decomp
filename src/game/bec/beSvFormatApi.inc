igMetaObject *g_beSvFormatApi_metaObject;

beSvFormatApi *beSvFormatApi_Create(int allocator) {
    beSvFormatApi_EnsureRegistered();
    return (beSvFormatApi *)igMetaObject_CreateInstance(g_beSvFormatApi_metaObject, (igMemoryPoolView *)allocator);
}

void *beSvFormatApi_GetMetaObject(void) {
    igMetaObject *g = g_beSvFormatApi_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvFormatApi_EnsureRegistered();
    }
    return g_beSvFormatApi_metaObject;
}

int beSvFormatApi_GetVTable(void) {
    beSvFormatApi obj;
    int vtable;
    igObject **iconWorkSlot;
    igObject **mountWorkSlot;
    igObject **imageWorkSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beSaveApi_vtable[0];
    imageWorkSlot = (igObject **)&obj._imageWork;
    *imageWorkSlot = 0;
    mountWorkSlot = (igObject **)&obj._mountWork;
    *mountWorkSlot = 0;
    iconWorkSlot = (igObject **)&obj._iconWork;
    *iconWorkSlot = 0;
    obj._vtable = (int)&g_beSvFormatApi_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beSaveApi_vtable[0];
    igObjectRef_Release(iconWorkSlot);
    igObjectRef_Release(mountWorkSlot);
    igObjectRef_Release(imageWorkSlot);
    return vtable;
}

void beSvFormatApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvFormatApi_Register);
}

CallbackArray *beSvFormatApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvFormatApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvFormatApi_GetMetaObjectFunction,
        "beSvFormatApi",
        0x40, /* instance size */
        beSvFormatApi_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvFormatApi_GetMetaObjectFunction(void)
{
    beSvFormatApi_GetMetaObject();
}

