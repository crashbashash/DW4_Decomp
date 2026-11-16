igMetaObject *g_libNdmwRuntimePlugin_metaObject;
igMetaField *g_libNdmwRuntimePlugin_afsSetupMetaField;
igMetaField *g_libNdmwRuntimePlugin_stageCtlMetaField;
igMetaField *g_libNdmwRuntimePlugin_panelWazaMetaField;
igMetaField *g_libNdmwRuntimePlugin_logoMetaField;
igMetaField *g_libNdmwRuntimePlugin_title2MetaField;
igMetaField *g_libNdmwRuntimePlugin_loadCtrl2MetaField;
igMetaField *g_libNdmwRuntimePlugin_loadIntf2MetaField;
igMetaField *g_libNdmwRuntimePlugin_saveCtrlMetaField;
igMetaField *g_libNdmwRuntimePlugin_saveIntfMetaField;
igMetaField *g_libNdmwRuntimePlugin_gameRamMetaField;
igMetaField *g_libNdmwRuntimePlugin_statusMetaField;
igMetaField *g_libNdmwRuntimePlugin_mdlPlayerMetaField;
igMetaField *g_libNdmwRuntimePlugin_mdlPlayer2MetaField;
igMetaField *g_libNdmwRuntimePlugin_mdlPBulletMetaField;
igMetaField *g_libNdmwRuntimePlugin_mdlEnemyMetaField;
igMetaField *g_libNdmwRuntimePlugin_mdlEBulletMetaField;
igMetaField *g_libNdmwRuntimePlugin_mdlObjectMetaField;
igMetaField *g_libNdmwRuntimePlugin_mdlItemMetaField;
igMetaField *g_libNdmwRuntimePlugin_mdlEffectMetaField;
igMetaField *g_libNdmwRuntimePlugin_mdlMapBaseMetaField;
igMetaField *g_libNdmwRuntimePlugin_mdlMapCursorMetaField;

igMetaObject *libNdmwRuntimePlugin_GetMetaObject(void) {
    igMetaObject *g = g_libNdmwRuntimePlugin_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    libNdmwRuntimePlugin_EnsureRegistered();
done:
    return g_libNdmwRuntimePlugin_metaObject;
}

int libNdmwRuntimePlugin_GetVTable(void) {
    NdmwRuntimePluginView plugin;
    return *(int *)((char *)&plugin + *(int *)((char *)g_objectSystem[0] + 916));
}

igSmartPointer<igObject> *igSmartPointer_beNDMWAfsSetup_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWStageCtl_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWPanelWaza_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWLogo_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWTitle2_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWLoadCtrl2_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWLoadIntf2_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWSaveCtrl_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWSaveIntf_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWGameRam_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWStatus_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlPlayer_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlPlayer2_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlPBullet_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlEnemy_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlEBullet_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlObject_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlItem_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlEffect_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlMapBase_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlMapCursor_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlMapCursor_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlMapBase_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlEffect_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlItem_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlObject_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlEBullet_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlEnemy_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlPBullet_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlPlayer2_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWMdlPlayer_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWStatus_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWGameRam_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWSaveIntf_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWSaveCtrl_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWLoadIntf2_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWLoadCtrl2_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWTitle2_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWLogo_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWPanelWaza_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWStageCtl_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWAfsSetup_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

void libNdmwRuntimePlugin_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(libNdmwRuntimePlugin_Register);
}

static igMetaObjectCallback g_libNdmwRuntimePlugin_callbackList[] = { beNDMWAfsSetup_EnsureRegistered, beNDMWStageCtl_EnsureRegistered, beNDMWPanelWaza_EnsureRegistered, beNDMWLogo_EnsureRegistered, beNDMWTitle2_EnsureRegistered, beNDMWLoadCtrl2_EnsureRegistered, beNDMWLoadIntf2_EnsureRegistered, beNDMWSaveCtrl_EnsureRegistered, beNDMWSaveIntf_EnsureRegistered, beNDMWGameRam_EnsureRegistered, beNDMWStatus_EnsureRegistered, beNDMWMdlPlayer_EnsureRegistered, beNDMWMdlPlayer2_EnsureRegistered, beNDMWMdlPBullet_EnsureRegistered, beNDMWMdlEnemy_EnsureRegistered, beNDMWMdlEBullet_EnsureRegistered, beNDMWMdlObject_EnsureRegistered, beNDMWMdlItem_EnsureRegistered, beNDMWMdlEffect_EnsureRegistered, beNDMWMdlMapBase_EnsureRegistered, beNDMWMdlMapCursor_EnsureRegistered, 0 };

