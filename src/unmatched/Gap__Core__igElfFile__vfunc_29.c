typedef struct ElfOperatorName { const char *mangled; const char *name; } ElfOperatorName;
extern ElfOperatorName DAT_004c2380[];
extern int DAT_004fb410;
extern char DAT_004fdf80[];
extern char DAT_004fde68[];
extern char DAT_004fde70[];
char *strstr(const char *, const char *);
char *strncpy(char *, const char *, int);
char *strchr(char *, int);
void *memcpy(void *, const void *, int);
int strlen(const char *);
int strncmp(const char *, const char *, int);
void FUN_00321530(const char *, char *, int);
void Gap__Core__igElfFile__vfunc_29(int *result, void *self, char *mangled, char *out, int size) {
    char inner[256];
    char *start;
    char *sep;
    char *open;
    int parts;
    int c;
    int length;
    int copy;
    int limit;
    int advance;
    int nameLength;
    char *scan;
    int i;
    char *tail;
    sep = strstr(*mangled != 0 ? mangled + 1 : mangled, DAT_004fdf80);
    start = out;
    if (sep != 0) {
        nameLength = sep - mangled;
    } else {
        nameLength = strlen(mangled);
        if (nameLength > size - 1) {
            nameLength = size - 1;
        }
        strncpy(out, mangled, nameLength);
        out[nameLength] = 0;
        *result = DAT_004fb410;
        return;
    }
    if (sep[2] == 'Q') {
        sep += 2;
        sep++;
        parts = *sep - '0';
        if (parts > 0 && parts < 10) {
            sep++;
            while (parts-- != 0) {
                length = 0;
                while ((c = *sep) >= '0' && c <= 57) {
                    length = c - '0' + length * 10;
                    sep++;
                }
                limit = size - 1;
                copy = length;
                if (copy > limit) {
                    copy = limit;
                }
                strncpy(out, sep, copy);
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
                    sep += length;
                    out += copy;
                    size -= copy;
                }
                if (size > 2) {
                    size -= 2;
                    out[0] = ':';
                    out[1] = ':';
                    out += 2;
                }
            }
        }
    }
    *out = 0;
    tail = out - 1;
    if (strncmp(mangled, DAT_004fdf80, 2) == 0) {
        while (((start < tail) ^ 1) == 0 && *tail == ':') {
            tail--;
        }
        scan = tail;
        if (*tail != 0) {
            tail++;
        }
        while (((start < scan) ^ 1) == 0 && *scan != ':') {
            scan--;
        }
        if (*scan == ':') {
            scan++;
        }
        if (strncmp(mangled, DAT_004fde68, nameLength) == 0) {
            nameLength = tail - scan;
            if (nameLength > size - 1) {
                nameLength = size - 1;
            }
            strncpy(out, scan, nameLength);
            out[nameLength] = 0;
            *result = DAT_004fb410;
            return;
        }
        if (strncmp(mangled, DAT_004fde70, nameLength) == 0) {
            nameLength = tail - scan;
            if (size > 0) {
                *out = '~';
                size--;
                out++;
            }
            if (nameLength > size - 1) {
                nameLength = size - 1;
            }
            strncpy(out, scan, nameLength);
            out[nameLength] = 0;
            *result = DAT_004fb410;
            return;
        }
        for (i = 0; DAT_004c2380[i].mangled != 0; i++) {
            if (strncmp(DAT_004c2380[i].mangled, mangled, nameLength) == 0 && DAT_004c2380[i].name != 0) {
                nameLength = strlen(DAT_004c2380[i].name);
                if (nameLength > size - 1) {
                    nameLength = size - 1;
                }
                strncpy(out, DAT_004c2380[i].name, nameLength);
                out[nameLength] = 0;
                *result = DAT_004fb410;
                return;
            }
        }
    }
    if (nameLength > size - 1) {
        nameLength = size - 1;
    }
    strncpy(out, mangled, nameLength);
    out[nameLength] = 0;
    *result = DAT_004fb410;
}
