void *FUN_0033e830(void) {
    struct G *g = DAT_00587a20[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0033ea40();
    }
    return DAT_00587a20[0];
}

int beWeaponInfoRam_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *p;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00539e90[0];
    p = (S_ref *)&u.b[40];
    *(int *)p = 0;
    u.vt = (int)&DAT_00539e30[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00539e90[0];
    if (p != 0) {
        p = *(S_ref **)p;
        if (p != 0) {
            p->f4 = (int)((int) (p->f4 - 1));
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    return temp_s0;
}

void *FUN_0033e920(S *arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        arg0->vt = (int)(&DAT_00539e90[0]);
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
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *ObjectRef_Destruct_0033e9c0(ObjectRefWord *self,int delete_storage) {
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

void FUN_0033ea40(void)
{
    igMetaObject_RunStaticInit(beWeaponInfoRam_Register);
}

void *beWeaponInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWeaponInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beWeaponInfoRam_GetMetaObject,
        beWeaponInfoRam_className,
        0x2c, /* instance size */
        beWeaponInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beWeaponInfoRam_GetMetaObject(void)
{
    FUN_0033e830();
}

int FUN_0033eaf0(void) {
    return ((int *)DAT_00589d28)[0];
}

