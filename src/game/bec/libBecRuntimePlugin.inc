igMetaObject *g_libBecRuntimePlugin_metaObject;
igMetaField *g_libBecRuntimePlugin_particleCtrl2MetaField;
igMetaField *g_libBecRuntimePlugin_luaManagerMetaField;
igMetaField *g_libBecRuntimePlugin_matCtrlMetaField;
igMetaField *g_libBecRuntimePlugin_selectCtrlMetaField;
igMetaField *g_libBecRuntimePlugin_waterPlainMetaField;
igMetaField *g_libBecRuntimePlugin_action2MetaField;
igMetaField *g_libBecRuntimePlugin_meterCtrlMetaField;
igMetaField *g_libBecRuntimePlugin_targetObjMetaField;
igMetaField *g_libBecRuntimePlugin_weaponMetaField;
igMetaField *g_libBecRuntimePlugin_cameraCtrlMetaField;
igMetaField *g_libBecRuntimePlugin_point01MetaField;
igMetaField *g_libBecRuntimePlugin_bkColorMetaField;
igMetaField *g_libBecRuntimePlugin_cpTransformMetaField;
igMetaField *g_libBecRuntimePlugin_shadow01MetaField;
igMetaField *g_libBecRuntimePlugin_generaterMetaField;
igMetaField *g_libBecRuntimePlugin_hitLandModelMetaField;
igMetaField *g_libBecRuntimePlugin_hitLandDelivMetaField;
igMetaField *g_libBecRuntimePlugin_soundMetaField;
igMetaField *g_libBecRuntimePlugin_seCtlMetaField;
igMetaField *g_libBecRuntimePlugin_actionStarterMetaField;
igMetaField *g_libBecRuntimePlugin_layerCtlMetaField;
igMetaField *g_libBecRuntimePlugin_fontMetaField;
igMetaField *g_libBecRuntimePlugin_switchCtrlMetaField;
igMetaField *g_libBecRuntimePlugin_lightCtrlMetaField;
igMetaField *g_libBecRuntimePlugin_numberCtrlMetaField;
igMetaField *g_libBecRuntimePlugin_staticInfoCtlMetaField;
igMetaField *g_libBecRuntimePlugin_movieMetaField;
igMetaField *g_libBecRuntimePlugin_dbManagerMetaField;
igMetaField *g_libBecRuntimePlugin_saveUtilMetaField;
igMetaField *g_libBecRuntimePlugin_textureCtrlMetaField;
igMetaField *g_libBecRuntimePlugin_systemMetaField;
igMetaField *g_libBecRuntimePlugin_messengerMetaField;
igMetaField *g_libBecRuntimePlugin_fileListMetaField;
igMetaField *g_libBecRuntimePlugin_padManagerMetaField;
igMetaField *g_libBecRuntimePlugin_criMetaField;
igMetaField *g_libBecRuntimePlugin_luaInterfaceMetaField;
igMetaField *g_libBecRuntimePlugin_demoManagerMetaField;
igMetaField *g_libBecRuntimePlugin_timerMetaField;
igMetaField *g_libBecRuntimePlugin_memoryMetaField;

void *libBecRuntimePlugin_GetMetaObject(void) {
    if (g_libBecRuntimePlugin_metaObject == 0 || !isValid(g_libBecRuntimePlugin_metaObject)) {
        libBecRuntimePlugin_EnsureRegistered();
    }
    return g_libBecRuntimePlugin_metaObject;
}

int libBecRuntimePlugin_GetVTable(void) {
    BecRuntimePluginView plugin;
    return *(int *)((char *)&plugin + *(int *)((char *)g_objectSystem + 916));
}

