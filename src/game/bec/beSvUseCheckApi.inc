igMetaObject *g_beSvUseCheckApi_metaObject;

void beSvUseCheckApi_Create(int allocator) {
    beSvUseCheckApi_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588268, allocator);
}

void *beSvUseCheckApi_GetMetaObject(void) {
    igMetaObject *g = g_beSvUseCheckApi_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvUseCheckApi_EnsureRegistered();
    }
    return g_beSvUseCheckApi_metaObject;
}

int beSvUseCheckApi_GetVTable(void) {
    beSvUseCheckApi obj;
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
    obj._vtable = (int)&g_beSvUseCheckApi_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beSaveApi_vtable[0];
    igObjectRef_Release(iconWorkSlot);
    igObjectRef_Release(mountWorkSlot);
    igObjectRef_Release(imageWorkSlot);
    return vtable;
}

void beSvUseCheckApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvUseCheckApi_Register);
}

void *beSvUseCheckApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvUseCheckApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvUseCheckApi_GetMetaObjectFunction,
        "beSvUseCheckApi",
        0x4c, /* instance size */
        beSvUseCheckApi_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvUseCheckApi_GetMetaObjectFunction(void)
{
    beSvUseCheckApi_GetMetaObject();
}

