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

ObjectRefWord *FUN_0033cd20(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void **FUN_0033cda0(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_0033ce20(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

struct R **FUN_0033cea0(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_0033cf20(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_0033cfa0(void **arg0, int arg1) {
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

void **FUN_0033d020(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_0033d0a0(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void **FUN_0033d120(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

O *FUN_0033d1a0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

void **FUN_0033d220(void **arg0, long long arg1) {
    char *o;
    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_0033d2a0(void **arg0, short arg1) {
    S_temp_a0_33d2a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_33d2a0 *)(*arg0);
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

ObjectRefWord *FUN_0033d320(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void **FUN_0033d3a0(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_0033d420(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

struct R **FUN_0033d4a0(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_0033d520(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void **FUN_0033d5a0(void **arg0, int arg1) {
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

void **FUN_0033d620(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_0033d6a0(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void **FUN_0033d720(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

O *FUN_0033d7a0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

ObjectRefWord *FUN_0033d820(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void **FUN_0033d8a0(void **arg0, short arg1) {
    S_temp_a0_33d8a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_33d8a0 *)(*arg0);
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

ObjectRefWord *FUN_0033d920(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void **FUN_0033d9a0(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_0033da20(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

struct R **FUN_0033daa0(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_0033db20(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void **FUN_0033dba0(void **arg0, int arg1) {
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

void **FUN_0033dc20(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_0033dca0(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void **FUN_0033dd20(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

O *FUN_0033dda0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) __dl__FPv(arg0);
    }
    return arg0;
}

void **FUN_0033de20(void **arg0, short arg1) {
    S_temp_a0_33de20 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_33de20 *)(*arg0);
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

void **FUN_0033dea0(void **arg0, short arg1) {
    S_temp_a0_33dea0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_33dea0 *)(*arg0);
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

ObjectRefWord *FUN_0033df20(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void **FUN_0033dfa0(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_0033e020(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
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
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_11;
    void *temp_s2_12;
    void *temp_s2_13;
    void *temp_s2_14;
    void *temp_s2_15;
    void *temp_s2_16;
    void *temp_s2_17;
    void *temp_s2_18;
    void *temp_s2_19;
    void *temp_s2_20;
    void *temp_s2_21;
    void *temp_s2_22;
    void *temp_s2_23;
    void *temp_s2_24;
    void *temp_s2_25;
    void *temp_s2_26;
    void *temp_s2_27;
    void *temp_s2_28;
    void *temp_s2_29;
    void *temp_s2_2;
    void *temp_s2_30;
    void *temp_s2_31;
    void *temp_s2_32;
    void *temp_s2_33;
    void *temp_s2_34;
    void *temp_s2_35;
    void *temp_s2_36;
    void *temp_s2_37;
    void *temp_s2_38;
    void *temp_s2_39;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)g_libBecRuntimePlugin_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_libBecRuntimePlugin_ctorTable, 0x27);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)beParticleCtrl2_GetOrCreateMetaObject();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)beLua_GetOrCreateMetaObject();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)beMatCtrl_GetOrCreateMetaObject();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)beSelectCtrl_GetOrCreateMetaObject();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)beWaterPlain_GetOrCreateMetaObject();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)beAction2_GetOrCreateMetaObject();
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)beMeterCtrl_GetOrCreateMetaObject();
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = (int)beTargetObj_GetOrCreateMetaObject();
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = (int)beWeapon_GetOrCreateMetaObject();
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = (int)beCameraCtrl_GetOrCreateMetaObject();
    temp_s2_11 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = (int)bePoint01_GetOrCreateMetaObject();
    temp_s2_12 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = (int)beBkColor_GetOrCreateMetaObject();
    temp_s2_13 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xC));
    ((igObjectRefMetaField *)temp_s2_13)->_metaObject = (int)beChangePosTransform_GetOrCreateMetaObject();
    temp_s2_14 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xD));
    ((igObjectRefMetaField *)temp_s2_14)->_metaObject = (int)beShadow01_GetOrCreateMetaObject();
    temp_s2_15 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xE));
    ((igObjectRefMetaField *)temp_s2_15)->_metaObject = (int)beGenerater_GetOrCreateMetaObject();
    temp_s2_16 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xF));
    ((igObjectRefMetaField *)temp_s2_16)->_metaObject = (int)beHitLandModel_GetOrCreateMetaObject();
    temp_s2_17 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x10));
    ((igObjectRefMetaField *)temp_s2_17)->_metaObject = (int)beHitLandDeliv_GetOrCreateMetaObject();
    temp_s2_18 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x11));
    ((igObjectRefMetaField *)temp_s2_18)->_metaObject = (int)beSound_GetOrCreateMetaObject();
    temp_s2_19 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x12));
    ((igObjectRefMetaField *)temp_s2_19)->_metaObject = (int)beSeCtl_GetOrCreateMetaObject();
    temp_s2_20 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x13));
    ((igObjectRefMetaField *)temp_s2_20)->_metaObject = (int)beActionStarter_GetOrCreateMetaObject();
    temp_s2_21 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x14));
    ((igObjectRefMetaField *)temp_s2_21)->_metaObject = (int)beLayerCtl_GetOrCreateMetaObject();
    temp_s2_22 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x15));
    ((igObjectRefMetaField *)temp_s2_22)->_metaObject = (int)beFont_GetOrCreateMetaObject();
    temp_s2_23 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x16));
    ((igObjectRefMetaField *)temp_s2_23)->_metaObject = (int)beSwitchCtrl_GetOrCreateMetaObject();
    temp_s2_24 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x17));
    ((igObjectRefMetaField *)temp_s2_24)->_metaObject = (int)beLightCtrl_GetOrCreateMetaObject();
    temp_s2_25 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x18));
    ((igObjectRefMetaField *)temp_s2_25)->_metaObject = (int)beNumberCtrl_GetOrCreateMetaObject();
    temp_s2_26 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x19));
    ((igObjectRefMetaField *)temp_s2_26)->_metaObject = (int)beStaticInfoCtl_GetOrCreateMetaObject();
    temp_s2_27 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x1A));
    ((igObjectRefMetaField *)temp_s2_27)->_metaObject = (int)beMovie_GetOrCreateMetaObject();
    temp_s2_28 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x1B));
    ((igObjectRefMetaField *)temp_s2_28)->_metaObject = (int)beDBManager_GetOrCreateMetaObject();
    temp_s2_29 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x1C));
    ((igObjectRefMetaField *)temp_s2_29)->_metaObject = (int)beSaveUtil_GetOrCreateMetaObject();
    temp_s2_30 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x1D));
    ((igObjectRefMetaField *)temp_s2_30)->_metaObject = (int)beTextureCtrl_GetOrCreateMetaObject();
    temp_s2_31 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x1E));
    ((igObjectRefMetaField *)temp_s2_31)->_metaObject = (int)beSystem_GetOrCreateMetaObject();
    temp_s2_32 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x1F));
    ((igObjectRefMetaField *)temp_s2_32)->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    temp_s2_33 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x20));
    ((igObjectRefMetaField *)temp_s2_33)->_metaObject = (int)beFileListInfoManager_GetOrCreateMetaObject();
    temp_s2_34 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x21));
    ((igObjectRefMetaField *)temp_s2_34)->_metaObject = (int)bePadManager_GetOrCreateMetaObject();
    temp_s2_35 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x22));
    ((igObjectRefMetaField *)temp_s2_35)->_metaObject = (int)beCri_GetOrCreateMetaObject();
    temp_s2_36 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x23));
    ((igObjectRefMetaField *)temp_s2_36)->_metaObject = (int)be_GetOrCreateMetaObject();
    temp_s2_37 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x24));
    ((igObjectRefMetaField *)temp_s2_37)->_metaObject = (int)beDemoManager_GetOrCreateMetaObject();
    temp_s2_38 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x25));
    ((igObjectRefMetaField *)temp_s2_38)->_metaObject = (int)beTimer_GetOrCreateMetaObject();
    temp_s2_39 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x26));
    ((igObjectRefMetaField *)temp_s2_39)->_metaObject = (int)beMemory_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s1, g_libBecRuntimePlugin_fieldTable, g_libBecRuntimePlugin_fieldHandles, g_libBecRuntimePlugin_fieldOffsets, temp_s0);
}

