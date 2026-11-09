void List_Resize(void *list, int count, int size);
extern int DAT_004c2620;
typedef struct List { int pad[2]; int count; int capacity; int *data; } List;
int *Gap__Core__igPsx2CallStackTracer__vfunc_31(List *list) {
    int index = *(const int *)&list->count;
    if (index < list->capacity) {
        list->count = list->count + 1;
    } else {
        List_Resize(list, index + 1, 4);
    }
    list->data[index] = DAT_004c2620;
    return list->data;
}
