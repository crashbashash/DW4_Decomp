int List_AppendWord(igDataList *list, int value) {
    int index = list->_count;
    List_Resize(list, index + 1, 4);
    (*(int **)&list->_data)[index] = value;
}

void List_AppendWords(L_2d6c60 *arg0, int arg1, int arg2) {
    int temp_a1;
    int temp_s0;

    if ((arg1 >= 0) && (arg1 != 0)) {
        temp_s0 = arg0->count;
        temp_a1 = temp_s0 + arg1;
        if (temp_a1 <= arg0->cap) {
            arg0->count = temp_a1;
        } else {
            List_Resize(arg0, temp_a1, 4);
        }
        memcpy(arg0->data + temp_s0, arg2, arg1 * 4);
    }
}

