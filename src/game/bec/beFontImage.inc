igMetaObject *g_beFontImage_metaObject;

igMetaObject *beFontImage_GetMetaObject(void) {
    if (g_beFontImage_metaObject == 0 || !isValid(g_beFontImage_metaObject)) beFontImage_EnsureRegistered();
    return g_beFontImage_metaObject;
}

int beFontImage_GetVTable(void) {
    beFontImage obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._attrList = 0;
    obj._charMetricsList = 0;
    obj._textureBind = 0;
    obj._vtable = (int)&g_beFontImage_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beFontImage_vtable[0];
    igBitmapFont_Destroy((O_361b00 *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_FUN_00452790_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

O_361a20 *igFont_Destroy(O_361a20 *arg0, short arg1) {
    int *temp_a1;
    int temp_v0;
    R_361a20 *temp_a0;
    int *temp_v1;

    if (arg0 != 0) {
        arg0->vt = &g_igFont_vtable[0];
        if (&arg0->ref != 0) {
            temp_a0 = arg0->ref;
            if (temp_a0 != 0) {
                temp_a0->refs = temp_a0->refs - 1;
                if (((unsigned long long)((long long)temp_a0->refs << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0);
                }
            }
        }
        if (arg0 != 0) {
            arg0->vt = &g_igNamedObject_vtable[0];
            if (&arg0->str != 0) {
                temp_v1 = arg0->str;
                if (temp_v1 != 0) {
                    temp_a1 = temp_v1 - 2;
                    temp_v0 = temp_v1[-1] - 1;
                    temp_v1[-1] = temp_v0;
                    if (temp_v0 == 0) {
                        StringChunk_ReleaseHeader(*temp_a1, temp_a1);
                    }
                }
            }
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

O_361b00 *igBitmapFont_Destroy(O_361b00 *arg0, short arg1) {
    int *temp_a1;
    int temp_v0;
    R_361b00 *temp_a0;
    R_361b00 *temp_a0_2;
    R_361b00 *temp_a0_3;
    int *temp_v1;

    if (arg0 != 0) {
        arg0->vt = &g_igBitmapFont_vtable[0];
        if (&arg0->ref32 != 0) {
            temp_a0 = arg0->ref32;
            if (temp_a0 != 0) {
                temp_a0->refs = temp_a0->refs - 1;
                if (((unsigned long long)((long long)temp_a0->refs << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0);
                }
            }
        }
        if (&arg0->ref28 != 0) {
            temp_a0_2 = arg0->ref28;
            if (temp_a0_2 != 0) {
                temp_a0_2->refs = temp_a0_2->refs - 1;
                if (((unsigned long long)((long long)temp_a0_2->refs << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0_2);
                }
            }
        }
        if (arg0 != 0) {
            arg0->vt = &g_igFont_vtable[0];
            if (&arg0->ref20 != 0) {
                temp_a0_3 = arg0->ref20;
                if (temp_a0_3 != 0) {
                    temp_a0_3->refs = temp_a0_3->refs - 1;
                    if (((unsigned long long)((long long)temp_a0_3->refs << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(temp_a0_3);
                    }
                }
            }
            if (arg0 != 0) {
                arg0->vt = &g_igNamedObject_vtable[0];
                if (&arg0->str != 0) {
                    temp_v1 = arg0->str;
                    if (temp_v1 != 0) {
                        temp_a1 = temp_v1 - 2;
                        temp_v0 = temp_v1[-1] - 1;
                        temp_v1[-1] = temp_v0;
                        if (temp_v0 == 0) {
                            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
                        }
                    }
                }
            }
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

void beFontImage_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beFontImage_Register);
}

void *beFontImage_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beFontImage_metaObject,
        igBitmapFont_Register,
        igBitmapFont_GetPublishedMetaObject,
        beFontImage_GetMetaObjectFunction,
        "beFontImage",
        0x24, /* instance size */
        beFontImage_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beFontImage_GetMetaObjectFunction(void)
{
    beFontImage_GetMetaObject();
}

int igBitmapFont_GetPublishedMetaObject(void) {
    return g_igBitmapFont_metaObject[0];
}

igMetaEnum *g_beFontImage_alignMetaEnum;
static const char *g_beFontImage_alignNames[] = {
    "LEFT", "RIGHT", "CENTER",
};
static int g_beFontImage_alignValues[] = {
    0, 1, 2,
};

igMetaEnum *beFont_GetAlignEnum(void) {
    if (g_beFontImage_alignMetaEnum == 0) {
        g_beFontImage_alignMetaEnum = igMetaEnum_Create("Align", g_beFontImage_alignNames, g_beFontImage_alignValues, 3);
    }
    return g_beFontImage_alignMetaEnum;
}

igMetaEnum *g_beFontImage_swtCtlMetaEnum;
static const char *g_beFontImage_swtCtlNames[] = {
    "CLR", "SET", "DISPOFF", "DISPON",
};
static int g_beFontImage_swtCtlValues[] = {
    0, 1, 0, 1,
};

igMetaEnum *beFont_GetSwitchEnum(void) {
    if (g_beFontImage_swtCtlMetaEnum == 0) {
        g_beFontImage_swtCtlMetaEnum = igMetaEnum_Create("SwtCtl", g_beFontImage_swtCtlNames, g_beFontImage_swtCtlValues, 4);
    }
    return g_beFontImage_swtCtlMetaEnum;
}

igMetaEnum *g_beFontImage_messageMetaEnum;
static const char *g_beFontImage_messageNames[] = {
    "INITIALIZE", "TEXTSET", "ALIGN", "SWITCH",
    "SETPOSITION", "COLOR", "DEFAULTCOLOR", "CANCELCOLOR",
    "REPLACEUNKNOWN",
};
static int g_beFontImage_messageValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8,
};

igMetaEnum *beFont_GetMessageEnum(void) {
    if (g_beFontImage_messageMetaEnum == 0) {
        g_beFontImage_messageMetaEnum = igMetaEnum_Create("Message", g_beFontImage_messageNames, g_beFontImage_messageValues, 9);
    }
    return g_beFontImage_messageMetaEnum;
}

