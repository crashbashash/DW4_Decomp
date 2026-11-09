struct RefCounted { int pad; int _refCount; };
struct RetainedList { int pad0[2]; void *_words; int pad1[2]; int _count;
};
extern "C" int List_InsertWords(void *list, int at, int n, void *from);
extern "C" void FUN_0023b3b0(RetainedList *list, RefCounted *object) {
    int at = list->_count;
    void *words = list->_words;
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
    List_InsertWords(words, at, 1, &object);
    list->_count = list->_count + 1;
}
