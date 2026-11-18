static const char *g_igViewerSceneInfoManager_GUI_VISIBILITYNames[] = {
    "ALL_VISIBLE", "ONLY_STATS", "ALL_HIDDEN",
};
static int g_igViewerSceneInfoManager_GUI_VISIBILITYValues[] = {
    0, 1, 2,
};
igMetaEnum *g_igViewerSceneInfoManager_GUI_VISIBILITYMetaEnum;
igMetaObject *g_igViewerSceneInfoManager_metaObject;
igMetaField *g_igViewerSceneInfoManager_nameMetaField;
igMetaField *g_igViewerSceneInfoManager_applicationControllerMetaField;
igMetaField *g_igViewerSceneInfoManager_parametersMetaField;
igMetaField *g_igViewerSceneInfoManager_viewerRendererMetaField;
igMetaField *g_igViewerSceneInfoManager_bboxRendererMetaField;
igMetaField *g_igViewerSceneInfoManager_normalsRendererMetaField;
igMetaField *g_igViewerSceneInfoManager_flushRendererMetaField;
igMetaField *g_igViewerSceneInfoManager_clippingCheckFrameMetaField;
igMetaField *g_igViewerSceneInfoManager_guiMetaField;
igMetaField *g_igViewerSceneInfoManager_guiFactoryMetaField;
igMetaField *g_igViewerSceneInfoManager_rootComponentMetaField;
igMetaField *g_igViewerSceneInfoManager_menuHolderMetaField;
igMetaField *g_igViewerSceneInfoManager_operationBoxHolderMetaField;
igMetaField *g_igViewerSceneInfoManager_operationBoxMetaField;
igMetaField *g_igViewerSceneInfoManager_timeBoxHolderMetaField;
igMetaField *g_igViewerSceneInfoManager_timeBoxMetaField;
igMetaField *g_igViewerSceneInfoManager_menuBarMetaField;
igMetaField *g_igViewerSceneInfoManager_viewMenuMetaField;
igMetaField *g_igViewerSceneInfoManager_viewportMenuMetaField;
igMetaField *g_igViewerSceneInfoManager_cameraMenuMetaField;
igMetaField *g_igViewerSceneInfoManager_cameraMenuActiverMetaField;
igMetaField *g_igViewerSceneInfoManager_optionMenuMetaField;
igMetaField *g_igViewerSceneInfoManager_disableMenuMetaField;
igMetaField *g_igViewerSceneInfoManager_statMenuMetaField;
igMetaField *g_igViewerSceneInfoManager_timeMenuMetaField;
igMetaField *g_igViewerSceneInfoManager_alchemyMenuMetaField;
igMetaField *g_igViewerSceneInfoManager_timeStatisticMetaField;
igMetaField *g_igViewerSceneInfoManager_speedStatisticMetaField;
igMetaField *g_igViewerSceneInfoManager_nearPlaneStatisticMetaField;
igMetaField *g_igViewerSceneInfoManager_farPlaneStatisticMetaField;
igMetaField *g_igViewerSceneInfoManager_hotKeyReceiverMetaField;
igMetaField *g_igViewerSceneInfoManager_viewManagerMetaField;
igMetaField *g_igViewerSceneInfoManager_statManagerMetaField;
igMetaField *g_igViewerSceneInfoManager_disableComponentsMetaField;
igMetaField *g_igViewerSceneInfoManager_disableViewsMetaField;
igMetaField *g_igViewerSceneInfoManager_operationModeGroupMetaField;
igMetaField *g_igViewerSceneInfoManager_referencesMetaField;
igMetaField *g_igViewerSceneInfoManager_framesMetaField;
igMetaField *g_igViewerSceneInfoManager_lastStatTimeMetaField;
igMetaField *g_igViewerSceneInfoManager_guiVisibilityMetaField;
igMetaField *g_igViewerSceneInfoManager_textureListMetaField;
igMetaField *g_igViewerSceneInfoManager_modeChangeMetaField;
igMetaField *g_igViewerSceneInfoManager_isCapturingBudgetMetaField;
igMetaField *g_igViewerSceneInfoManager_hideAllStatisticsMenuItemMetaField;

