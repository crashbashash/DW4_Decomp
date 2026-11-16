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
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beFontImage_vtable[0];
    igBitmapFont_Destroy((igBitmapFont *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_igCharMetricsList_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

igFont *igFont_Destroy(igFont *self, short delete_storage) {
    if (self != 0) {
        self->_vtable = (int)&g_igFont_vtable[0];
        igObjectRef_Release((igObject **)&self->_attrList);
        /* ~igNamedObject is inlined here with its own null check on `this` */
        if (self != 0) {
            self->_vtable = (int)&g_igNamedObject_vtable[0];
            igStringRef_Release((char **)&self->_name);
        }
        if (delete_storage > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

igBitmapFont *igBitmapFont_Destroy(igBitmapFont *self, short delete_storage) {
    if (self != 0) {
        self->_vtable = (int)&g_igBitmapFont_vtable[0];
        igObjectRef_Release((igObject **)&self->_textureBind);
        igObjectRef_Release((igObject **)&self->_charMetricsList);
        /* ~igFont and ~igNamedObject are inlined here with their own null checks on `this` */
        if (self != 0) {
            self->_vtable = (int)&g_igFont_vtable[0];
            igObjectRef_Release((igObject **)&self->_attrList);
            if (self != 0) {
                self->_vtable = (int)&g_igNamedObject_vtable[0];
                igStringRef_Release((char **)&self->_name);
            }
        }
        if (delete_storage > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

void beFontImage_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beFontImage_Register);
}

CallbackArray *beFontImage_Register(void) {
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

igMetaObject *igBitmapFont_GetPublishedMetaObject(void) {
    return g_igBitmapFont_metaObject;
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

