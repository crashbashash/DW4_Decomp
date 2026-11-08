struct igResult { int w0; igResult() {} igResult(const igResult &o) { w0 = o.w0; } bool operator==(const igResult &o) const { return w0 == o.w0; } };
extern "C" {
extern char _ctype_[];
extern char DAT_004d3d11[];
extern char DAT_004f95c0[];
extern char DAT_004fb198[];
extern char DAT_004fb1a0[];
extern igResult DAT_004fb410;
int sscanf(char *, char *, int);
int strncmp(char *, char *, int);
char *strstr(char *, char *);
igResult igMetaEnum_GetValueByName(void *, char *, int);
int strlen(char *);
void strncpy(char *, char *, int);
}
static inline bool sameChar(int a, int b) { return (char)a == (char)b; }
static inline int isSpaceChar(char c) { return _ctype_[c + 1] & 8; }
extern "C" int FUN_00307200(char *text, int value, void *meta, char *format) {
    char buffer[260];
    char *end;
    int length;
    char *token;
    char *f;
    char *s;
    f = format;
    s = text;
    end = text + strlen(text);
    while (!(!*s) && isSpaceChar(*s)) {
        s++;
    }
    while (!(!*s) && *f != 0 && sameChar(*s, *f)) {
        s++;
        f++;
    }
    if (*f == '%') {
        f++;
        if (*f == 's') {
            f++;
        }
    }
    if (*f != 0) {
        char *found = strstr(s, f);
        if (found != 0) {
            end = found;
        } else {
            return 0;
        }
    }
    if (DAT_004d3d11[*s] & 4) {
        if (strncmp(text, DAT_004fb198, 2) == 0) {
            if (sscanf(text, DAT_004fb1a0, value) == 1) {
                return 1;
            }
        } else if (sscanf(text, DAT_004f95c0, value) == 1) {
            return 1;
        }
    } else {
        token = s;
        while (!(!*s) && !isSpaceChar(*s) && s < end) {
            s++;
        }
        if (*token != 0) {
            length = s - token;
            if (length > 255) {
                length = 255;
            }
            strncpy(buffer, token, length);
            buffer[length] = 0;
            if (igMetaEnum_GetValueByName(meta, buffer, value) == DAT_004fb410) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}