igMetaEnum *FUN_004592e0(void) {
    if (g_igViewerSceneInfoManager_GUI_VISIBILITYMetaEnum == 0) {
        g_igViewerSceneInfoManager_GUI_VISIBILITYMetaEnum = igMetaEnum_Create("GUI_VISIBILITY", g_igViewerSceneInfoManager_GUI_VISIBILITYNames, g_igViewerSceneInfoManager_GUI_VISIBILITYValues, 3);
    }
    return g_igViewerSceneInfoManager_GUI_VISIBILITYMetaEnum;
}

igObject *igViewerSceneInfoManager_Create(igMemoryPoolView *pool) {
    igViewerSceneInfoManager_EnsureRegistered();
    return igMetaObject_CreateInstance(g_igViewerSceneInfoManager_metaObject, pool);
}

igMetaObject *igViewerSceneInfoManager_GetOrCreateMetaObject(void) {
    if (g_igViewerSceneInfoManager_metaObject == 0) {
        g_igViewerSceneInfoManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igViewerSceneInfoManager_metaObject;
}

void *igViewerSceneInfoManager_GetMetaObject(void) {
    bool ok;
    if (g_igViewerSceneInfoManager_metaObject == 0) goto make;
    ok = !!(((MetaObjectFlags *)g_igViewerSceneInfoManager_metaObject)->f & 4);
    if (ok != false) goto done;
make:
    igViewerSceneInfoManager_EnsureRegistered();
done:;
    return (void *)g_igViewerSceneInfoManager_metaObject;
}

int igViewerSceneInfoManager_GetVTable(void) {
    union U u;
    int r;
    char *p352;
    char *p344;
    char *p340;
    char *p316;
    char *p312;
    char *p308;
    char *p304;
    char *p300;
    char *p296;
    igInfoManager_Construct((igInfoManager *)u.b);
    u.vt = (int)&g_igViewerSceneInfoManager_vtable[0];
    FUN_00459e30((int *)&u.b[16]);
    FUN_00459e20((int *)&u.b[20]);
    FUN_00459e10((int *)&u.b[24]);
    FUN_00459e00((int *)&u.b[28]);
    FUN_00459df0((int *)&u.b[32]);
    FUN_00459de0((int *)&u.b[36]);
    FUN_00459dd0((int *)&u.b[44]);
    igSmartPointer_igViewerGuiFactory_Construct((int *)&u.b[48]);
    igSmartPointer_igBoxComponent_Construct((int *)&u.b[52]);
    igSmartPointer_igGuiComponent_Construct((int *)&u.b[56]);
    igSmartPointer_igGuiComponent_Construct((int *)&u.b[60]);
    igSmartPointer_igBoxComponent_Construct((int *)&u.b[64]);
    igSmartPointer_igGuiComponent_Construct((int *)&u.b[68]);
    igSmartPointer_igBoxComponent_Construct((int *)&u.b[72]);
    igSmartPointer_igBoxComponent_Construct((int *)&u.b[76]);
    igSmartPointer_igBoxComponent_Construct((int *)&u.b[80]);
    igSmartPointer_igBoxComponent_Construct((int *)&u.b[84]);
    igSmartPointer_igBoxComponent_Construct((int *)&u.b[88]);
    igSmartPointer_igGuiComponent_Construct((int *)&u.b[92]);
    igSmartPointer_igBoxComponent_Construct((int *)&u.b[96]);
    igSmartPointer_igBoxComponent_Construct((int *)&u.b[100]);
    igSmartPointer_igBoxComponent_Construct((int *)&u.b[104]);
    igSmartPointer_igBoxComponent_Construct((int *)&u.b[108]);
    igSmartPointer_igBoxComponent_Construct((int *)&u.b[112]);
    igSmartPointer_igStatisticsItem_Construct((int *)&u.b[116]);
    igSmartPointer_igStatisticsItem_Construct((int *)&u.b[120]);
    igSmartPointer_igStatisticsItem_Construct((int *)&u.b[124]);
    igSmartPointer_igStatisticsItem_Construct((int *)&u.b[128]);
    FUN_00459dc0((int *)&u.b[132]);
    p296 = &u.b[136];
    FUN_00459db0((int *)p296);
    p300 = &u.b[140];
    FUN_00459da0((int *)p300);
    p304 = &u.b[144];
    FUN_00459d90((int *)p304);
    p308 = &u.b[148];
    igSmartPointer_igObjectList_Construct((int *)p308);
    p312 = &u.b[152];
    FUN_00459d80((int *)p312);
    p316 = &u.b[156];
    igSmartPointer_igObjectList_Construct((int *)p316);
    p340 = &u.b[180];
    FUN_00459d70((int *)p340);
    p344 = &u.b[184];
    FUN_00459d60((int *)p344);
    p352 = &u.b[192];
    igSmartPointer_igGuiComponent_Construct((int *)p352);
    r = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    *(int **)u.b = &g_igViewerSceneInfoManager_vtable[0];
    igSmartPointer_igGuiComponent_Destruct((igSmartPointer<igObject> *)p352, -1);
    FUN_00459ce0((void **)p344, -1);
    igSmartPointer_igTextureList_Destruct((igSmartPointer<igObject> *)p340, -1);
    igSmartPointer_igObjectList_Destruct((igSmartPointer<igObject> *)p316, -1);
    igSmartPointer_igRadioGroup_Destruct((igSmartPointer<igObject> *)p312, -1);
    igSmartPointer_igObjectList_Destruct((igSmartPointer<igObject> *)p308, -1);
    FUN_0044c1c0((void **)p304, -1);
    FUN_00459c60((ObjectRefWord *)p300, -1);
    FUN_00459be0((void **)p296, -1);
    FUN_00459b60((ObjectRefWord *)&u.b[132], -1);
    igSmartPointer_igStatisticsItem_Destruct((igSmartPointer<igObject> *)&u.b[128], -1);
    igSmartPointer_igStatisticsItem_Destruct((igSmartPointer<igObject> *)&u.b[124], -1);
    igSmartPointer_igStatisticsItem_Destruct((igSmartPointer<igObject> *)&u.b[120], -1);
    igSmartPointer_igStatisticsItem_Destruct((igSmartPointer<igObject> *)&u.b[116], -1);
    GameMain_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&u.b[112], -1);
    GameMain_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&u.b[108], -1);
    GameMain_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&u.b[104], -1);
    GameMain_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&u.b[100], -1);
    GameMain_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&u.b[96], -1);
    igSmartPointer_igGuiComponent_Destruct((igSmartPointer<igObject> *)&u.b[92], -1);
    GameMain_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&u.b[88], -1);
    GameMain_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&u.b[84], -1);
    GameMain_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&u.b[80], -1);
    GameMain_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&u.b[76], -1);
    GameMain_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&u.b[72], -1);
    igSmartPointer_igGuiComponent_Destruct((igSmartPointer<igObject> *)&u.b[68], -1);
    GameMain_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&u.b[64], -1);
    igSmartPointer_igGuiComponent_Destruct((igSmartPointer<igObject> *)&u.b[60], -1);
    igSmartPointer_igGuiComponent_Destruct((igSmartPointer<igObject> *)&u.b[56], -1);
    GameMain_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&u.b[52], -1);
    igSmartPointer_igViewerGuiFactory_Destruct((igSmartPointer<igObject> *)&u.b[48], -1);
    FUN_00459ae0((O *)&u.b[44], -1);
    FUN_00459a60((void **)&u.b[36], -1);
    FUN_004599e0((struct Ref **)&u.b[32], -1);
    FUN_00459960((void **)&u.b[28], -1);
    FUN_004598e0((void **)&u.b[24], -1);
    FUN_00459860((ObjectRefWord *)&u.b[20], -1);
    FUN_004597e0((struct R **)&u.b[16], -1);
    igInfoManager_Destroy((igInfoManager *)u.b, 0);
    return r;
}