void *libNdmwRuntimePlugin_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_libNdmwRuntimePlugin_metaObject,
        igInsightPlugin_Register,
        igInsightPlugin_GetPublishedMetaObject,
        libNdmwRuntimePlugin_GetMetaObjectFunction,
        "libNdmwRuntimePlugin",
        0x5c, /* instance size */
        libNdmwRuntimePlugin_GetVTable,
        libNdmwRuntimePlugin_InitFields,
        0, /* extra callback item */
        g_libNdmwRuntimePlugin_callbackList /* callback list */
    );
}

void libNdmwRuntimePlugin_GetMetaObjectFunction(void)
{
    libNdmwRuntimePlugin_GetMetaObject();
}

static FieldFactory g_libNdmwRuntimePlugin_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_libNdmwRuntimePlugin_fieldTable[] = {
    "_afsSetup",
    "_stageCtl",
    "_panelWaza",
    "_logo",
    "_title2",
    "_loadCtrl2",
    "_loadIntf2",
    "_saveCtrl",
    "_saveIntf",
    "_gameRam",
    "_status",
    "_mdlPlayer",
    "_mdlPlayer2",
    "_mdlPBullet",
    "_mdlEnemy",
    "_mdlEBullet",
    "_mdlObject",
    "_mdlItem",
    "_mdlEffect",
    "_mdlMapBase",
    "_mdlMapCursor",
};
static igMetaField **g_libNdmwRuntimePlugin_fieldHandles[] = {
    &g_libNdmwRuntimePlugin_afsSetupMetaField,
    &g_libNdmwRuntimePlugin_stageCtlMetaField,
    &g_libNdmwRuntimePlugin_panelWazaMetaField,
    &g_libNdmwRuntimePlugin_logoMetaField,
    &g_libNdmwRuntimePlugin_title2MetaField,
    &g_libNdmwRuntimePlugin_loadCtrl2MetaField,
    &g_libNdmwRuntimePlugin_loadIntf2MetaField,
    &g_libNdmwRuntimePlugin_saveCtrlMetaField,
    &g_libNdmwRuntimePlugin_saveIntfMetaField,
    &g_libNdmwRuntimePlugin_gameRamMetaField,
    &g_libNdmwRuntimePlugin_statusMetaField,
    &g_libNdmwRuntimePlugin_mdlPlayerMetaField,
    &g_libNdmwRuntimePlugin_mdlPlayer2MetaField,
    &g_libNdmwRuntimePlugin_mdlPBulletMetaField,
    &g_libNdmwRuntimePlugin_mdlEnemyMetaField,
    &g_libNdmwRuntimePlugin_mdlEBulletMetaField,
    &g_libNdmwRuntimePlugin_mdlObjectMetaField,
    &g_libNdmwRuntimePlugin_mdlItemMetaField,
    &g_libNdmwRuntimePlugin_mdlEffectMetaField,
    &g_libNdmwRuntimePlugin_mdlMapBaseMetaField,
    &g_libNdmwRuntimePlugin_mdlMapCursorMetaField,
};
static int g_libNdmwRuntimePlugin_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
    76,
    80,
    84,
    88,
};

