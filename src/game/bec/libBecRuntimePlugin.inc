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
    unsigned char b;
    if (g_libBecRuntimePlugin_metaObject != 0) {
        b = (*(int *)((char *)(g_libBecRuntimePlugin_metaObject) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    libBecRuntimePlugin_EnsureRegistered();
done:
    return g_libBecRuntimePlugin_metaObject;
}

int libBecRuntimePlugin_GetVTable(void) {
    BecRuntimePluginView plugin;
    return *(int *)((char *)&plugin + *(int *)((char *)g_objectSystem[0] + 916));
}

igSmartPointer<igObject> *FUN_0033cd20(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *FUN_0033cda0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033ce20(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *FUN_0033cea0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033cf20(igSmartPointer<igObject> *self, long long delete_storage) {
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

igSmartPointer<igObject> *FUN_0033cfa0(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *FUN_0033d020(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033d0a0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033d120(igSmartPointer<igObject> *self, long long delete_storage) {
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

igSmartPointer<igObject> *FUN_0033d1a0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033d220(igSmartPointer<igObject> *self, long long delete_storage) {
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

igSmartPointer<igObject> *FUN_0033d2a0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033d320(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *FUN_0033d3a0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033d420(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *FUN_0033d4a0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033d520(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *FUN_0033d5a0(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *FUN_0033d620(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033d6a0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033d720(igSmartPointer<igObject> *self, long long delete_storage) {
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

igSmartPointer<igObject> *FUN_0033d7a0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033d820(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *FUN_0033d8a0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033d920(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *FUN_0033d9a0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033da20(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *FUN_0033daa0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033db20(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *FUN_0033dba0(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *FUN_0033dc20(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033dca0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033dd20(igSmartPointer<igObject> *self, long long delete_storage) {
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

igSmartPointer<igObject> *FUN_0033dda0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033de20(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033dea0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033df20(igSmartPointer<igObject> *self, int delete_storage) {
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

igSmartPointer<igObject> *FUN_0033dfa0(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *FUN_0033e020(igSmartPointer<igObject> *self, int delete_storage) {
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

int *FUN_0033e0a0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e0b0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e0c0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e0d0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e0e0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e0f0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e100(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e110(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e120(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e130(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e140(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e150(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e160(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e170(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e180(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e190(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e1a0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e1b0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e1c0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e1d0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e1e0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e1f0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e200(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e210(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e220(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e230(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e240(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e250(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e260(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e270(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e280(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e290(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e2a0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e2b0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e2c0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e2d0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e2e0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e2f0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0033e300(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int **FUN_0033e310(int **arg0) {
    igObject_InitHeader();
    *arg0 = &g_igInsightPlugin_vtable[0];
    return arg0;
}

void libBecRuntimePlugin_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(libBecRuntimePlugin_Register);
}

static igMetaObjectCallback g_libBecRuntimePlugin_callbackList[] = { beParticleCtrl2_EnsureRegistered, beLua_EnsureRegistered, beMatCtrl_EnsureRegistered, beSelectCtrl_EnsureRegistered, beWaterPlain_EnsureRegistered, beAction2_EnsureRegistered, beMeterCtrl_EnsureRegistered, beTargetObj_EnsureRegistered, beWeapon_EnsureRegistered, beCameraCtrl_EnsureRegistered, bePoint01_EnsureRegistered, beBkColor_EnsureRegistered, beChangePosTransform_EnsureRegistered, beShadow01_EnsureRegistered, beGenerater_EnsureRegistered, beHitLandModel_EnsureRegistered, beHitLandDeliv_EnsureRegistered, beSound_EnsureRegistered, beSeCtl_EnsureRegistered, beActionStarter_EnsureRegistered, beLayerCtl_EnsureRegistered, beFont_EnsureRegistered, beSwitchCtrl_EnsureRegistered, beLightCtrl_EnsureRegistered, beNumberCtrl_EnsureRegistered, beStaticInfoCtl_EnsureRegistered, beMovie_EnsureRegistered, beDBManager_EnsureRegistered, beSaveUtil_EnsureRegistered, beTextureCtrl_EnsureRegistered, beSystem_EnsureRegistered, beMessenger_EnsureRegistered, beFileListInfoManager_EnsureRegistered, bePadManager_EnsureRegistered, beCri_EnsureRegistered, be_EnsureRegistered, beDemoManager_EnsureRegistered, beTimer_EnsureRegistered, beMemory_EnsureRegistered, 0 };

void *libBecRuntimePlugin_Register(void) {
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
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_libBecRuntimePlugin_ctorTable, 0x27);
    particleCtrl2 = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)particleCtrl2)->_metaObject = (int)beParticleCtrl2_GetOrCreateMetaObject();
    luaManager = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)luaManager)->_metaObject = (int)beLua_GetOrCreateMetaObject();
    matCtrl = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)matCtrl)->_metaObject = (int)beMatCtrl_GetOrCreateMetaObject();
    selectCtrl = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)selectCtrl)->_metaObject = (int)beSelectCtrl_GetOrCreateMetaObject();
    waterPlain = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)waterPlain)->_metaObject = (int)beWaterPlain_GetOrCreateMetaObject();
    action2 = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)action2)->_metaObject = (int)beAction2_GetOrCreateMetaObject();
    meterCtrl = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((igObjectRefMetaField *)meterCtrl)->_metaObject = (int)beMeterCtrl_GetOrCreateMetaObject();
    targetObj = (void *)(igMetaObject_GetFieldAt(meta, base + 7));
    ((igObjectRefMetaField *)targetObj)->_metaObject = (int)beTargetObj_GetOrCreateMetaObject();
    weapon = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)weapon)->_metaObject = (int)beWeapon_GetOrCreateMetaObject();
    cameraCtrl = (void *)(igMetaObject_GetFieldAt(meta, base + 9));
    ((igObjectRefMetaField *)cameraCtrl)->_metaObject = (int)beCameraCtrl_GetOrCreateMetaObject();
    point01 = (void *)(igMetaObject_GetFieldAt(meta, base + 0xA));
    ((igObjectRefMetaField *)point01)->_metaObject = (int)bePoint01_GetOrCreateMetaObject();
    bkColor = (void *)(igMetaObject_GetFieldAt(meta, base + 0xB));
    ((igObjectRefMetaField *)bkColor)->_metaObject = (int)beBkColor_GetOrCreateMetaObject();
    cpTransform = (void *)(igMetaObject_GetFieldAt(meta, base + 0xC));
    ((igObjectRefMetaField *)cpTransform)->_metaObject = (int)beChangePosTransform_GetOrCreateMetaObject();
    shadow01 = (void *)(igMetaObject_GetFieldAt(meta, base + 0xD));
    ((igObjectRefMetaField *)shadow01)->_metaObject = (int)beShadow01_GetOrCreateMetaObject();
    generater = (void *)(igMetaObject_GetFieldAt(meta, base + 0xE));
    ((igObjectRefMetaField *)generater)->_metaObject = (int)beGenerater_GetOrCreateMetaObject();
    hitLandModel = (void *)(igMetaObject_GetFieldAt(meta, base + 0xF));
    ((igObjectRefMetaField *)hitLandModel)->_metaObject = (int)beHitLandModel_GetOrCreateMetaObject();
    hitLandDeliv = (void *)(igMetaObject_GetFieldAt(meta, base + 0x10));
    ((igObjectRefMetaField *)hitLandDeliv)->_metaObject = (int)beHitLandDeliv_GetOrCreateMetaObject();
    sound = (void *)(igMetaObject_GetFieldAt(meta, base + 0x11));
    ((igObjectRefMetaField *)sound)->_metaObject = (int)beSound_GetOrCreateMetaObject();
    seCtl = (void *)(igMetaObject_GetFieldAt(meta, base + 0x12));
    ((igObjectRefMetaField *)seCtl)->_metaObject = (int)beSeCtl_GetOrCreateMetaObject();
    actionStarter = (void *)(igMetaObject_GetFieldAt(meta, base + 0x13));
    ((igObjectRefMetaField *)actionStarter)->_metaObject = (int)beActionStarter_GetOrCreateMetaObject();
    layerCtl = (void *)(igMetaObject_GetFieldAt(meta, base + 0x14));
    ((igObjectRefMetaField *)layerCtl)->_metaObject = (int)beLayerCtl_GetOrCreateMetaObject();
    font = (void *)(igMetaObject_GetFieldAt(meta, base + 0x15));
    ((igObjectRefMetaField *)font)->_metaObject = (int)beFont_GetOrCreateMetaObject();
    switchCtrl = (void *)(igMetaObject_GetFieldAt(meta, base + 0x16));
    ((igObjectRefMetaField *)switchCtrl)->_metaObject = (int)beSwitchCtrl_GetOrCreateMetaObject();
    lightCtrl = (void *)(igMetaObject_GetFieldAt(meta, base + 0x17));
    ((igObjectRefMetaField *)lightCtrl)->_metaObject = (int)beLightCtrl_GetOrCreateMetaObject();
    numberCtrl = (void *)(igMetaObject_GetFieldAt(meta, base + 0x18));
    ((igObjectRefMetaField *)numberCtrl)->_metaObject = (int)beNumberCtrl_GetOrCreateMetaObject();
    staticInfoCtl = (void *)(igMetaObject_GetFieldAt(meta, base + 0x19));
    ((igObjectRefMetaField *)staticInfoCtl)->_metaObject = (int)beStaticInfoCtl_GetOrCreateMetaObject();
    movie = (void *)(igMetaObject_GetFieldAt(meta, base + 0x1A));
    ((igObjectRefMetaField *)movie)->_metaObject = (int)beMovie_GetOrCreateMetaObject();
    dbManager = (void *)(igMetaObject_GetFieldAt(meta, base + 0x1B));
    ((igObjectRefMetaField *)dbManager)->_metaObject = (int)beDBManager_GetOrCreateMetaObject();
    saveUtil = (void *)(igMetaObject_GetFieldAt(meta, base + 0x1C));
    ((igObjectRefMetaField *)saveUtil)->_metaObject = (int)beSaveUtil_GetOrCreateMetaObject();
    textureCtrl = (void *)(igMetaObject_GetFieldAt(meta, base + 0x1D));
    ((igObjectRefMetaField *)textureCtrl)->_metaObject = (int)beTextureCtrl_GetOrCreateMetaObject();
    system = (void *)(igMetaObject_GetFieldAt(meta, base + 0x1E));
    ((igObjectRefMetaField *)system)->_metaObject = (int)beSystem_GetOrCreateMetaObject();
    messenger = (void *)(igMetaObject_GetFieldAt(meta, base + 0x1F));
    ((igObjectRefMetaField *)messenger)->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    fileList = (void *)(igMetaObject_GetFieldAt(meta, base + 0x20));
    ((igObjectRefMetaField *)fileList)->_metaObject = (int)beFileListInfoManager_GetOrCreateMetaObject();
    padManager = (void *)(igMetaObject_GetFieldAt(meta, base + 0x21));
    ((igObjectRefMetaField *)padManager)->_metaObject = (int)bePadManager_GetOrCreateMetaObject();
    cri = (void *)(igMetaObject_GetFieldAt(meta, base + 0x22));
    ((igObjectRefMetaField *)cri)->_metaObject = (int)beCri_GetOrCreateMetaObject();
    luaInterface = (void *)(igMetaObject_GetFieldAt(meta, base + 0x23));
    ((igObjectRefMetaField *)luaInterface)->_metaObject = (int)be_GetOrCreateMetaObject();
    demoManager = (void *)(igMetaObject_GetFieldAt(meta, base + 0x24));
    ((igObjectRefMetaField *)demoManager)->_metaObject = (int)beDemoManager_GetOrCreateMetaObject();
    timer = (void *)(igMetaObject_GetFieldAt(meta, base + 0x25));
    ((igObjectRefMetaField *)timer)->_metaObject = (int)beTimer_GetOrCreateMetaObject();
    memory = (void *)(igMetaObject_GetFieldAt(meta, base + 0x26));
    ((igObjectRefMetaField *)memory)->_metaObject = (int)beMemory_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_libBecRuntimePlugin_fieldTable, g_libBecRuntimePlugin_fieldHandles, g_libBecRuntimePlugin_fieldOffsets, base);
}

