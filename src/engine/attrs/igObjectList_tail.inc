void igObjectList_TrimCapacity(igObjectList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        ((Gap::Core::igDataList *)self)->setCapacity(count, 4);
    }
}

