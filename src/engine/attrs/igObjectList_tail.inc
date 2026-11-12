void igObjectList_TrimCapacity(igObjectList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        List_Reserve(self, count, 4);
    }
}

