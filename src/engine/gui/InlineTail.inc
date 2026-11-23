namespace Gap {
namespace Gui {

void igView::userDestruct()
{
    if (_model) {
        _model->removeView(this);
    }
    igObject::userDestruct();
}
}
}

int igTextElement_GetMeta(void) {
    return (int)g_igTextElement_metaObject;
}

igMetaObject *igOnOffValueObserver_GetMeta(void) {
    return g_igOnOffValueObserver_metaObject;
}

void igOnOffValueObserver_IsCompatible(void *arg0, int arg1) {
    ((Gap::Core::igObject *)arg1)->isOfType(igOnOffModel_GetMetaObject());
}

igMetaObject *igRadioGroupSelectedObserver_GetMeta(void) {
    return g_igRadioGroupSelectedObserver_metaObject;
}

void igRadioGroupSelectedObserver_IsCompatible(void *arg0, int arg1) {
    ((Gap::Core::igObject *)arg1)->isOfType(igRadioGroupModel_GetMetaObject());
}

igMetaObject *igRadioGroup_GetMeta(void) {
    return g_igRadioGroup_metaObject;
}

igMetaObject *igHotKeyEventReceiver_GetMeta(void) {
    return g_igHotKeyEventReceiver_metaObject;
}

igMetaObject *igGuiSystem_GetMeta(void) {
    return g_igGuiSystem_metaObject;
}

igMetaObject *igGuiSystemRenderer_GetMeta(void) {
    return g_igGuiSystemRenderer_metaObject;
}

igMetaObject *igActiveComponentsObserver_GetMeta(void) {
    return g_igActiveComponentsObserver_metaObject;
}

void igActiveComponentsObserver_IsCompatible(void *arg0, int arg1) {
    ((Gap::Core::igObject *)arg1)->isOfType(igGuiSystemModel_GetMetaObject());
}

igMetaObject *igMousePosObserver_GetMeta(void) {
    return g_igMousePosObserver_metaObject;
}

void igMousePosObserver_IsCompatible(void *arg0, int arg1) {
    ((Gap::Core::igObject *)arg1)->isOfType(igGuiSystemModel_GetMetaObject());
}

igMetaObject *igWindowSizeObserver_GetMeta(void) {
    return g_igWindowSizeObserver_metaObject;
}

void igWindowSizeObserver_IsCompatible(void *arg0, int arg1) {
    ((Gap::Core::igObject *)arg1)->isOfType(igGuiSystemModel_GetMetaObject());
}

igMetaObject *igGuiSystemModel_GetMeta(void) {
    return g_igGuiSystemModel_metaObject;
}

igMetaObject *igGuiComponentNode_GetMeta(void) {
    return g_igGuiComponentNode_metaObject;
}

int igGuiComponentController_GetMeta(void) {
    return (int)g_igGuiComponentController_metaObject;
}

igMetaObject *igGuiComponent_GetMeta(void) {
    return g_igGuiComponent_metaObject;
}

igMetaObject *igFieldChangeView_GetMeta(void) {
    return g_igFieldChangeView_metaObject;
}

int igFieldChangeView_IsCompatible(void) {
    return 1;
}

igMetaObject *igEventDispatcher_GetMeta(void) {
    return g_igEventDispatcher_metaObject;
}

int igDefaultAspect_GetMeta(void) {
    return (int)g_igDefaultAspect_metaObject;
}

void igDefaultAspect_IsCompatible(igDefaultAspect *self, int model) {
    ((Gap::Core::igObject *)model)->isOfType(igGuiComponentModel_GetMetaObject());
}

igMetaObject *igOnOffColorChanger_GetMeta(void) {
    return g_igOnOffColorChanger_metaObject;
}

igMetaObject *igBasicColorChanger_GetMeta(void) {
    return g_igBasicColorChanger_metaObject;
}

igMetaObject *igColorChanger_GetMeta(void) {
    return g_igColorChanger_metaObject;
}

igMetaObject *igBitmapFont_GetMeta(void) {
    return g_igBitmapFont_metaObject;
}

igMetaObject *igCharMetricsMetaField_GetMeta(void) {
    return g_igCharMetricsMetaField_metaObject;
}

int igCharMetricsMetaField_GetDescriptor(void) {
    return (int)g_igCharMetricsMetaField_instance;
}

int igCharMetricsList_GetMeta(void) {
    return (int)g_igCharMetricsList_metaObject;
}

igMetaObject *igBoxComponent_GetMeta(void) {
    return g_igBoxComponent_metaObject;
}

igMetaObject *igDefaultAspectElement_GetMeta(void) {
    return g_igDefaultAspectElement_metaObject;
}

igMetaObject *igDefaultAspectElementList_GetMeta(void) {
    return g_igDefaultAspectElementList_metaObject;
}

igMetaObject *igEventReceiverOrderedList_GetMeta(void) {
    return g_igEventReceiverOrderedList_metaObject;
}

int igFieldChangeViewList_GetMeta(void) {
    return (int)g_igFieldChangeViewList_metaObject;
}

igMetaObject *igFieldSynchronizer_GetMeta(void) {
    return g_igFieldSynchronizer_metaObject;
}

igMetaObject *igGuiComponentList_GetMeta(void) {
    return g_igGuiComponentList_metaObject;
}

igMetaObject *igMouseCursor_GetMeta(void) {
    return g_igMouseCursor_metaObject;
}

igMetaObject *igHotKeyBinding_GetMeta(void) {
    return g_igHotKeyBinding_metaObject;
}

igMetaObject *igHotKeyBindingList_GetMeta(void) {
    return g_igHotKeyBindingList_metaObject;
}

igMetaObject *igOnOffModel_GetMeta(void) {
    return g_igOnOffModel_metaObject;
}

igMetaObject *igRadioGroupModel_GetMeta(void) {
    return g_igRadioGroupModel_metaObject;
}

igMetaObject *igOnOffValueObserverList_GetMeta(void) {
    return g_igOnOffValueObserverList_metaObject;
}

igMetaObject *igRendererOrderedList_GetMeta(void) {
    return g_igRendererOrderedList_metaObject;
}

int igGuiComponentModel_GetMeta(void) {
    return (int)g_igGuiComponentModel_metaObject;
}

int FUN_00458310(void) {
    return (int)g_igGeometryElement_metaObject;
}

/* Element size in bytes of the list's items: 0x28 (one igCharMetrics record). The same class's
 * TrimCapacity (vfunc_18) re-sizes the buffer with Gap::Core::igDataList::setCapacity(self, count, 0x28), and the
 * sibling lists igDependencyList (8) and igPsx2AudioSourceList (0x24) return their item size from
 * this same slot 23. */

int igCharMetricsList_GetElementSize(void) {
    return CHAR_METRICS_ITEM_SIZE;
}

igMetaObject *igDefaultAspectElementList_GetElementMeta(void) {
    return g_igDefaultAspectElement_metaObject;
}

int igFieldChangeViewList_GetElementMeta(void) {
    return (int)g_igFieldChangeView_metaObject;
}

igMetaObject *igHotKeyBindingList_GetElementMeta(void) {
    return g_igHotKeyBinding_metaObject;
}

igMetaObject *igOnOffValueObserverList_GetElementMeta(void) {
    return g_igOnOffValueObserver_metaObject;
}

igMetaObject *igGuiComponentList_GetElementMeta(void) {
    return g_igGuiComponent_metaObject;
}

void igCharMetricsList_TrimCapacity(igCharMetricsList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        ((Gap::Core::igDataList *)self)->setCapacity(count, 0x28);
    }
}