igSmartPointer<igObject> *igSmartPointer_beParticleCtrl2_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beLua_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beMatCtrl_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beSelectCtrl_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beWaterPlain_Destruct(igSmartPointer<igObject> *self, long long delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beAction2_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beMeterCtrl_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beTargetObj_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beWeapon_Destruct(igSmartPointer<igObject> *self, long long delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beCameraCtrl_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_bePoint01_Destruct(igSmartPointer<igObject> *self, long long delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beBkColor_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beChangePosTransform_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beShadow01_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beGenerater_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beHitLandModel_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beHitLandDeliv_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beSound_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beSeCtl_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beActionStarter_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beLayerCtl_Destruct(igSmartPointer<igObject> *self, long long delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beFont_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beSwitchCtrl_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beLightCtrl_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beNumberCtrl_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beStaticInfoCtl_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beMovie_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beDBManager_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beSaveUtil_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beTextureCtrl_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beSystem_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beMessenger_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beFileListInfoManager_Destruct(igSmartPointer<igObject> *self, long long delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_bePadManager_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beCri_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_be_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beDemoManager_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beTimer_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beMemory_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *igSmartPointer_beMemory_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beTimer_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beDemoManager_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_be_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beCri_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_bePadManager_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beFileListInfoManager_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beMessenger_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beSystem_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beTextureCtrl_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beSaveUtil_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beDBManager_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beMovie_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beStaticInfoCtl_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNumberCtrl_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beLightCtrl_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beSwitchCtrl_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beFont_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beLayerCtl_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beActionStarter_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beSeCtl_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beSound_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beHitLandDeliv_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beHitLandModel_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beGenerater_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beShadow01_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beChangePosTransform_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beBkColor_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_bePoint01_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beCameraCtrl_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beWeapon_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beTargetObj_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beMeterCtrl_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beAction2_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beWaterPlain_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beSelectCtrl_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beMatCtrl_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beLua_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beParticleCtrl2_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igObject *igInsightPlugin_Construct(igObject *self) {
    igObject_InitHeader(self);
    self->_vtable = (int)&g_igInsightPlugin_vtable[0];
    return self;
}

void libBecRuntimePlugin_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(libBecRuntimePlugin_Register);
}

static igMetaObjectCallback g_libBecRuntimePlugin_callbackList[] = { beParticleCtrl2_EnsureRegistered, beLua_EnsureRegistered, beMatCtrl_EnsureRegistered, beSelectCtrl_EnsureRegistered, beWaterPlain_EnsureRegistered, beAction2_EnsureRegistered, beMeterCtrl_EnsureRegistered, beTargetObj_EnsureRegistered, beWeapon_EnsureRegistered, beCameraCtrl_EnsureRegistered, bePoint01_EnsureRegistered, beBkColor_EnsureRegistered, beChangePosTransform_EnsureRegistered, beShadow01_EnsureRegistered, beGenerater_EnsureRegistered, beHitLandModel_EnsureRegistered, beHitLandDeliv_EnsureRegistered, beSound_EnsureRegistered, beSeCtl_EnsureRegistered, beActionStarter_EnsureRegistered, beLayerCtl_EnsureRegistered, beFont_EnsureRegistered, beSwitchCtrl_EnsureRegistered, beLightCtrl_EnsureRegistered, beNumberCtrl_EnsureRegistered, beStaticInfoCtl_EnsureRegistered, beMovie_EnsureRegistered, beDBManager_EnsureRegistered, beSaveUtil_EnsureRegistered, beTextureCtrl_EnsureRegistered, beSystem_EnsureRegistered, beMessenger_EnsureRegistered, beFileListInfoManager_EnsureRegistered, bePadManager_EnsureRegistered, beCri_EnsureRegistered, be_EnsureRegistered, beDemoManager_EnsureRegistered, beTimer_EnsureRegistered, beMemory_EnsureRegistered, 0 };

CallbackArray *libBecRuntimePlugin_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_libBecRuntimePlugin_metaObject,
        igInsightPlugin_Register,
        igInsightPlugin_GetPublishedMetaObject,
        libBecRuntimePlugin_GetMetaObjectFunction,
        "libBecRuntimePlugin",
        0xa4, /* instance size */
        libBecRuntimePlugin_GetVTable,
        libBecRuntimePlugin_InitFields,
        0, /* extra callback item */
        g_libBecRuntimePlugin_callbackList /* callback list */
    );
}

void libBecRuntimePlugin_GetMetaObjectFunction(void)
{
    libBecRuntimePlugin_GetMetaObject();
}

static FieldFactory g_libBecRuntimePlugin_ctorTable[] = {
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
static const char *g_libBecRuntimePlugin_fieldTable[] = {
    "_particleCtrl2",
    "_luaManager",
    "_matCtrl",
    "_selectCtrl",
    "_waterPlain",
    "_action2",
    "_meterCtrl",
    "_targetObj",
    "_weapon",
    "_cameraCtrl",
    "_point01",
    "_bkColor",
    "_cpTransform",
    "_shadow01",
    "_generater",
    "_hitLandModel",
    "_hitLandDeliv",
    "_sound",
    "_seCtl",
    "_actionStarter",
    "_layerCtl",
    "_font",
    "_switchCtrl",
    "_lightCtrl",
    "_numberCtrl",
    "_staticInfoCtl",
    "_movie",
    "_dbManager",
    "_saveUtil",
    "_textureCtrl",
    "_system",
    "_messenger",
    "_fileList",
    "_padManager",
    "_cri",
    "_luaInterface",
    "_demoManager",
    "_timer",
    "_memory",
};
static igMetaField **g_libBecRuntimePlugin_fieldHandles[] = {
    &g_libBecRuntimePlugin_particleCtrl2MetaField,
    &g_libBecRuntimePlugin_luaManagerMetaField,
    &g_libBecRuntimePlugin_matCtrlMetaField,
    &g_libBecRuntimePlugin_selectCtrlMetaField,
    &g_libBecRuntimePlugin_waterPlainMetaField,
    &g_libBecRuntimePlugin_action2MetaField,
    &g_libBecRuntimePlugin_meterCtrlMetaField,
    &g_libBecRuntimePlugin_targetObjMetaField,
    &g_libBecRuntimePlugin_weaponMetaField,
    &g_libBecRuntimePlugin_cameraCtrlMetaField,
    &g_libBecRuntimePlugin_point01MetaField,
    &g_libBecRuntimePlugin_bkColorMetaField,
    &g_libBecRuntimePlugin_cpTransformMetaField,
    &g_libBecRuntimePlugin_shadow01MetaField,
    &g_libBecRuntimePlugin_generaterMetaField,
    &g_libBecRuntimePlugin_hitLandModelMetaField,
    &g_libBecRuntimePlugin_hitLandDelivMetaField,
    &g_libBecRuntimePlugin_soundMetaField,
    &g_libBecRuntimePlugin_seCtlMetaField,
    &g_libBecRuntimePlugin_actionStarterMetaField,
    &g_libBecRuntimePlugin_layerCtlMetaField,
    &g_libBecRuntimePlugin_fontMetaField,
    &g_libBecRuntimePlugin_switchCtrlMetaField,
    &g_libBecRuntimePlugin_lightCtrlMetaField,
    &g_libBecRuntimePlugin_numberCtrlMetaField,
    &g_libBecRuntimePlugin_staticInfoCtlMetaField,
    &g_libBecRuntimePlugin_movieMetaField,
    &g_libBecRuntimePlugin_dbManagerMetaField,
    &g_libBecRuntimePlugin_saveUtilMetaField,
    &g_libBecRuntimePlugin_textureCtrlMetaField,
    &g_libBecRuntimePlugin_systemMetaField,
    &g_libBecRuntimePlugin_messengerMetaField,
    &g_libBecRuntimePlugin_fileListMetaField,
    &g_libBecRuntimePlugin_padManagerMetaField,
    &g_libBecRuntimePlugin_criMetaField,
    &g_libBecRuntimePlugin_luaInterfaceMetaField,
    &g_libBecRuntimePlugin_demoManagerMetaField,
    &g_libBecRuntimePlugin_timerMetaField,
    &g_libBecRuntimePlugin_memoryMetaField,
};
static int g_libBecRuntimePlugin_fieldOffsets[] = {
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
    92,
    96,
    100,
    104,
    108,
    112,
    116,
    120,
    124,
    128,
    132,
    136,
    140,
    144,
    148,
    152,
    156,
    160,
};

void libBecRuntimePlugin_InitFields(void) {
    void *particleCtrl2;
    void *cameraCtrl;
    void *point01;
    void *bkColor;
    void *cpTransform;
    void *shadow01;
    void *generater;
    void *hitLandModel;
    void *hitLandDeliv;
    void *sound;
    void *seCtl;
    void *actionStarter;
    void *layerCtl;
    void *font;
    void *switchCtrl;
    void *lightCtrl;
    void *numberCtrl;
    void *staticInfoCtl;
    void *movie;
    void *dbManager;
    void *saveUtil;
    void *luaManager;
    void *textureCtrl;
    void *system;
    void *messenger;
    void *fileList;
    void *padManager;
    void *cri;
    void *luaInterface;
    void *demoManager;
    void *timer;
    void *memory;
    void *matCtrl;
    void *selectCtrl;
    void *waterPlain;
    void *action2;
    void *meterCtrl;
    void *targetObj;
    void *weapon;
    void *meta;
    int base;

    meta = (void *)g_libBecRuntimePlugin_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_libBecRuntimePlugin_ctorTable, 0x27);
    particleCtrl2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base));
    ((igObjectRefMetaField *)particleCtrl2)->_metaObject = (int)beParticleCtrl2_GetOrCreateMetaObject();
    luaManager = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1));
    ((igObjectRefMetaField *)luaManager)->_metaObject = (int)beLua_GetOrCreateMetaObject();
    matCtrl = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2));
    ((igObjectRefMetaField *)matCtrl)->_metaObject = (int)beMatCtrl_GetOrCreateMetaObject();
    selectCtrl = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3));
    ((igObjectRefMetaField *)selectCtrl)->_metaObject = (int)beSelectCtrl_GetOrCreateMetaObject();
    waterPlain = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4));
    ((igObjectRefMetaField *)waterPlain)->_metaObject = (int)beWaterPlain_GetOrCreateMetaObject();
    action2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5));
    ((igObjectRefMetaField *)action2)->_metaObject = (int)beAction2_GetOrCreateMetaObject();
    meterCtrl = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6));
    ((igObjectRefMetaField *)meterCtrl)->_metaObject = (int)beMeterCtrl_GetOrCreateMetaObject();
    targetObj = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7));
    ((igObjectRefMetaField *)targetObj)->_metaObject = (int)beTargetObj_GetOrCreateMetaObject();
    weapon = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 8));
    ((igObjectRefMetaField *)weapon)->_metaObject = (int)beWeapon_GetOrCreateMetaObject();
    cameraCtrl = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 9));
    ((igObjectRefMetaField *)cameraCtrl)->_metaObject = (int)beCameraCtrl_GetOrCreateMetaObject();
    point01 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xA));
    ((igObjectRefMetaField *)point01)->_metaObject = (int)bePoint01_GetOrCreateMetaObject();
    bkColor = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xB));
    ((igObjectRefMetaField *)bkColor)->_metaObject = (int)beBkColor_GetOrCreateMetaObject();
    cpTransform = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xC));
    ((igObjectRefMetaField *)cpTransform)->_metaObject = (int)beChangePosTransform_GetOrCreateMetaObject();
    shadow01 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xD));
    ((igObjectRefMetaField *)shadow01)->_metaObject = (int)beShadow01_GetOrCreateMetaObject();
    generater = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xE));
    ((igObjectRefMetaField *)generater)->_metaObject = (int)beGenerater_GetOrCreateMetaObject();
    hitLandModel = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xF));
    ((igObjectRefMetaField *)hitLandModel)->_metaObject = (int)beHitLandModel_GetOrCreateMetaObject();
    hitLandDeliv = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x10));
    ((igObjectRefMetaField *)hitLandDeliv)->_metaObject = (int)beHitLandDeliv_GetOrCreateMetaObject();
    sound = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x11));
    ((igObjectRefMetaField *)sound)->_metaObject = (int)beSound_GetOrCreateMetaObject();
    seCtl = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x12));
    ((igObjectRefMetaField *)seCtl)->_metaObject = (int)beSeCtl_GetOrCreateMetaObject();
    actionStarter = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x13));
    ((igObjectRefMetaField *)actionStarter)->_metaObject = (int)beActionStarter_GetOrCreateMetaObject();
    layerCtl = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x14));
    ((igObjectRefMetaField *)layerCtl)->_metaObject = (int)beLayerCtl_GetOrCreateMetaObject();
    font = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x15));
    ((igObjectRefMetaField *)font)->_metaObject = (int)beFont_GetOrCreateMetaObject();
    switchCtrl = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x16));
    ((igObjectRefMetaField *)switchCtrl)->_metaObject = (int)beSwitchCtrl_GetOrCreateMetaObject();
    lightCtrl = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x17));
    ((igObjectRefMetaField *)lightCtrl)->_metaObject = (int)beLightCtrl_GetOrCreateMetaObject();
    numberCtrl = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x18));
    ((igObjectRefMetaField *)numberCtrl)->_metaObject = (int)beNumberCtrl_GetOrCreateMetaObject();
    staticInfoCtl = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x19));
    ((igObjectRefMetaField *)staticInfoCtl)->_metaObject = (int)beStaticInfoCtl_GetOrCreateMetaObject();
    movie = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x1A));
    ((igObjectRefMetaField *)movie)->_metaObject = (int)beMovie_GetOrCreateMetaObject();
    dbManager = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x1B));
    ((igObjectRefMetaField *)dbManager)->_metaObject = (int)beDBManager_GetOrCreateMetaObject();
    saveUtil = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x1C));
    ((igObjectRefMetaField *)saveUtil)->_metaObject = (int)beSaveUtil_GetOrCreateMetaObject();
    textureCtrl = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x1D));
    ((igObjectRefMetaField *)textureCtrl)->_metaObject = (int)beTextureCtrl_GetOrCreateMetaObject();
    system = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x1E));
    ((igObjectRefMetaField *)system)->_metaObject = (int)beSystem_GetOrCreateMetaObject();
    messenger = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x1F));
    ((igObjectRefMetaField *)messenger)->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    fileList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x20));
    ((igObjectRefMetaField *)fileList)->_metaObject = (int)beFileListInfoManager_GetOrCreateMetaObject();
    padManager = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x21));
    ((igObjectRefMetaField *)padManager)->_metaObject = (int)bePadManager_GetOrCreateMetaObject();
    cri = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x22));
    ((igObjectRefMetaField *)cri)->_metaObject = (int)beCri_GetOrCreateMetaObject();
    luaInterface = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x23));
    ((igObjectRefMetaField *)luaInterface)->_metaObject = (int)be_GetOrCreateMetaObject();
    demoManager = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x24));
    ((igObjectRefMetaField *)demoManager)->_metaObject = (int)beDemoManager_GetOrCreateMetaObject();
    timer = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x25));
    ((igObjectRefMetaField *)timer)->_metaObject = (int)beTimer_GetOrCreateMetaObject();
    memory = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x26));
    ((igObjectRefMetaField *)memory)->_metaObject = (int)beMemory_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_libBecRuntimePlugin_fieldTable, g_libBecRuntimePlugin_fieldHandles, g_libBecRuntimePlugin_fieldOffsets, base);
}

