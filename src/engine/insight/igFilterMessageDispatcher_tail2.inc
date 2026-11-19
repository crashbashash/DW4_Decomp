void igFilterMessageDispatcher_AddFilteringForType(FilterDispatcherSlots *self, int message, igObject *target)
{
    igSmartPointer<MessageFilter> filter = igFilterMessageDispatcher_GetFilterOrCreate((FilterDispatcher *)self, target);

    self->dispatch(message, filter.get());
}

void igFilterMessageDispatcher_AddFiltering(igFilterMessageDispatcher *self, void *arg1, void *arg2) {
    ObjectList_AppendUniqueRetained((igTDataList<igObject *> *)(*(int *)((char *)(arg2) + 12)), (igObject *)arg1);
    ObjectList_AppendUniqueRetained((igTDataList<igObject *> *)(self->_filters), (igObject *)arg2);
}

void igFilterMessageDispatcher_RemoveFilteringForType(void **arg0, int arg1, int arg2) {
    int temp_v0;

    temp_v0 = (int)igFilterMessageDispatcher_GetFilter((const A_237990 *)arg0, arg2);
    if (temp_v0 != 0) {
        ((DW4VC_108_2 *)(arg0))->vX((int)(arg1), (int)(temp_v0));
    }
}

void igFilterMessageDispatcher_RemoveFilteringForReceiver(V *arg0, int arg1) {
    int i;
    for (i = arg0->list->n - 1; i >= 0; i--) {
        arg0->vX(arg1, arg0->list->arr[i]);
    }
}

void igFilterMessageDispatcher_RemoveFiltering(S_arg0 *arg0, void *arg1, S_arg2 *arg2) {
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

void igMessenger_PostMessage(igMessageDispatcherOwnerView *self, void *message)
{
    self->f8->vfunc_26(message);
}

