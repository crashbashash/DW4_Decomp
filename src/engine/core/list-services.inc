int List_AppendWord(igDataList *list, int value) {
    int index = list->_count;
    List_Resize(list, index + 1, 4);
    (*(int **)&list->_data)[index] = value;
}

extern "C" void List_InsertWords(igDataList *list, int index, int count, const void *src) {
    int oldCount;
    int newCount;
    int *at;
    int *dst;
    int tail;
    if (index < 0 || index > countOf(list)) {
        return;
    }
    if (count >= 0 && count != 0) {
        oldCount = list->_count;
        newCount = oldCount + count;
        if (newCount <= list->_capacity) { list->_count = newCount; } else { List_Resize(list, newCount, 4); }
        at = (int *)list->_data + index;
        count *= sizeof(int);
        dst = (int *)((char *)at + count);
        tail = oldCount - index;
        if (tail != 0) {
            memmove(dst, at, tail * sizeof(int));
        }
        memcpy(at, src, count);
    }
}

void List_AppendWords(igDataList *list, int count, const int *words) {
    int newCount;
    int oldCount;

    if ((count >= 0) && (count != 0)) {
        oldCount = list->_count;
        newCount = oldCount + count;
        if (newCount <= list->_capacity) {
            list->_count = newCount;
        } else {
            List_Resize(list, newCount, 4);
        }
        memcpy((int *)list->_data + oldCount, words, count * 4);
    }
}

