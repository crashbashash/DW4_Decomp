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

int Gap__Gui__igClearRenderer__vfunc_22(void) {
    return DAT_0058c1f0[0];
}

void Gap__Gui__igClearRenderer__vfunc_25(void) {

}

void Gap__Gui__igClearRenderer__vfunc_24(void) {

}

int Gap__Gui__igOnOffValueObserver__vfunc_22(void) {
    return DAT_0058c220[0];
}

void Gap__Gui__igOnOffValueObserver__vfunc_23(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igOnOffModel_GetMetaObject());
}

int Gap__Gui__igRadioGroupSelectedObserver__vfunc_22(void) {
    return DAT_0058c230[0];
}

void Gap__Gui__igRadioGroupSelectedObserver__vfunc_23(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igRadioGroupModel_GetMetaObject());
}

int Gap__Gui__igRadioGroup__vfunc_22(void) {
    return DAT_0058c240[0];
}

int Gap__Gui__igModel__vfunc_22(void) {
    return DAT_0058c298[0];
}

int Gap__Gui__igHotKeyEventReceiver__vfunc_22(void) {
    return DAT_0058c2a8[0];
}

int Gap__Gui__igGuiSystem__vfunc_22(void) {
    return DAT_0058c2e0[0];
}

int Gap__Gui__igGuiSystemRenderer__vfunc_22(void) {
    return DAT_0058c338[0];
}

int Gap__Gui__igActiveComponentsObserver__vfunc_22(void) {
    return DAT_0058c360[0];
}

void Gap__Gui__igActiveComponentsObserver__vfunc_23(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igGuiSystemModel_GetMetaObject());
}

int Gap__Gui__igMousePosObserver__vfunc_22(void) {
    return DAT_0058c380[0];
}

void Gap__Gui__igMousePosObserver__vfunc_23(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igGuiSystemModel_GetMetaObject());
}

int Gap__Gui__igWindowSizeObserver__vfunc_22(void) {
    return DAT_0058c3c0[0];
}

void Gap__Gui__igWindowSizeObserver__vfunc_23(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igGuiSystemModel_GetMetaObject());
}

int Gap__Gui__igGuiSystemModel__vfunc_22(void) {
    return DAT_0058c3c8[0];
}

int Gap__Gui__igGuiComponentNode__vfunc_22(void) {
    return DAT_0058c428[0];
}

int Gap__Gui__igGuiComponentController__vfunc_22(void) {
    return (int)g_igGuiComponentController_metaObject[0];
}

int Gap__Gui__igGuiComponent__vfunc_22(void) {
    return DAT_0058c4a8[0];
}

int Gap__Gui__igFieldChangeView__vfunc_22(void) {
    return DAT_0058c550[0];
}

int Gap__Gui__igFieldChangeView__vfunc_23(void) {
    return 1;
}

int Gap__Gui__igEventDispatcher__vfunc_22(void) {
    return DAT_0058c578[0];
}

int Gap__Gui__igDefaultAspect__vfunc_22(void) {
    return (int)g_igDefaultAspect_metaObject[0];
}

void Gap__Gui__igDefaultAspect__vfunc_23(igDefaultAspect *self, int model) {
    igObject_IsKindOf(model, igGuiComponentModel_GetMetaObject());
}

int Gap__Gui__igOnOffColorChanger__vfunc_22(void) {
    return DAT_0058c5e8[0];
}

int Gap__Gui__igBasicColorChanger__vfunc_22(void) {
    return DAT_0058c5f0[0];
}

int Gap__Gui__igColorChanger__vfunc_22(void) {
    return DAT_0058c608[0];
}

int Gap__Gui__igBitmapFont__vfunc_22(void) {
    return DAT_0058c620[0];
}

int Gap__Gui__igCharMetricsMetaField__vfunc_22(void) {
    return DAT_0058c648[0];
}

int Gap__Gui__igCharMetricsMetaField__vfunc_23(void) {
    return (int)DAT_0058c650[0];
}

int Gap__Gui__igCharMetricsList__vfunc_22(void) {
    return (int)g_igCharMetricsList_metaObject[0];
}

int Gap__Gui__igBoxComponent__vfunc_22(void) {
    return DAT_0058c610[0];
}

int Gap__Gui__igDefaultAspectElement__vfunc_22(void) {
    return DAT_0058c5b0[0];
}

int Gap__Gui__igDefaultAspectElementList__vfunc_22(void) {
    return DAT_0058c5a0[0];
}

int Gap__Gui__igEventReceiverOrderedList__vfunc_22(void) {
    return DAT_0058c568[0];
}

int Gap__Gui__igFieldChangeViewList__vfunc_22(void) {
    return (int)g_igFieldChangeViewList_metaObject[0];
}

int Gap__Gui__igFieldSynchronizer__vfunc_22(void) {
    return DAT_0058c538[0];
}

int Gap__Gui__igGuiComponentList__vfunc_22(void) {
    return DAT_0058c4a0[0];
}

int Gap__Gui__igMouseCursor__vfunc_22(void) {
    return DAT_0058c320[0];
}

int Gap__Gui__igHotKeyBinding__vfunc_22(void) {
    return DAT_0058c2c0[0];
}

int Gap__Gui__igHotKeyBindingList__vfunc_22(void) {
    return DAT_0058c2b8[0];
}

int Gap__Gui__igOnOffModel__vfunc_22(void) {
    return DAT_0058c288[0];
}

int Gap__Gui__igRadioGroupModel__vfunc_22(void) {
    return DAT_0058c278[0];
}

int Gap__Gui__igOnOffValueObserverList__vfunc_22(void) {
    return DAT_0058c218[0];
}

int Gap__Gui__igRendererOrderedList__vfunc_22(void) {
    return DAT_0058c200[0];
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

int Gap__Gui__igNonRefCountedViewList__vfunc_22(void) {
    return DAT_0058c1b0[0];
}

int Gap__Gui__igNonRefCountedViewList__vfunc_24(void) {
    return DAT_0058c1c0[0];
}

/* Element size in bytes of the list's items: 0x28 (one igCharMetrics record). The same class's
 * TrimCapacity (vfunc_18) re-sizes the buffer with List_Reserve(self, count, 0x28), and the
 * sibling lists igDependencyList (8) and igPsx2AudioSourceList (0x24) return their item size from
 * this same slot 23. */

int Gap__Gui__igCharMetricsList__vfunc_23(void) {
    return CHAR_METRICS_ITEM_SIZE;
}

int Gap__Gui__igDefaultAspectElementList__vfunc_24(void) {
    return DAT_0058c5b0[0];
}

int Gap__Gui__igFieldChangeViewList__vfunc_24(void) {
    return (int)g_igFieldChangeView_metaObject[0];
}

int Gap__Gui__igHotKeyBindingList__vfunc_24(void) {
    return DAT_0058c2c0[0];
}

int Gap__Gui__igOnOffValueObserverList__vfunc_24(void) {
    return DAT_0058c220[0];
}

int Gap__Gui__igGuiComponentList__vfunc_24(void) {
    return DAT_0058c4a8[0];
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

