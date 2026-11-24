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
    ((Gap::Core::igObject *)arg1)->isOfType(Gap::Gui::igGuiSystemModel::getClassTypeSafe());
}

igMetaObject *igMousePosObserver_GetMeta(void) {
    return g_igMousePosObserver_metaObject;
}

void igMousePosObserver_IsCompatible(void *arg0, int arg1) {
    ((Gap::Core::igObject *)arg1)->isOfType(Gap::Gui::igGuiSystemModel::getClassTypeSafe());
}

igMetaObject *igWindowSizeObserver_GetMeta(void) {
    return g_igWindowSizeObserver_metaObject;
}

void igWindowSizeObserver_IsCompatible(void *arg0, int arg1) {
    ((Gap::Core::igObject *)arg1)->isOfType(Gap::Gui::igGuiSystemModel::getClassTypeSafe());
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

igMetaObject *igEventDispatcher_GetMeta(void) {
    return g_igEventDispatcher_metaObject;
}

int igDefaultAspect_GetMeta(void) {
    return (int)g_igDefaultAspect_metaObject;
}

void igDefaultAspect_IsCompatible(igDefaultAspect *self, int model) {
    ((Gap::Core::igObject *)model)->isOfType(Gap::Gui::igGuiComponentModel::getClassTypeSafe());
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

igMetaObject *igGuiComponentList_GetMeta(void) {
    return g_igGuiComponentList_metaObject;
}

int FUN_00458310(void) {
    return (int)Gap::Gui::igGeometryElement::getClassMeta();
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

