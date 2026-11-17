char *igMetaEnum_GetNamesByMask(char *buffer, int size, int mask, int metaEnum) {
    int count;
    int i;
    int written;
    int room;
    written = 0;
    count = igMetaEnum_GetNameCount((igMetaEnum *)metaEnum);
    *buffer = 0;
    i = 0;
    room = size - 1;
    for (; i < count; i++) {
        if (mask & igMetaEnum_GetValueAt((void *)metaEnum, i)) {
            if (written != 0) {
                strncat(buffer, (const char *)text_space, room);
            }
            {
                igStringRef name = igMetaEnum_GetNameAt((igMetaEnum *)metaEnum, i);
                strncat(buffer, name.p, room);
            }
            written++;
        }
    }
    buffer[size - 1] = 0;
    return buffer;
}

char *igMetaEnum_GetValueName(char *buffer, int size, int value, int metaEnum) {
    igStringRef name = igMetaEnum_GetNameByValue((const igMetaEnum *)metaEnum, value);
    strncpy(buffer, name.p, size - 1);
    *(buffer + size - 1) = 0;
    return buffer;
}

