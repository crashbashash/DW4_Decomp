igMetaObject *g_beSvFileFindApi_metaObject;

beSvFileFindApi *beSvFileFindApi_Create(int allocator) {
    beSvFileFindApi_EnsureRegistered();
    return (beSvFileFindApi *)igMetaObject_CreateInstance(g_beSvFileFindApi_metaObject, (igMemoryPoolView *)allocator);
}

void *beSvFileFindApi_GetMetaObject(void) {
    bool ok;
    if (g_beSvFileFindApi_metaObject == 0) goto make;
    ok = !!(g_beSvFileFindApi_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beSvFileFindApi_EnsureRegistered();
done:;
    return g_beSvFileFindApi_metaObject;
}

int beSvFileFindApi_GetVTable(void) {
    beSvFileFindApi obj;
    int vtable;
    igObject **iconWorkSlot;
    igObject **mountWorkSlot;
    igObject **imageWorkSlot;

    igObject_InitHeader(&obj);
    imageWorkSlot = (igObject **)&obj._imageWork;
    *imageWorkSlot = 0;
    obj._vtable = (int)(&g_beSaveApi_vtable[0]);
    mountWorkSlot = (igObject **)&obj._mountWork;
    *mountWorkSlot = 0;
    iconWorkSlot = (igObject **)&obj._iconWork;
    *iconWorkSlot = 0;
    obj._vtable = (int)(&g_beSvFileFindApi_vtable[0]);
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)(&g_beSaveApi_vtable[0]);
    igObjectRef_Release(iconWorkSlot);
    igObjectRef_Release(mountWorkSlot);
    igObjectRef_Release(imageWorkSlot);
    return vtable;
}

void beSvFileFindApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvFileFindApi_Register);
}

CallbackArray *beSvFileFindApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvFileFindApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvFileFindApi_GetMetaObjectFunction,
        "beSvFileFindApi",
        0x54, /* instance size */
        beSvFileFindApi_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvFileFindApi_GetMetaObjectFunction(void)
{
    beSvFileFindApi_GetMetaObject();
}

