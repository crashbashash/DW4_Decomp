S *FUN_003b0a30(void) {
    S *g = DAT_0058a8f8[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_003b18b0();
done:
    return DAT_0058a8f8[0];
}

void **FUN_003b0ce0(struct Ref **self, short flag) {
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

void **FUN_003b0d60(void **arg0, long long arg1) {
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

O *FUN_003b0de0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

ObjectRefWord *FUN_003b0e60(ObjectRefWord *self,int delete_storage) {
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

void **FUN_003b0ee0(void **arg0, short arg1) {
    S_temp_a0_3b0ee0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_3b0ee0 *)(*arg0);
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

ObjectRefWord *FUN_003b0f60(ObjectRefWord *self,int delete_storage) {
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

void **FUN_003b0fe0(void **arg0, short arg1) {
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

ObjectRefWord *FUN_003b1060(ObjectRefWord *self,int delete_storage) {
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

struct R **FUN_003b10e0(struct R **arg0, short arg1) {
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

void **FUN_003b1160(void **arg0, long long arg1) {
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

void **FUN_003b11e0(void **arg0, int arg1) {
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

void **FUN_003b1260(void **arg0, short arg1) {
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

void **FUN_003b12e0(struct Ref **self, short flag) {
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

void **FUN_003b1360(void **arg0, long long arg1) {
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

O *FUN_003b13e0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

void **FUN_003b1460(void **arg0, long long arg1) {
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

void **FUN_003b14e0(void **arg0, short arg1) {
    S_temp_a0_3b14e0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_3b14e0 *)(*arg0);
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

ObjectRefWord *FUN_003b1560(ObjectRefWord *self,int delete_storage) {
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

void **FUN_003b15e0(void **arg0, short arg1) {
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

ObjectRefWord *FUN_003b1660(ObjectRefWord *self,int delete_storage) {
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

struct R **FUN_003b16e0(struct R **arg0, short arg1) {
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

int *FUN_003b1760(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b1770(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b1780(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b1790(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b17a0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b17b0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b17c0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b17d0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b17e0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b17f0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b1800(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b1810(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b1820(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b1830(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b1840(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b1850(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b1860(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b1870(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b1880(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b1890(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_003b18a0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void FUN_003b18b0(void)
{
    igMetaObject_RunStaticInit(libNdmwRuntimePlugin_Register);
}

void *libNdmwRuntimePlugin_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_libNdmwRuntimePlugin_metaObject,
        igInsightPlugin_Register,
        igInsightPlugin_GetPublishedMetaObject,
        libNdmwRuntimePlugin_GetMetaObject,
        libNdmwRuntimePlugin_className,
        0x5c, /* instance size */
        libNdmwRuntimePlugin_GetVTable,
        libNdmwRuntimePlugin_InitFields,
        0, /* extra callback item */
        g_libNdmwRuntimePlugin_callbackList /* callback list */
    );
}

void libNdmwRuntimePlugin_GetMetaObject(void)
{
    FUN_003b0a30();
}

void libNdmwRuntimePlugin_InitFields(void) {
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
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)((int *)DAT_0058a8f8)[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c9290[0], 0x15);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_003cae40();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_003bbde0();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_003beed0();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_003c2380();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_003b28e0();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_003c7de0();
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_003c4740();
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_003bd430();
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = FUN_003bccc0();
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = FUN_003c9ce0();
    temp_s2_11 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = FUN_003bb7d0();
    temp_s2_12 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = FUN_003bf8d0();
    temp_s2_13 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xC));
    ((igObjectRefMetaField *)temp_s2_13)->_metaObject = FUN_003bf1f0();
    temp_s2_14 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xD));
    ((igObjectRefMetaField *)temp_s2_14)->_metaObject = FUN_003c09a0();
    temp_s2_15 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xE));
    ((igObjectRefMetaField *)temp_s2_15)->_metaObject = FUN_003c1760();
    temp_s2_16 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xF));
    ((igObjectRefMetaField *)temp_s2_16)->_metaObject = FUN_003c1ce0();
    temp_s2_17 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x10));
    ((igObjectRefMetaField *)temp_s2_17)->_metaObject = FUN_003c0b90();
    temp_s2_18 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x11));
    ((igObjectRefMetaField *)temp_s2_18)->_metaObject = FUN_003c1160();
    temp_s2_19 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x12));
    ((igObjectRefMetaField *)temp_s2_19)->_metaObject = FUN_003c1af0();
    temp_s2_20 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x13));
    ((igObjectRefMetaField *)temp_s2_20)->_metaObject = FUN_003c0f70();
    temp_s2_21 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x14));
    ((igObjectRefMetaField *)temp_s2_21)->_metaObject = FUN_003c0d80();
    igMetaObject_NameFields(temp_s1, &DAT_004c92f0[0], &DAT_004c9350[0], &DAT_004c93b0[0], temp_s0);
}

