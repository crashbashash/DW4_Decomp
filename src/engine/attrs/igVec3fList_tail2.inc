void igVec3fList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 0xC);
    }
}
