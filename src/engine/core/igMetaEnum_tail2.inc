char *igMetaEnum_GetNamesByMask(char *buffer, int size, int mask, int metaEnum) {
    int *name;
    int *hdr;
    int count;
    int i;
    int written;
    int room;
    int refs;
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
            igMetaEnum_GetNameAt((int *)&name, (void *)metaEnum, i);
            strncat(buffer, (const char *)name, room);
            if (name != 0) {
                hdr = name - 2;
                refs = name[-1] - 1;
                name[-1] = refs;
                if (refs == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)(*hdr), (int)hdr);
                }
            }
            written++;
        }
    }
    buffer[size - 1] = 0;
    return buffer;
}

char *igMetaEnum_GetValueName(char *buffer, int size, int value, int metaEnum) {
    int *name;
    int *hdr;
    int refs;

    igMetaEnum_GetNameByValue((int *)&name, (const igMetaEnum *)metaEnum, value);
    strncpy(buffer, name, size - 1);
    *(buffer + size - 1) = 0;
    if (name != 0) {
        hdr = name - 2;
        refs = name[-1] - 1;
        name[-1] = refs;
        if (refs == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*hdr), (int)hdr);
        }
    }
    return buffer;
}

