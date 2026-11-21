char *igMetaEnum_GetNamesByMask(char *buffer, int size, int mask, int metaEnum) {
    int count;
    int i;
    int written;
    int room;
    written = 0;
    count = ((Gap::Core::igMetaEnum *)metaEnum)->getEnumCount();
    *buffer = 0;
    i = 0;
    room = size - 1;
    for (; i < count; i++) {
        if (mask & ((Gap::Core::igMetaEnum *)metaEnum)->getIndexedEnumValue(i)) {
            if (written != 0) {
                strncat(buffer, (const char *)text_space, room);
            }
            {
                igStringRef name = ((Gap::Core::igMetaEnum *)metaEnum)->getIndexedEnumName(i);
                strncat(buffer, name.p, room);
            }
            written++;
        }
    }
    buffer[size - 1] = 0;
    return buffer;
}

char *igMetaEnum_GetValueName(char *buffer, int size, int value, int metaEnum) {
    igStringRef name = ((Gap::Core::igMetaEnum *)((const igMetaEnum *)metaEnum))->getEnumName(value);
    strncpy(buffer, name.p, size - 1);
    *(buffer + size - 1) = 0;
    return buffer;
}

