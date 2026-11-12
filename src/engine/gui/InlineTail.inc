/* Teardown slot (the slot the other classes' teardown bodies also chain from to the igObject
 * base): if the mode still has its _model, FUN_004577f0 detaches the mode from it (it nulls the
 * mode's entry in the model's list at +8), then the base igObject teardown runs. */
void Gap__Bec__beCameraMode__vfunc_08(beCameraMode *self) {
    int model;

    model = self->_model;
    if (model != 0) {
        FUN_004577f0((igModel *)model, (OV *)self);
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(self);
}

int Gap__Gui__igTextElement__vfunc_22(void) {
    return (int)g_igTextElement_metaObject[0];
}

igMetaObject *Gap__Gui__igClearRenderer__vfunc_22(void) {
    return g_igClearRenderer_metaObject[0];
}

void Gap__Gui__igClearRenderer__vfunc_25(void) {

}

void Gap__Gui__igClearRenderer__vfunc_24(void) {

}

igMetaObject *Gap__Gui__igOnOffValueObserver__vfunc_22(void) {
    return g_igOnOffValueObserver_metaObject[0];
}

void Gap__Gui__igOnOffValueObserver__vfunc_23(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igOnOffModel_GetMetaObject());
}

igMetaObject *Gap__Gui__igRadioGroupSelectedObserver__vfunc_22(void) {
    return g_igRadioGroupSelectedObserver_metaObject[0];
}

void Gap__Gui__igRadioGroupSelectedObserver__vfunc_23(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igRadioGroupModel_GetMetaObject());
}

igMetaObject *Gap__Gui__igRadioGroup__vfunc_22(void) {
    return g_igRadioGroup_metaObject[0];
}

igMetaObject *Gap__Gui__igModel__vfunc_22(void) {
    return g_igModel_metaObject[0];
}

igMetaObject *Gap__Gui__igHotKeyEventReceiver__vfunc_22(void) {
    return g_igHotKeyEventReceiver_metaObject[0];
}

igMetaObject *Gap__Gui__igGuiSystem__vfunc_22(void) {
    return g_igGuiSystem_metaObject[0];
}

igMetaObject *Gap__Gui__igGuiSystemRenderer__vfunc_22(void) {
    return g_igGuiSystemRenderer_metaObject[0];
}

igMetaObject *Gap__Gui__igActiveComponentsObserver__vfunc_22(void) {
    return g_igActiveComponentsObserver_metaObject[0];
}

void Gap__Gui__igActiveComponentsObserver__vfunc_23(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igGuiSystemModel_GetMetaObject());
}

igMetaObject *Gap__Gui__igMousePosObserver__vfunc_22(void) {
    return g_igMousePosObserver_metaObject[0];
}

void Gap__Gui__igMousePosObserver__vfunc_23(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igGuiSystemModel_GetMetaObject());
}

igMetaObject *Gap__Gui__igWindowSizeObserver__vfunc_22(void) {
    return g_igWindowSizeObserver_metaObject[0];
}

void Gap__Gui__igWindowSizeObserver__vfunc_23(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igGuiSystemModel_GetMetaObject());
}

igMetaObject *Gap__Gui__igGuiSystemModel__vfunc_22(void) {
    return g_igGuiSystemModel_metaObject[0];
}

igMetaObject *Gap__Gui__igGuiComponentNode__vfunc_22(void) {
    return g_igGuiComponentNode_metaObject[0];
}

int Gap__Gui__igGuiComponentController__vfunc_22(void) {
    return (int)g_igGuiComponentController_metaObject[0];
}

igMetaObject *Gap__Gui__igGuiComponent__vfunc_22(void) {
    return g_igGuiComponent_metaObject[0];
}

igMetaObject *Gap__Gui__igFieldChangeView__vfunc_22(void) {
    return g_igFieldChangeView_metaObject[0];
}

int Gap__Gui__igFieldChangeView__vfunc_23(void) {
    return 1;
}

igMetaObject *Gap__Gui__igEventDispatcher__vfunc_22(void) {
    return g_igEventDispatcher_metaObject[0];
}

int Gap__Gui__igDefaultAspect__vfunc_22(void) {
    return (int)g_igDefaultAspect_metaObject[0];
}

void Gap__Gui__igDefaultAspect__vfunc_23(igDefaultAspect *self, int model) {
    igObject_IsKindOf(model, igGuiComponentModel_GetMetaObject());
}

igMetaObject *Gap__Gui__igOnOffColorChanger__vfunc_22(void) {
    return g_igOnOffColorChanger_metaObject[0];
}

igMetaObject *Gap__Gui__igBasicColorChanger__vfunc_22(void) {
    return g_igBasicColorChanger_metaObject[0];
}

igMetaObject *Gap__Gui__igColorChanger__vfunc_22(void) {
    return g_igColorChanger_metaObject[0];
}

