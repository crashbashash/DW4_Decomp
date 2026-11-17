igMetaObject *g_beParticleCtrl2InfoRam_metaObject;
igMetaField *g_beParticleCtrl2InfoRam_transformMetaField;
igMetaField *g_beParticleCtrl2InfoRam_particleTimerMetaField;
igMetaField *g_beParticleCtrl2InfoRam_workMetaField;

void *beParticleCtrl2InfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beParticleCtrl2InfoRam_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beParticleCtrl2InfoRam_EnsureRegistered();
    }
    return g_beParticleCtrl2InfoRam_metaObject;
}

int beParticleCtrl2InfoRam_GetVTable(void) {
    beParticleCtrl2InfoRam obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._dataList = 0;
    obj._vtable = (int)&g_beParticleCtrl2InfoRam_vtable[0];
    obj._transform = 0;
    obj._particleTimer = 0;
    obj._work = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beParticleCtrl2InfoRam_vtable[0];
    igSmartPointer_beParticleCtrl2InfoWork_Destruct((igSmartPointer<igObject> *)(&obj._work), -1);
    igSmartPointer_ParticleTimer_Destruct((igSmartPointer<igObject> *)(&obj._particleTimer), (short)(-1));
    igSmartPointer_igTransform_Destruct((igSmartPointer<igObject> *)&obj._transform, -1);
    beBaseInfoRam_Destroy((beBaseInfoRam *)&obj, (long long)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_ParticleTimer_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beParticleCtrl2InfoWork_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void beParticleCtrl2InfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beParticleCtrl2InfoRam_Register);
}

static igMetaObjectCallback g_beParticleCtrl2InfoRam_callbackList[] = { igTransform_EnsureRegistered, ParticleTimer_EnsureRegistered, beParticleCtrl2InfoWork_EnsureRegistered, 0 };

CallbackArray *beParticleCtrl2InfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beParticleCtrl2InfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beParticleCtrl2InfoRam_GetMetaObjectFunction,
        "beParticleCtrl2InfoRam",
        0x38, /* instance size */
        beParticleCtrl2InfoRam_GetVTable,
        beParticleCtrl2InfoRam_InitFields,
        0, /* extra callback item */
        g_beParticleCtrl2InfoRam_callbackList /* callback list */
    );
}

void beParticleCtrl2InfoRam_GetMetaObjectFunction(void)
{
    beParticleCtrl2InfoRam_GetMetaObject();
}

static FieldFactory g_beParticleCtrl2InfoRam_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beParticleCtrl2InfoRam_fieldTable[] = {
    "_transform",
    "_particleTimer",
    "_work",
};
static igMetaField **g_beParticleCtrl2InfoRam_fieldHandles[] = {
    &g_beParticleCtrl2InfoRam_transformMetaField,
    &g_beParticleCtrl2InfoRam_particleTimerMetaField,
    &g_beParticleCtrl2InfoRam_workMetaField,
};
static int g_beParticleCtrl2InfoRam_fieldOffsets[] = {
    44,
    48,
    52,
};

void beParticleCtrl2InfoRam_InitFields(void) {
    int base;
    void *transform;
    void *particleTimer;
    void *work;
    igMetaObject *meta;

    meta = g_beParticleCtrl2InfoRam_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beParticleCtrl2InfoRam_ctorTable, 3);
    transform = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)transform)->_metaObject = (int)igTransform_GetOrCreateMetaObject();
    particleTimer = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)particleTimer)->_metaObject = (int)ParticleTimer_GetOrCreateMetaObject();
    work = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)work)->_metaObject = (int)beParticleCtrl2InfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beParticleCtrl2InfoRam_fieldTable, g_beParticleCtrl2InfoRam_fieldHandles, g_beParticleCtrl2InfoRam_fieldOffsets, base);
}

