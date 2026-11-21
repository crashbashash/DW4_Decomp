igMetaObject *g_beParticleCtrl2InfoWork_metaObject;
igMetaField *g_beParticleCtrl2InfoWork_positionLockNodeMetaField;
igMetaField *g_beParticleCtrl2InfoWork_positionLockOffsetMetaField;

beParticleCtrl2InfoWork *beParticleCtrl2InfoWork_Create(int allocator) {
    beParticleCtrl2InfoWork_EnsureRegistered();
    return (beParticleCtrl2InfoWork *)igMetaObject_CreateInstance(g_beParticleCtrl2InfoWork_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beParticleCtrl2InfoWork_GetOrCreateMetaObject(void) {
    if (g_beParticleCtrl2InfoWork_metaObject == 0) {
        g_beParticleCtrl2InfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beParticleCtrl2InfoWork_metaObject;
}

void *beParticleCtrl2InfoWork_GetMetaObject(void) {
    unsigned char b;
    if (g_beParticleCtrl2InfoWork_metaObject != 0) {
        b = (g_beParticleCtrl2InfoWork_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beParticleCtrl2InfoWork_EnsureRegistered();
done:
    return g_beParticleCtrl2InfoWork_metaObject;
}

int beParticleCtrl2InfoWork_GetVTable(void) {
    beParticleCtrl2InfoWork obj;
    int vtable;
    igObject **positionLockNodeSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beParticleCtrl2InfoWork_vtable[0];
    positionLockNodeSlot = (igObject **)&obj._positionLockNode;
    *positionLockNodeSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beParticleCtrl2InfoWork_vtable[0];
    igObjectRef_Release(positionLockNodeSlot);
    return vtable;
}

void beParticleCtrl2InfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beParticleCtrl2InfoWork_Register);
}

static igMetaObjectCallback g_beParticleCtrl2InfoWork_callbackList[] = { beModelCtrlNode2_EnsureRegistered, 0 };

CallbackArray *beParticleCtrl2InfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beParticleCtrl2InfoWork_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beParticleCtrl2InfoWork_GetMetaObjectFunction,
        "beParticleCtrl2InfoWork",
        0x18, /* instance size */
        beParticleCtrl2InfoWork_GetVTable,
        beParticleCtrl2InfoWork_InitFields,
        0, /* extra callback item */
        g_beParticleCtrl2InfoWork_callbackList /* callback list */
    );
}

void beParticleCtrl2InfoWork_GetMetaObjectFunction(void)
{
    beParticleCtrl2InfoWork_GetMetaObject();
}

static FieldFactory g_beParticleCtrl2InfoWork_ctorTable[] = {
    igObjectRefMetaField_Create,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
};
static const char *g_beParticleCtrl2InfoWork_fieldTable[] = {
    "_positionLockNode",
    "_positionLockOffset",
};
static igMetaField **g_beParticleCtrl2InfoWork_fieldHandles[] = {
    &g_beParticleCtrl2InfoWork_positionLockNodeMetaField,
    &g_beParticleCtrl2InfoWork_positionLockOffsetMetaField,
};
static int g_beParticleCtrl2InfoWork_fieldOffsets[] = {
    8,
    12,
};

void beParticleCtrl2InfoWork_InitFields(void) {
    int base;
    void *positionLockNode;
    igMetaObject *meta;

    meta = g_beParticleCtrl2InfoWork_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beParticleCtrl2InfoWork_ctorTable, 2);
    positionLockNode = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)positionLockNode)->_metaObject = (int)beModelCtrlNode2_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beParticleCtrl2InfoWork_fieldTable, g_beParticleCtrl2InfoWork_fieldHandles, g_beParticleCtrl2InfoWork_fieldOffsets, base);
}

