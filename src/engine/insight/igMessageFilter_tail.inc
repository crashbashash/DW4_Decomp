void igMessageFilter_AcceptMessage(igMessageFilter *self, int arg1) {
    igObject_IsKindOf((igObject *)arg1, (igMetaObject *)(self->_msgType));
}

