void Gap__Insight__igFilterMessageDispatcher__vfunc_23(FilterDispatcherSlots *self, int message, igObject *target)
{
    igSmartPointer<MessageFilter> filter = FUN_002379e0((FilterDispatcher *)self, target);

    self->dispatch(message, filter.get());
}

void Gap__Insight__igFilterMessageDispatcher__vfunc_24(void *arg0, void *arg1, void *arg2) {
    ObjectList_AppendUniqueRetained((igTDataList<igObject *> *)(*(int *)((char *)(arg2) + 12)), (igObject *)arg1);
    ObjectList_AppendUniqueRetained((igTDataList<igObject *> *)(*(int *)((char *)(arg0) + 12)), (igObject *)arg2);
}

void Gap__Insight__igFilterMessageDispatcher__vfunc_26(void **arg0, int arg1, int arg2) {
    int temp_v0;

    temp_v0 = (int)FUN_00237990((const A_237990 *)arg0, arg2);
    if (temp_v0 != 0) {
        ((DW4VC_108_2 *)(arg0))->vX((int)(arg1), (int)(temp_v0));
    }
}

void Gap__Insight__igFilterMessageDispatcher__vfunc_25(V *arg0, int arg1) {
    int i;
    for (i = arg0->list->n - 1; i >= 0; i--) {
        arg0->vX(arg1, arg0->list->arr[i]);
    }
}

void Gap__Insight__igFilterMessageDispatcher__vfunc_27(S_arg0 *arg0, void *arg1, S_arg2 *arg2) {
    ObjectList_RemoveFirstRetained((igTDataList<igObject *> *)arg2->f12, (igObject *)arg1, 0);
    if (*(int *)((char *)(arg2->f12) + 8) == 0) {
        ObjectList_RemoveFirstRetained((igTDataList<igObject *> *)arg0->f12, (igObject *)arg2, 0);
        ObjectList_RemoveFirstRetained((igTDataList<igObject *> *)arg0->f8, (igObject *)arg2, 0);
    }
}

void igMessenger_AddReceiver(igMessenger *messenger, igObject *receiver, igMetaObject *messageType)
{
    ((igFilterMessageDispatcherView *)messenger->_dispatcher)->vfunc_21(receiver, messageType);
}

void FUN_00237ea0(igMessageDispatcherOwnerView *self, void *message)
{
    self->f8->vfunc_26(message);
}

