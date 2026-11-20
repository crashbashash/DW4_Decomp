void igMessageFilter_AcceptMessage(igMessageFilter *self, int arg1) {
    ((Gap::Core::igObject *)arg1)->isOfType((igMetaObject *)(self->_msgType));
}