struct R **FUN_004597e0(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_00459860(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

void **FUN_004598e0(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void **FUN_00459960(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void **FUN_004599e0(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy((igObject *)p);
        }
        if (flag > 0) operator delete(self);
    }
    return (void **)self;
}

void **FUN_00459a60(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

O *FUN_00459ae0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
        if (arg1 > 0) operator delete(arg0);
    }
    return arg0;
}

ObjectRefWord *FUN_00459b60(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

void **FUN_00459be0(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_00459c60(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

void **FUN_00459ce0(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy((igObject *)r);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

int *FUN_00459d60(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459d70(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459d80(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459d90(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459da0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459db0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459dc0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459dd0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459de0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459df0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459e00(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459e10(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459e20(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_00459e30(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void igViewerSceneInfoManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igViewerSceneInfoManager_Register);
}

static igMetaObjectCallback g_igViewerSceneInfoManager_callbackList[] = { igViewerSceneInfoManagerController_EnsureRegistered, igViewerParameters_EnsureRegistered, igViewerRenderer_EnsureRegistered, igBoundingBoxRenderer_EnsureRegistered, igNormalsRenderer_EnsureRegistered, igFlushRenderer_EnsureRegistered, igGuiSystem_RunStaticInit, igViewerGuiFactory_EnsureRegistered, igBoxComponent_RunStaticInit, igGuiComponent_EnsureRegistered, igStatisticsItem_EnsureRegistered, igHotKeyEventReceiver_RunStaticInit, igViewManager_EnsureRegistered, igViewerStatisticsManager_EnsureRegistered, igGuiComponentList_EnsureRegistered, igObjectList_EnsureRegistered, igRadioGroup_EnsureRegistered, igTextureList_EnsureRegistered, igViewerModeChangeMessage_EnsureRegistered, 0 };

CallbackArray *igViewerSceneInfoManager_Register(void) {
    ViewerLibrary_MarkRegistered();  /* one-shot static-init latch (sets a gp-relative byte flag once) */
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igViewerSceneInfoManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        igViewerSceneInfoManager_GetMetaObjectFunction,
        "igViewerSceneInfoManager",
        0xC8, /* instance size */
        igViewerSceneInfoManager_GetVTable,
        FUN_00459ee0,                               /* field adder: InitFields, registers the reflected fields */
        0, /* extra callback item */
        g_igViewerSceneInfoManager_callbackList /* callback list */
    );
}

void igViewerSceneInfoManager_GetMetaObjectFunction(void) {
    igViewerSceneInfoManager_GetMetaObject();
}

static FieldFactory g_igViewerSceneInfoManager_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
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
    igIntMetaField_Create,
    igLongMetaField_Create,
    igEnumMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igViewerSceneInfoManager_fieldTable[] = {
    "_applicationController",
    "_parameters",
    "_viewerRenderer",
    "_bboxRenderer",
    "_normalsRenderer",
    "_flushRenderer",
    "_clippingCheckFrame",
    "_gui",
    "_guiFactory",
    "_rootComponent",
    "_menuHolder",
    "_operationBoxHolder",
    "_operationBox",
    "_timeBoxHolder",
    "_timeBox",
    "_menuBar",
    "_viewMenu",
    "_viewportMenu",
    "_cameraMenu",
    "_cameraMenuActiver",
    "_optionMenu",
    "_disableMenu",
    "_statMenu",
    "_timeMenu",
    "_alchemyMenu",
    "_timeStatistic",
    "_speedStatistic",
    "_nearPlaneStatistic",
    "_farPlaneStatistic",
    "_hotKeyReceiver",
    "_viewManager",
    "_statManager",
    "_disableComponents",
    "_disableViews",
    "_operationModeGroup",
    "_references",
    "_frames",
    "_lastStatTime",
    "_guiVisibility",
    "_textureList",
    "_modeChange",
    "_isCapturingBudget",
    "_hideAllStatisticsMenuItem",
};
static igMetaField **g_igViewerSceneInfoManager_fieldHandles[] = {
    &g_igViewerSceneInfoManager_applicationControllerMetaField,
    &g_igViewerSceneInfoManager_parametersMetaField,
    &g_igViewerSceneInfoManager_viewerRendererMetaField,
    &g_igViewerSceneInfoManager_bboxRendererMetaField,
    &g_igViewerSceneInfoManager_normalsRendererMetaField,
    &g_igViewerSceneInfoManager_flushRendererMetaField,
    &g_igViewerSceneInfoManager_clippingCheckFrameMetaField,
    &g_igViewerSceneInfoManager_guiMetaField,
    &g_igViewerSceneInfoManager_guiFactoryMetaField,
    &g_igViewerSceneInfoManager_rootComponentMetaField,
    &g_igViewerSceneInfoManager_menuHolderMetaField,
    &g_igViewerSceneInfoManager_operationBoxHolderMetaField,
    &g_igViewerSceneInfoManager_operationBoxMetaField,
    &g_igViewerSceneInfoManager_timeBoxHolderMetaField,
    &g_igViewerSceneInfoManager_timeBoxMetaField,
    &g_igViewerSceneInfoManager_menuBarMetaField,
    &g_igViewerSceneInfoManager_viewMenuMetaField,
    &g_igViewerSceneInfoManager_viewportMenuMetaField,
    &g_igViewerSceneInfoManager_cameraMenuMetaField,
    &g_igViewerSceneInfoManager_cameraMenuActiverMetaField,
    &g_igViewerSceneInfoManager_optionMenuMetaField,
    &g_igViewerSceneInfoManager_disableMenuMetaField,
    &g_igViewerSceneInfoManager_statMenuMetaField,
    &g_igViewerSceneInfoManager_timeMenuMetaField,
    &g_igViewerSceneInfoManager_alchemyMenuMetaField,
    &g_igViewerSceneInfoManager_timeStatisticMetaField,
    &g_igViewerSceneInfoManager_speedStatisticMetaField,
    &g_igViewerSceneInfoManager_nearPlaneStatisticMetaField,
    &g_igViewerSceneInfoManager_farPlaneStatisticMetaField,
    &g_igViewerSceneInfoManager_hotKeyReceiverMetaField,
    &g_igViewerSceneInfoManager_viewManagerMetaField,
    &g_igViewerSceneInfoManager_statManagerMetaField,
    &g_igViewerSceneInfoManager_disableComponentsMetaField,
    &g_igViewerSceneInfoManager_disableViewsMetaField,
    &g_igViewerSceneInfoManager_operationModeGroupMetaField,
    &g_igViewerSceneInfoManager_referencesMetaField,
    &g_igViewerSceneInfoManager_framesMetaField,
    &g_igViewerSceneInfoManager_lastStatTimeMetaField,
    &g_igViewerSceneInfoManager_guiVisibilityMetaField,
    &g_igViewerSceneInfoManager_textureListMetaField,
    &g_igViewerSceneInfoManager_modeChangeMetaField,
    &g_igViewerSceneInfoManager_isCapturingBudgetMetaField,
    &g_igViewerSceneInfoManager_hideAllStatisticsMenuItemMetaField,
};
static int g_igViewerSceneInfoManager_fieldOffsets[] = {
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
    168,
    176,
    180,
    184,
    188,
    192,
};

void FUN_00459ee0(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_10;
    void *temp_s0_11;
    void *temp_s0_12;
    void *temp_s0_13;
    void *temp_s0_14;
    void *temp_s0_15;
    void *temp_s0_16;
    void *temp_s0_17;
    void *temp_s0_18;
    void *temp_s0_19;
    void *temp_s0_20;
    void *temp_s0_21;
    void *temp_s0_22;
    void *temp_s0_23;
    void *temp_s0_24;
    void *temp_s0_25;
    void *temp_s0_26;
    void *temp_s0_27;
    void *temp_s0_28;
    void *temp_s0_29;
    void *temp_s0_2;
    void *temp_s0_30;
    void *temp_s0_31;
    void *temp_s0_32;
    void *temp_s0_33;
    void *temp_s0_34;
    void *temp_s0_35;
    void *temp_s0_36;
    void *temp_s0_37;
    void *temp_s0_38;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s0_6;
    void *temp_s0_7;
    void *temp_s0_8;
    void *temp_s0_9;
    void *temp_s1;
    void *temp_v0_2;
    void *temp_v0_3;

    temp_s1 = g_igViewerSceneInfoManager_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igViewerSceneInfoManager_ctorTable, 0x2B);
    temp_v0 = (void **)(igMetaObject_FindFieldByName((igMetaObject *)temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText((igMetaField *)temp_v0_2, "Viewer scene manager");
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&g_igViewerSceneInfoManager_nameMetaField);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s3, (igMetaField *)temp_v0_2);
    *(int *)((char *)(temp_v0_2) + 4) = (int)((int) (*(int *)((char *)(temp_v0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_v0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2));
    *(int *)((char *)(temp_s0) + 56) = (int)igViewerSceneInfoManagerController_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0) + 52) = 1;
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 1));
    *(int *)((char *)(temp_s0_2) + 56) = (int)igViewerParameters_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_2) + 52) = 1;
    temp_s0_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 2));
    *(int *)((char *)(temp_s0_3) + 56) = (int)igViewerRenderer_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_3) + 52) = 1;
    temp_s0_4 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 3));
    *(int *)((char *)(temp_s0_4) + 56) = (int)igBoundingBoxRenderer_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_4) + 52) = 1;
    temp_s0_5 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 4));
    *(int *)((char *)(temp_s0_5) + 56) = (int)igNormalsRenderer_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_5) + 52) = 1;
    temp_s0_6 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 5));
    *(int *)((char *)(temp_s0_6) + 56) = (int)igFlushRenderer_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_6) + 52) = 1;
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 6), -1);
    temp_s0_7 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 7));
    *(int *)((char *)(temp_s0_7) + 56) = (int)igGuiSystem_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_7) + 52) = 1;
    temp_s0_8 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 8));
    *(int *)((char *)(temp_s0_8) + 56) = (int)igViewerGuiFactory_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_8) + 52) = 1;
    temp_s0_9 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 9));
    *(int *)((char *)(temp_s0_9) + 56) = (int)igBoxComponent_GetOrCreateMetaObject();
    temp_s0_10 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0xA));
    *(int *)((char *)(temp_s0_10) + 56) = (int)igGuiComponent_GetOrCreateMetaObject();
    temp_s0_11 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0xB));
    *(int *)((char *)(temp_s0_11) + 56) = (int)igGuiComponent_GetOrCreateMetaObject();
    temp_s0_12 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0xC));
    *(int *)((char *)(temp_s0_12) + 56) = (int)igBoxComponent_GetOrCreateMetaObject();
    temp_s0_13 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0xD));
    *(int *)((char *)(temp_s0_13) + 56) = (int)igGuiComponent_GetOrCreateMetaObject();
    temp_s0_14 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0xE));
    *(int *)((char *)(temp_s0_14) + 56) = (int)igBoxComponent_GetOrCreateMetaObject();
    temp_s0_15 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0xF));
    *(int *)((char *)(temp_s0_15) + 56) = (int)igBoxComponent_GetOrCreateMetaObject();
    temp_s0_16 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x10));
    *(int *)((char *)(temp_s0_16) + 56) = (int)igBoxComponent_GetOrCreateMetaObject();
    temp_s0_17 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x11));
    *(int *)((char *)(temp_s0_17) + 56) = (int)igBoxComponent_GetOrCreateMetaObject();
    temp_s0_18 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x12));
    *(int *)((char *)(temp_s0_18) + 56) = (int)igBoxComponent_GetOrCreateMetaObject();
    temp_s0_19 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x13));
    *(int *)((char *)(temp_s0_19) + 56) = (int)igGuiComponent_GetOrCreateMetaObject();
    temp_s0_20 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x14));
    *(int *)((char *)(temp_s0_20) + 56) = (int)igBoxComponent_GetOrCreateMetaObject();
    temp_s0_21 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x15));
    *(int *)((char *)(temp_s0_21) + 56) = (int)igBoxComponent_GetOrCreateMetaObject();
    temp_s0_22 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x16));
    *(int *)((char *)(temp_s0_22) + 56) = (int)igBoxComponent_GetOrCreateMetaObject();
    temp_s0_23 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x17));
    *(int *)((char *)(temp_s0_23) + 56) = (int)igBoxComponent_GetOrCreateMetaObject();
    temp_s0_24 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x18));
    *(int *)((char *)(temp_s0_24) + 56) = (int)igBoxComponent_GetOrCreateMetaObject();
    temp_s0_25 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x19));
    *(int *)((char *)(temp_s0_25) + 56) = (int)igStatisticsItem_GetOrCreateMetaObject();
    temp_s0_26 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x1A));
    *(int *)((char *)(temp_s0_26) + 56) = (int)igStatisticsItem_GetOrCreateMetaObject();
    temp_s0_27 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x1B));
    *(int *)((char *)(temp_s0_27) + 56) = (int)igStatisticsItem_GetOrCreateMetaObject();
    temp_s0_28 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x1C));
    *(int *)((char *)(temp_s0_28) + 56) = (int)igStatisticsItem_GetOrCreateMetaObject();
    temp_s0_29 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x1D));
    *(int *)((char *)(temp_s0_29) + 56) = (int)igHotKeyEventReceiver_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_29) + 52) = 1;
    temp_s0_30 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x1E));
    *(int *)((char *)(temp_s0_30) + 56) = (int)igViewManager_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_30) + 52) = 1;
    temp_s0_31 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x1F));
    *(int *)((char *)(temp_s0_31) + 56) = (int)igViewerStatisticsManager_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_31) + 52) = 1;
    temp_s0_32 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x20));
    *(int *)((char *)(temp_s0_32) + 56) = (int)igGuiComponentList_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_32) + 52) = 1;
    temp_s0_33 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x21));
    *(int *)((char *)(temp_s0_33) + 56) = (int)igObjectList_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_33) + 52) = 1;
    temp_s0_34 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x22));
    *(int *)((char *)(temp_s0_34) + 56) = (int)igRadioGroup_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_34) + 52) = 1;
    temp_s0_35 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x23));
    *(int *)((char *)(temp_s0_35) + 56) = (int)igObjectList_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_35) + 52) = 1;
    temp_v0_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x26));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0_3, 0);
    *(int *)((char *)(temp_v0_3) + 52) = (int)(&FUN_004592e0);
    temp_s0_36 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x27));
    *(int *)((char *)(temp_s0_36) + 56) = (int)igTextureList_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_36) + 52) = 1;
    temp_s0_37 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x28));
    *(int *)((char *)(temp_s0_37) + 56) = (int)igViewerModeChangeMessage_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_37) + 52) = 1;
    temp_s0_38 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s2 + 0x2A));
    *(int *)((char *)(temp_s0_38) + 56) = (int)igGuiComponent_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igViewerSceneInfoManager_fieldTable, g_igViewerSceneInfoManager_fieldHandles, g_igViewerSceneInfoManager_fieldOffsets, temp_s2);
}

