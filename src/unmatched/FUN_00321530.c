char *strncpy(char *, const char *, int);
char *strchr(char *, int);
void *memcpy(void *, const void *, int);
int strlen(const char *);
void FUN_00321530(const char *in, char *out, int size) {
    char *cursor = (char *)in;
    char inner[256];
    int pointers = 0;
    int copy;
    int parts;
    int length;
    int advance;
    int limit;
    int c;
    char *open;
    while ((c = *cursor) != 0) {
        char kind = c;
        if (kind == 'P') {
            cursor++;
            pointers++;
        } else if (kind == 'Q') {
            cursor++;
            parts = *cursor - '0';
            if (parts > 0 && parts < 10) {
                cursor++;
                while (parts-- != 0) {
                    length = 0;
                    while ((c = *cursor) >= '0' && c <= 57) {
                        length = c - '0' + length * 10;
                        cursor++;
                    }
                    limit = size - 1;
                    copy = length;
                    if (copy > limit) {
                        copy = limit;
                    }
                    strncpy(out, cursor, copy);
                    out[copy] = 0;
                    open = strchr(out, '<');
                    if (open != 0) {
                        length = open - out;
                        memcpy(inner, open + 1, copy + 1 - length);
                        advance = length + 1;
                        if (advance > 254) {
                            advance = 254;
                        }
                        if (advance > size) {
                            advance = size;
                        }
                        out += advance;
                        size -= advance;
                        *out = 0;
                        FUN_00321530(inner, out, size);
                        advance = strlen(out);
                        size -= advance;
                        out += advance;
                        if (size > 1) {
                            *out = '>';
                            size--;
                            out++;
                        }
                        if (size > 1) {
                            *out = 0;
                            size--;
                            out++;
                        }
                    } else {
                        cursor += length;
                        out += copy;
                        size -= copy;
                    }
                    if (parts != 0 && size > 2) {
                        size -= 2;
                        out[0] = ':';
                        out[1] = ':';
                        out += 2;
                    }
                }
            }
            while (((pointers != 0) ^ 1) == 0 && size > 1) {
                *out = '*';
                size--;
                pointers--;
                out++;
                *out = 0;
            }
            continue;
        } else {
            cursor++;
        }
    }
    *out = 0;
}
