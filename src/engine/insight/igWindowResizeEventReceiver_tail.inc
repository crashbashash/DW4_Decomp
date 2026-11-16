int Gap__Insight__igWindowResizeEventReceiver__vfunc_32(Receiver *self, int width, int height) {
    igSmartPointer<ResizeEvent> event((ResizeEvent *)FUN_002332b0(igObject_GetAllocator()));
    {
        ResizeEvent *e = event.get();
        e->origin[0] = DAT_004e0fa0[0];
        e->origin[1] = DAT_004e0fa4[0];
    }
    {
        ResizeEvent *e = event.get();
        e->size[0] = (float)width;
        e->size[1] = (float)height;
    }
    FUN_00237ea0((igMessageDispatcherOwnerView *)self->f8->f40, event.get());
    return 0;
}

void igInsightCore_AddManager(igInsightCore *core, igObject *manager) {
    if (FUN_00236b70() == 0) {
        igRendererOrderedList_Append(core->_managerList, manager, 0);
        *(int *)((char *)(manager) + 12) = (int)(core);
        ((DW4VC_92_0 *)manager)->vX();
    }
}

void igInsightCore_RemoveManager(igInsightCore *core, igObject *manager) {
    int sp3C;

    if (FUN_00236b70() != 0) {
        ((DW4VC_96_0 *)manager)->vX();
        *(int *)((char *)(manager) + 12) = 0;
        igObjectList_RemoveRetained(&sp3C, core->_managerList, manager);
    }
}

void igInsightCore_AddToScheduler(igInsightCore *core, igObject *object) {
    if (((DW4VC_104_0 *)core->_scheduler)->vX() == 0) {
        ((DW4VC_96_1 *)core->_scheduler)->vX((int)object);
    }
}

void igInsightCore_RemoveFromScheduler(igInsightCore *core, igObject *object) {
    if (((DW4VC_104_0 *)core->_scheduler)->vX() != 0) {
        ((DW4VC_100_1 *)core->_scheduler)->vX((int)object);
    }
}

void FUN_00236ca0(int self) {
    int meta;
    int count;
    int i;
    count = igMetaObject_CountTree(meta = (int)igInsightPlugin_GetMetaObject());
    for (i = 0; i < count; i++) {
        int type = igMetaObject_GetTreeNode(meta, i);
        igSmartPointer<Instance> plugin(igMetaObject_CreateInstanceRef(type, igObject_GetAllocator(self)).get(), kRetainReference);
        if (plugin.get()) {
            FUN_00236dd0((void *)self, (void **)plugin.get());
        }
    }
}

void FUN_00236dd0(void *arg0, void **arg1) {
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 104));
    ((DW4VC_92_1 *)(arg1))->vX((int)(arg0));
}

void FUN_00236e20(void *arg0, void **arg1) {
    int sp3C;

    ((DW4VC_96_1 *)(arg1))->vX((int)(arg0));
    ObjectList_RemoveFirstRetained(&sp3C, *(int *)((char *)(arg0) + 104), arg1, 0);
}

void FUN_00236e80(A *arg0) {
    int i;

    for (i = arg0->f68->cnt - 1; i >= 0; i--) {
        FUN_00236e20(arg0, (void **)arg0->f68->arr[i]);
    }
}

void igInsightCore_AddRenderer(igInsightCore *core, igObject *renderer) {
    FUN_00457ca0(renderer, core->_visualContext);
    igRendererOrderedList_Append(core->_rendererList, renderer, 0);
}

void igInsightCore_RemoveRenderer(igInsightCore *core, igObject *renderer) {
    int sp2C;
    igObjectList_RemoveRetained(&sp2C, core->_rendererList, renderer);
    if (sp2C == g_resultSuccess[0]) {
        FUN_00457ca0(renderer, 0);
    }
}

igObject *igInsightCore_FindManager(igInsightCore *core, igMetaObject *kind) {
    unsigned int i;
    for (i = 0; i < (unsigned int)((igObjectList *)((igInfoManagerOrderedList *)core->_managerList)->_objectList)->_count; i++) {
        InfoManagerView *manager = ((InfoManagerView **)((igObjectList *)((igInfoManagerOrderedList *)core->_managerList)->_objectList)->_data)[i];
        if (manager->getMeta() == kind) return (igObject *)manager;
    }
    return 0;
}

int FUN_00237010(void) {
    return (int)g_igInfoManager_metaObject;
}

void igInsightCore_AddRendererOrder(igInsightCore *core, igObject *first, igObject *second)
{
    igDependencyOrderedList_AddDependency(core->_rendererList, first, second);
}

