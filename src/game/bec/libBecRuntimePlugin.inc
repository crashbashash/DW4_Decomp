void *FUN_0033c900(void) {
    unsigned char b;
    if (g_libBecRuntimePlugin_metaObject[0] != 0) {
        b = (*(int *)((char *)(g_libBecRuntimePlugin_metaObject[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_0033e350();
done:
    return g_libBecRuntimePlugin_metaObject[0];
}

ObjectRefWord *FUN_0033cd20(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
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
            FUN_00100610(arg0);
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
        if((short)delete_storage>0) FUN_00100610(self);
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
            FUN_00100610(arg0);
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
            FUN_00100610(arg0);
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
            FUN_00100610(arg0);
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
            FUN_00100610(arg0);
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
        if (flag > 0) FUN_00100610(self);
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
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

O *FUN_0033d1a0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
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
            FUN_00100610(arg0);
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
            FUN_00100610(arg0);
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
        if((short)delete_storage>0) FUN_00100610(self);
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
            FUN_00100610(arg0);
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
        if((short)delete_storage>0) FUN_00100610(self);
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
            FUN_00100610(arg0);
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
        if((short)delete_storage>0) FUN_00100610(self);
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
            FUN_00100610(arg0);
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
            FUN_00100610(arg0);
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
        if (flag > 0) FUN_00100610(self);
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
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

O *FUN_0033d7a0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
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
        if((short)delete_storage>0) FUN_00100610(self);
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
            FUN_00100610(arg0);
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
        if((short)delete_storage>0) FUN_00100610(self);
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
            FUN_00100610(arg0);
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
        if((short)delete_storage>0) FUN_00100610(self);
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
            FUN_00100610(arg0);
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
        if((short)delete_storage>0) FUN_00100610(self);
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
            FUN_00100610(arg0);
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
            FUN_00100610(arg0);
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
        if (flag > 0) FUN_00100610(self);
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
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

O *FUN_0033dda0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
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
            FUN_00100610(arg0);
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
            FUN_00100610(arg0);
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
        if((short)delete_storage>0) FUN_00100610(self);
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
            FUN_00100610(arg0);
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
        if((short)delete_storage>0) FUN_00100610(self);
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
    *arg0 = &DAT_005338a0[0];
    return arg0;
}

void FUN_0033e350(void)
{
    igMetaObject_RunStaticInit(libBecRuntimePlugin_Register);
}

void *libBecRuntimePlugin_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_libBecRuntimePlugin_metaObject,
        igInsightPlugin_Register,
        igInsightPlugin_GetPublishedMetaObject,
        libBecRuntimePlugin_GetMetaObject,
        libBecRuntimePlugin_className,
        0xa4, /* instance size */
        libBecRuntimePlugin_GetVTable,
        libBecRuntimePlugin_InitFields,
        0, /* extra callback item */
        g_libBecRuntimePlugin_callbackList /* callback list */
    );
}

void libBecRuntimePlugin_GetMetaObject(void)
{
    FUN_0033c900();
}

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

    temp_s1 = (void *)g_libBecRuntimePlugin_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c2d00[0], 0x27);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_0034c670();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_0035b770();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_0035a750();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_00345a40();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_00340d00();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)FUN_0036dd70();
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)FUN_003576a0();
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = (int)FUN_003429b0();
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = (int)FUN_0033f450();
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = (int)FUN_00369860();
    temp_s2_11 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = (int)FUN_0034ba20();
    temp_s2_12 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = (int)FUN_00369e00();
    temp_s2_13 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xC));
    ((igObjectRefMetaField *)temp_s2_13)->_metaObject = (int)FUN_00368750();
    temp_s2_14 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xD));
    ((igObjectRefMetaField *)temp_s2_14)->_metaObject = (int)FUN_00344e80();
    temp_s2_15 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xE));
    ((igObjectRefMetaField *)temp_s2_15)->_metaObject = (int)FUN_00360bb0();
    temp_s2_16 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xF));
    ((igObjectRefMetaField *)temp_s2_16)->_metaObject = (int)FUN_0035d7c0();
    temp_s2_17 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x10));
    ((igObjectRefMetaField *)temp_s2_17)->_metaObject = (int)FUN_0035ebd0();
    temp_s2_18 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x11));
    ((igObjectRefMetaField *)temp_s2_18)->_metaObject = (int)FUN_003442f0();
    temp_s2_19 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x12));
    ((igObjectRefMetaField *)temp_s2_19)->_metaObject = (int)FUN_00346530();
    temp_s2_20 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x13));
    ((igObjectRefMetaField *)temp_s2_20)->_metaObject = (int)FUN_0036c070();
    temp_s2_21 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x14));
    ((igObjectRefMetaField *)temp_s2_21)->_metaObject = (int)FUN_0035cae0();
    temp_s2_22 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x15));
    ((igObjectRefMetaField *)temp_s2_22)->_metaObject = (int)FUN_00361e90();
    temp_s2_23 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x16));
    ((igObjectRefMetaField *)temp_s2_23)->_metaObject = (int)FUN_003434d0();
    temp_s2_24 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x17));
    ((igObjectRefMetaField *)temp_s2_24)->_metaObject = (int)FUN_0035c050();
    temp_s2_25 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x18));
    ((igObjectRefMetaField *)temp_s2_25)->_metaObject = (int)FUN_0034e3a0();
    temp_s2_26 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x19));
    ((igObjectRefMetaField *)temp_s2_26)->_metaObject = (int)FUN_003437a0();
    temp_s2_27 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x1A));
    ((igObjectRefMetaField *)temp_s2_27)->_metaObject = (int)FUN_0034ef70();
    temp_s2_28 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x1B));
    ((igObjectRefMetaField *)temp_s2_28)->_metaObject = (int)FUN_00366110();
    temp_s2_29 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x1C));
    ((igObjectRefMetaField *)temp_s2_29)->_metaObject = (int)FUN_00346cc0();
    temp_s2_30 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x1D));
    ((igObjectRefMetaField *)temp_s2_30)->_metaObject = (int)FUN_00342350();
    temp_s2_31 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x1E));
    ((igObjectRefMetaField *)temp_s2_31)->_metaObject = (int)FUN_00342ce0();
    temp_s2_32 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x1F));
    ((igObjectRefMetaField *)temp_s2_32)->_metaObject = (int)FUN_00357910();
    temp_s2_33 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x20));
    ((igObjectRefMetaField *)temp_s2_33)->_metaObject = (int)FUN_00362830();
    temp_s2_34 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x21));
    ((igObjectRefMetaField *)temp_s2_34)->_metaObject = (int)FUN_0034c8e0();
    temp_s2_35 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x22));
    ((igObjectRefMetaField *)temp_s2_35)->_metaObject = (int)FUN_003678a0();
    temp_s2_36 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x23));
    ((igObjectRefMetaField *)temp_s2_36)->_metaObject = (int)FUN_0036dfe0();
    temp_s2_37 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x24));
    ((igObjectRefMetaField *)temp_s2_37)->_metaObject = (int)FUN_00363250();
    temp_s2_38 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x25));
    ((igObjectRefMetaField *)temp_s2_38)->_metaObject = (int)FUN_00341380();
    temp_s2_39 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x26));
    ((igObjectRefMetaField *)temp_s2_39)->_metaObject = (int)FUN_003591e0();
    igMetaObject_NameFields(temp_s1, &DAT_004c2da0[0], &DAT_004c2e40[0], &DAT_004c2ee0[0], temp_s0);
}

