int igObject_IsKindOf();
int igRadioGroupModel_GetMetaObject();

void Gap__Gui__igRadioGroupSelectedObserver__vfunc_23(void *arg0, int arg1) {
    igObject_IsKindOf(arg1, igRadioGroupModel_GetMetaObject());
}
