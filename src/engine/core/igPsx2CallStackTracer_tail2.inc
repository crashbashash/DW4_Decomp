static inline int n_of_32aed0(const struct S_32aed0 *list) { return list->n; }

int Gap__Core__igPsx2CallStackTracer__vfunc_24(struct S_32aed0 *arg0) {
    int temp_s1;

    temp_s1 = n_of_32aed0(arg0);
    if (temp_s1 < arg0->cap) {
        arg0->n = arg0->n + 1;
    } else {
        List_Resize(arg0, temp_s1 + 1, 4);
    }
    *(int *)((char *)arg0->data + (temp_s1 * 4)) = DAT_004c2618[0];
    return (int)arg0->data;
}

/* J-thunk for igCallStackTracer virtual slot 25, forwarding to the slot body. The callee takes the
 * caller's registers untouched, so the thunk has no arguments of its own. */
void thunk_Gap__Core__igCallStackTracer__vfunc_25(void) {
    Gap__Core__igCallStackTracer__vfunc_25();
}

static inline int count_of_32aed0(const List_32aed0 *list) { return list->count; }

int *Gap__Core__igPsx2CallStackTracer__vfunc_31(List_32aed0 *list) {
    int index = count_of_32aed0(list);
    if (index < list->capacity) {
        list->count = list->count + 1;
    } else {
        List_Resize(list, index + 1, 4);
    }
    list->data[index] = DAT_004c2620;
    return list->data;
}

