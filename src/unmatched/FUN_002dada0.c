int FUN_002dada0(void *self, char **cursor, char *out, int size) {
    int i = 0;
    int limit;
    int c = *(*cursor)++;
    while (c != '\n' && c != '\r' && c != 0) {
        if (i < size - 2) {
            out[i] = c;
        }
        i++;
        c = *(*cursor)++;
    }
    limit = size - 2;
    if (i > limit) {
        i = limit;
    }
    out[i] = '\n';
    out[i + 1] = 0;
    return i > 0 || c != 0;
}