igMetaObject *Gap__Gui__igBitmapFont__vfunc_22(void) {
    return g_igBitmapFont_metaObject[0];
}

igMetaObject *Gap__Gui__igCharMetricsMetaField__vfunc_22(void) {
    return g_igCharMetricsMetaField_metaObject[0];
}

int Gap__Gui__igCharMetricsMetaField__vfunc_23(void) {
    return (int)DAT_0058c650[0];
}

int Gap__Gui__igCharMetricsList__vfunc_22(void) {
    return (int)g_igCharMetricsList_metaObject[0];
}

igMetaObject *Gap__Gui__igBoxComponent__vfunc_22(void) {
    return g_igBoxComponent_metaObject[0];
}

igMetaObject *Gap__Gui__igDefaultAspectElement__vfunc_22(void) {
    return g_igDefaultAspectElement_metaObject[0];
}

igMetaObject *Gap__Gui__igDefaultAspectElementList__vfunc_22(void) {
    return g_igDefaultAspectElementList_metaObject[0];
}

igMetaObject *Gap__Gui__igEventReceiverOrderedList__vfunc_22(void) {
    return g_igEventReceiverOrderedList_metaObject[0];
}

int Gap__Gui__igFieldChangeViewList__vfunc_22(void) {
    return (int)g_igFieldChangeViewList_metaObject[0];
}

igMetaObject *Gap__Gui__igFieldSynchronizer__vfunc_22(void) {
    return g_igFieldSynchronizer_metaObject[0];
}

igMetaObject *Gap__Gui__igGuiComponentList__vfunc_22(void) {
    return g_igGuiComponentList_metaObject[0];
}

igMetaObject *Gap__Gui__igMouseCursor__vfunc_22(void) {
    return g_igMouseCursor_metaObject[0];
}

igMetaObject *Gap__Gui__igHotKeyBinding__vfunc_22(void) {
    return g_igHotKeyBinding_metaObject[0];
}

igMetaObject *Gap__Gui__igHotKeyBindingList__vfunc_22(void) {
    return g_igHotKeyBindingList_metaObject[0];
}

igMetaObject *Gap__Gui__igOnOffModel__vfunc_22(void) {
    return g_igOnOffModel_metaObject[0];
}

igMetaObject *Gap__Gui__igRadioGroupModel__vfunc_22(void) {
    return g_igRadioGroupModel_metaObject[0];
}

igMetaObject *Gap__Gui__igOnOffValueObserverList__vfunc_22(void) {
    return g_igOnOffValueObserverList_metaObject[0];
}

igMetaObject *Gap__Gui__igRendererOrderedList__vfunc_22(void) {
    return g_igRendererOrderedList_metaObject[0];
}

int Gap__Gui__igGuiComponentModel__vfunc_22(void) {
    return (int)g_igGuiComponentModel_metaObject[0];
}

int FUN_00458310(void) {
    return (int)g_igGeometryElement_metaObject[0];
}

int Gap__Gui__igViewList__vfunc_22(void) {
    return (int)g_igViewList_metaObject[0];
}

igMetaObject *Gap__Gui__igNonRefCountedViewList__vfunc_22(void) {
    return g_igNonRefCountedViewList_metaObject[0];
}

igMetaObject *Gap__Gui__igNonRefCountedViewList__vfunc_24(void) {
    return g_igView_metaObject[0];
}

/* Element size in bytes of the list's items: 0x28 (one igCharMetrics record). The same class's
 * TrimCapacity (vfunc_18) re-sizes the buffer with List_Reserve(self, count, 0x28), and the
 * sibling lists igDependencyList (8) and igPsx2AudioSourceList (0x24) return their item size from
 * this same slot 23. */

int Gap__Gui__igCharMetricsList__vfunc_23(void) {
    return CHAR_METRICS_ITEM_SIZE;
}

igMetaObject *Gap__Gui__igDefaultAspectElementList__vfunc_24(void) {
    return g_igDefaultAspectElement_metaObject[0];
}

int Gap__Gui__igFieldChangeViewList__vfunc_24(void) {
    return (int)g_igFieldChangeView_metaObject[0];
}

igMetaObject *Gap__Gui__igHotKeyBindingList__vfunc_24(void) {
    return g_igHotKeyBinding_metaObject[0];
}

igMetaObject *Gap__Gui__igOnOffValueObserverList__vfunc_24(void) {
    return g_igOnOffValueObserver_metaObject[0];
}

igMetaObject *Gap__Gui__igGuiComponentList__vfunc_24(void) {
    return g_igGuiComponent_metaObject[0];
}

int Gap__Gui__igViewList__vfunc_24(void) {
    return (int)g_igView_metaObject[0];
}

void Gap__Gui__igCharMetricsList__vfunc_18(igCharMetricsList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        List_Reserve(self, count, 0x28);
    }
}

