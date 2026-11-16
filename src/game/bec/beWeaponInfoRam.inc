igMetaObject *g_beWeaponInfoRam_metaObject;

void *beWeaponInfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beWeaponInfoRam_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beWeaponInfoRam_EnsureRegistered();
    }
    return g_beWeaponInfoRam_metaObject;
}

int beWeaponInfoRam_GetVTable(void) {
    union U u;
    int temp_s0;
    igObject *p;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_beBaseInfoRam_vtable[0];
    p = (igObject *)&u.b[40];
    *(int *)p = 0;
    u.vt = (int)&g_beWeaponInfoRam_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beBaseInfoRam_vtable[0];
    if (p != 0) {
        p = *(igObject **)p;
        if (p != 0) {
            p->_refCount = (int)p->_refCount - 1;
            if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    return temp_s0;
}

void *FUN_0033e920(S *arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        arg0->vt = (int)(&g_beBaseInfoRam_vtable[0]);
        if (((char *)arg0 + 0x28) != 0) {
            o = arg0->m;
            if (o != 0) {
                *(int *)(o + 4) = *(int *)(o + 4) - 1;
                if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                    igObject_Destroy(o);
                }
            }
        }
        if ((short)arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

igSmartPointer<igObject> *ObjectRef_Destruct_0033e9c0(igSmartPointer<igObject> *self, int delete_storage) {
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

void beWeaponInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beWeaponInfoRam_Register);
}

void *beWeaponInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWeaponInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beWeaponInfoRam_GetMetaObjectFunction,
        "beWeaponInfoRam",
        0x2c, /* instance size */
        beWeaponInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beWeaponInfoRam_GetMetaObjectFunction(void)
{
    beWeaponInfoRam_GetMetaObject();
}

igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void) {
    return g_beBaseInfoRam_metaObject;
}

