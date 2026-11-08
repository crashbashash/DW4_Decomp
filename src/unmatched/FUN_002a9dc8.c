extern void *memcpy(void *d, const void *s, unsigned int n);
int FUN_002a9dc8(char *buf, int size, char *dst, int cap, char *src, int pos, char *data, int len) {
    int end = pos + len;
    int r = 0;
    if (size + cap >= end) {
        if (pos >= size) {
            memcpy(buf, src, size);
            memcpy(dst, src + size, pos - size);
            memcpy(dst + pos - size, data, len);
        } else {
            int room = size - pos;
            if (len >= room) {
                memcpy(buf, src, pos);
                memcpy(buf + pos, data, room);
                memcpy(dst, data + size - pos, len - room);
            } else {
                memcpy(buf, src, pos);
                memcpy(buf + pos, data, len);
            }
        }
        r = end;
    }
    return r;
}
