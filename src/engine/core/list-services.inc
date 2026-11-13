int List_AppendWord(igDataList *list, int value) {
    int index = list->_count;
    List_Resize(list, index + 1, 4);
    (*(int **)&list->_data)[index] = value;
}

static inline int countOf(const igDataList *list) { return list->_count; }
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

void List_AppendWords(WordList *arg0, int arg1, int arg2) {
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

