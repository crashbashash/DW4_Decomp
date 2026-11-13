igMetaObject *FUN_0045aaf0(void) {
    if (g_igViewerRenderer_metaObject[0] == 0) {
        g_igViewerRenderer_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igViewerRenderer_metaObject[0];
}

igMetaObject *igViewerRenderer_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igViewerRenderer_metaObject[0] != 0) {
        ready = (g_igViewerRenderer_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_0045b0d0();
done:
    return g_igViewerRenderer_metaObject[0];
}

int igViewerRenderer_GetVTable(void) {
    union U_45aaf0 u;
    int r;
    FUN_0045b090(&u.b[0]);
    u.pv = &DAT_005423f0[0];
    FUN_00459e20((int *)&u.b[12]);
    FUN_00197300(&u.b[16]);
    FUN_0045b080((int *)&u.b[20]);
    FUN_0045b070((int *)&u.b[24]);
    FUN_0045b060((int *)&u.b[28]);
    FUN_0045b050((int *)&u.b[32]);
    FUN_0019ac30(&u.b[36]);
    FUN_0045b040((int *)&u.b[40]);
    FUN_0045b030((int *)&u.b[44]);
    FUN_0045b020((int *)&u.b[48]);
    FUN_0045b010((int *)&u.b[52]);
    FUN_0045b000((int *)&u.b[56]);
    FUN_0019c370(&u.b[60]);
    FUN_0045aff0((int *)&u.b[64]);
    FUN_0045afe0((int *)&u.b[72]);
    FUN_00197350(&u.b[76]);
    FUN_0045afe0((int *)&u.b[80]);
    FUN_00197350(&u.b[84]);
    FUN_0045afd0((int *)&u.b[88]);
    r = *(int *)&u.b[*(int *)((char *)(((void *)g_objectSystem[0])) + 916)];
    u.pv = &DAT_005423f0[0];
    FUN_0045af50((void **)&u.b[88], -1);
    FUN_00197160(&u.b[84], -1);
    FUN_001d9870(&u.b[80], -1);
    FUN_00197160(&u.b[76], -1);
    FUN_001d9870(&u.b[72], -1);
    FUN_0019d9e0(&u.b[64], -1);
    FUN_0019c1a0(&u.b[60], -1);
    FUN_00239280(&u.b[56], -1);
    FUN_001a7580(&u.b[52], -1);
    FUN_0045aed0((void **)&u.b[48], -1);
    FUN_001d97f0(&u.b[44], -1);
    FUN_00229460(&u.b[40], -1);
    FUN_00136370(&u.b[36], -1);
    FUN_00239200(&u.b[32], -1);
    FUN_0045ae50((struct R **)&u.b[28], -1);
    FUN_0045add0((ObjectRefWord *)&u.b[24], -1);
    FUN_001d3090(&u.b[20], -1);
    FUN_00197060(&u.b[16], -1);
    FUN_00459860((ObjectRefWord *)&u.b[12], -1);
    FUN_00230f70(&u.b[0], 0);
    return r;
}

/* Deleting destructor; the deletion flag is a signed short. */
ObjectRefWord *FUN_0045add0(ObjectRefWord *self,int delete_storage) {
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

struct R **FUN_0045ae50(struct R **arg0, short arg1) {
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

void **FUN_0045aed0(void **arg0, long long arg1) {
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

void **FUN_0045af50(void **arg0, int arg1) {
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

int *FUN_0045afd0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045afe0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045aff0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b000(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b010(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b020(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b030(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b040(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b050(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b060(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b070(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0045b080(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void *FUN_0045b090(void *arg0) {
    igObject_InitHeader();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_0052d060[0]);
    *(int *)((char *)(arg0) + 8) = 0;
    return arg0;
}

void FUN_0045b0d0(void)
{
    igMetaObject_RunStaticInit(igViewerRenderer_Register);
}

void igViewerRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igViewerRenderer_GetMetaObject,
        igViewerRenderer_className,
        0x5C, /* instance size */
        igViewerRenderer_GetVTable,
        &igViewerRenderer_InitFields,
        0, /* extra callback item */
        g_igViewerRenderer_callbackList /* callback list */
    );
}

void thunk_igViewerRenderer_GetMetaObject(void) {
    igViewerRenderer_GetMetaObject();
}

void igViewerRenderer_InitFields(void) {
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
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igViewerRenderer_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igViewerRenderer_ctorTable[0], 0x14);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_0045b420();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_001386d0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0013b2b0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_00133950();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00134940();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_00135e60();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_00136750();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_001361f0();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = FUN_001a5d70();
    ((igRefMetaField *)temp_s2_9)->_construct = 1;
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = FUN_0019c6a0();
    ((igRefMetaField *)temp_s2_10)->_construct = 1;
    temp_s2_11 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = FUN_00196190();
    ((igRefMetaField *)temp_s2_11)->_construct = 1;
    temp_s2_12 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = FUN_0019dbb0();
    ((igRefMetaField *)temp_s2_12)->_construct = 1;
    temp_s2_13 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC));
    ((igObjectRefMetaField *)temp_s2_13)->_metaObject = FUN_001365e0();
    ((igRefMetaField *)temp_s2_13)->_construct = 1;
    temp_s2_14 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xD));
    ((igObjectRefMetaField *)temp_s2_14)->_metaObject = FUN_00136040();
    ((igRefMetaField *)temp_s2_14)->_construct = 1;
    temp_s2_15 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xF));
    ((igObjectRefMetaField *)temp_s2_15)->_metaObject = FUN_001a38e0();
    ((igRefMetaField *)temp_s2_15)->_construct = 1;
    temp_s2_16 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x10));
    ((igObjectRefMetaField *)temp_s2_16)->_metaObject = FUN_00137fb0();
    temp_s2_17 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x11));
    ((igObjectRefMetaField *)temp_s2_17)->_metaObject = FUN_001a38e0();
    temp_s2_18 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x12));
    ((igObjectRefMetaField *)temp_s2_18)->_metaObject = FUN_00137fb0();
    temp_s2_19 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x13));
    ((igObjectRefMetaField *)temp_s2_19)->_metaObject = FUN_0014f770();
    igMetaObject_NameFields(temp_s0, &g_igViewerRenderer_fieldTable[0], &DAT_004d0f80[0], &DAT_004d0fd0[0], temp_s1);
}