void libNdmwRuntimePlugin_InitFields(void) {
    void *afsSetup;
    void *gameRam;
    void *status;
    void *mdlPlayer;
    void *mdlPlayer2;
    void *mdlPBullet;
    void *mdlEnemy;
    void *mdlEBullet;
    void *mdlObject;
    void *mdlItem;
    void *mdlEffect;
    void *mdlMapBase;
    void *mdlMapCursor;
    void *stageCtl;
    void *panelWaza;
    void *logo;
    void *title2;
    void *loadCtrl2;
    void *loadIntf2;
    void *saveCtrl;
    void *saveIntf;
    void *meta;
    int base;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)g_libNdmwRuntimePlugin_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_libNdmwRuntimePlugin_ctorTable, 0x15);
    afsSetup = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)afsSetup)->_metaObject = (int)beNDMWAfsSetup_GetOrCreateMetaObject();
    stageCtl = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)stageCtl)->_metaObject = (int)beNDMWStageCtl_GetOrCreateMetaObject();
    panelWaza = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)panelWaza)->_metaObject = (int)beNDMWPanelWaza_GetOrCreateMetaObject();
    logo = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)logo)->_metaObject = (int)beNDMWLogo_GetOrCreateMetaObject();
    title2 = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)title2)->_metaObject = (int)beNDMWTitle2_GetOrCreateMetaObject();
    loadCtrl2 = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)loadCtrl2)->_metaObject = (int)beNDMWLoadCtrl2_GetOrCreateMetaObject();
    loadIntf2 = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((igObjectRefMetaField *)loadIntf2)->_metaObject = (int)beNDMWLoadIntf2_GetOrCreateMetaObject();
    saveCtrl = (void *)(igMetaObject_GetFieldAt(meta, base + 7));
    ((igObjectRefMetaField *)saveCtrl)->_metaObject = (int)beNDMWSaveCtrl_GetOrCreateMetaObject();
    saveIntf = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)saveIntf)->_metaObject = (int)beNDMWSaveIntf_GetOrCreateMetaObject();
    gameRam = (void *)(igMetaObject_GetFieldAt(meta, base + 9));
    ((igObjectRefMetaField *)gameRam)->_metaObject = (int)beNDMWGameRam_GetOrCreateMetaObject();
    status = (void *)(igMetaObject_GetFieldAt(meta, base + 0xA));
    ((igObjectRefMetaField *)status)->_metaObject = (int)beNDMWStatus_GetOrCreateMetaObject();
    mdlPlayer = (void *)(igMetaObject_GetFieldAt(meta, base + 0xB));
    ((igObjectRefMetaField *)mdlPlayer)->_metaObject = (int)beNDMWMdlPlayer_GetOrCreateMetaObject();
    mdlPlayer2 = (void *)(igMetaObject_GetFieldAt(meta, base + 0xC));
    ((igObjectRefMetaField *)mdlPlayer2)->_metaObject = (int)beNDMWMdlPlayer2_GetOrCreateMetaObject();
    mdlPBullet = (void *)(igMetaObject_GetFieldAt(meta, base + 0xD));
    ((igObjectRefMetaField *)mdlPBullet)->_metaObject = (int)beNDMWMdlPBullet_GetOrCreateMetaObject();
    mdlEnemy = (void *)(igMetaObject_GetFieldAt(meta, base + 0xE));
    ((igObjectRefMetaField *)mdlEnemy)->_metaObject = (int)beNDMWMdlEnemy_GetOrCreateMetaObject();
    mdlEBullet = (void *)(igMetaObject_GetFieldAt(meta, base + 0xF));
    ((igObjectRefMetaField *)mdlEBullet)->_metaObject = (int)beNDMWMdlEBullet_GetOrCreateMetaObject();
    mdlObject = (void *)(igMetaObject_GetFieldAt(meta, base + 0x10));
    ((igObjectRefMetaField *)mdlObject)->_metaObject = (int)beNDMWMdlObject_GetOrCreateMetaObject();
    mdlItem = (void *)(igMetaObject_GetFieldAt(meta, base + 0x11));
    ((igObjectRefMetaField *)mdlItem)->_metaObject = (int)beNDMWMdlItem_GetOrCreateMetaObject();
    mdlEffect = (void *)(igMetaObject_GetFieldAt(meta, base + 0x12));
    ((igObjectRefMetaField *)mdlEffect)->_metaObject = (int)beNDMWMdlEffect_GetOrCreateMetaObject();
    mdlMapBase = (void *)(igMetaObject_GetFieldAt(meta, base + 0x13));
    ((igObjectRefMetaField *)mdlMapBase)->_metaObject = (int)beNDMWMdlMapBase_GetOrCreateMetaObject();
    mdlMapCursor = (void *)(igMetaObject_GetFieldAt(meta, base + 0x14));
    ((igObjectRefMetaField *)mdlMapCursor)->_metaObject = (int)beNDMWMdlMapCursor_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_libNdmwRuntimePlugin_fieldTable, g_libNdmwRuntimePlugin_fieldHandles, g_libNdmwRuntimePlugin_fieldOffsets, base);
}

