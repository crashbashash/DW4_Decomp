void igFolder_ListFiles(void **result) {
    void *list;

    *result = 0;
    list = *result;
    if (list != 0) {
        ((igObject *)list)->_refCount = (int) (((igObject *)list)->_refCount + 1);
    }
}

