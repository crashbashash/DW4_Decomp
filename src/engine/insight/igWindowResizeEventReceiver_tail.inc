int igWindowResizeEventReceiver_WindowResizeEvent(Receiver *self, int width, int height) {
    igSmartPointer<ResizeEvent> event((ResizeEvent *)Gap::Insight::igViewportResizedMessage::_instantiateFromPool(((Gap::Core::igObject *)self)->getMemoryPool()));
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
    ((Gap::Insight::igMessenger *)self->f8->f40)->postMessage((Gap::Insight::igMessage *)(event.get()));
    return 0;
}

void igInsightCore_AddManager(igInsightCore *core, igObject *manager) {
    if (igInsightCore_IsRegistered(core, manager) == 0) {
        ((Gap::Core::igDependencyOrderedList *)core->_managerList)->append((Gap::Core::igObject *)manager);
        *(int *)((char *)(manager) + 12) = (int)(core);
        ((DW4VC_92_0 *)manager)->vX();
    }
}

void igInsightCore_RemoveManager(igInsightCore *core, igObject *manager) {
    if (igInsightCore_IsRegistered(core, manager) != 0) {
        ((DW4VC_96_0 *)manager)->vX();
        *(int *)((char *)(manager) + 12) = 0;
        ((Gap::Core::igDependencyOrderedList *)core->_managerList)->remove((Gap::Core::igObject *)manager);
    }
}

/* Index of *item in list, or -1. */
static inline int indexOfItem(const igObjectList *list, igObject *const *item) {
    int count = list->_count;
    for (int i = 0; i < count; i++) {
        if (*item == ((igObject **)list->_data)[i]) return i;
    }
    return -1;
}

/* Whether the core already holds manager in its manager list. */
int igInsightCore_IsRegistered(igInsightCore *core, igObject *manager) {
    igInfoManagerOrderedList *managers = (igInfoManagerOrderedList *)core->_managerList;
    /* matching construct: the copy taken by address keeps the manager in the 12(sp) slot, stored after the first list load. */
    igObject *item = manager;
    igObjectList *list = (igObjectList *)managers->_objectList;
    return indexOfItem(list, &item) >= 0;
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

void igInsightCore_RegisterAllPlugins(igInsightCore *core) {
    int self = (int)core;
    int meta;
    int count;
    int i;
    count = igMetaObject_CountTree((igMetaObject *)(meta = (int)Gap::Insight::igInsightPlugin::getClassTypeSafe()));
    for (i = 0; i < count; i++) {
        int type = (int)(igMetaObject_GetTreeNode((igMetaObject *)meta, i));
        igSmartPointer<Instance> plugin((Instance *)igMetaObject_CreateInstanceRef((igMetaObject *)type, ((Gap::Core::igObject *)self)->getMemoryPool()).get(), kRetainReference);
        if (plugin.get()) {
            igInsightCore_RegisterPlugin((igInsightCore *)self, (void **)plugin.get());
        }
    }
}

void igInsightCore_RegisterPlugin(igInsightCore *self, void **arg1) {
    ((Gap::Core::igObjectList *)self->_plugins)->append((Gap::Core::igObject *)arg1);
    ((DW4VC_92_1 *)(arg1))->vX((int)(self));
}

void igInsightCore_UnregisterPlugin(igInsightCore *self, void **arg1) {
    ((DW4VC_96_1 *)(arg1))->vX((int)(self));
    ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)(self->_plugins)))->removeByValue((Gap::Core::igObject *)arg1, 0);
}

void igInsightCore_UnregisterAllPlugins(igInsightCore *core) {
    A *arg0 = (A *)core;
    int i;

    for (i = arg0->f68->cnt - 1; i >= 0; i--) {
        igInsightCore_UnregisterPlugin((igInsightCore *)arg0, (void **)arg0->f68->arr[i]);
    }
}

void igInsightCore_AddRenderer(igInsightCore *core, igObject *renderer) {
    ((Gap::Gui::igRenderer *)renderer)->setVisualContext((Gap::Gfx::igVisualContext *)core->_visualContext);
    ((Gap::Core::igDependencyOrderedList *)core->_rendererList)->append((Gap::Core::igObject *)renderer);
}

void igInsightCore_RemoveRenderer(igInsightCore *core, igObject *renderer) {
    igResult removed = ((Gap::Core::igDependencyOrderedList *)core->_rendererList)->remove((Gap::Core::igObject *)renderer);
    if (removed.v == g_resultSuccess.v) {
        ((Gap::Gui::igRenderer *)renderer)->setVisualContext(0);
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
    return (int)Gap::Insight::igInfoManager::getClassMeta();
}

void igInsightCore_AddRendererOrder(igInsightCore *core, igObject *first, igObject *second)
{
    ((Gap::Core::igDependencyOrderedList *)core->_rendererList)->appendDependency(first, second);
}

