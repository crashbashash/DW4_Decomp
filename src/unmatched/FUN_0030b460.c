typedef struct IniStringView { char pad[8]; char *text; unsigned int length; } IniStringView;
void FUN_0030b320(IniStringView *, char *, unsigned int);
void FUN_00300f50(IniStringView *, char *);
char *FUN_00300d70(IniStringView *, unsigned int);
void memcpy(void *, const void *, unsigned int);
void FUN_0030b460(IniStringView *self, char *insert, unsigned int at, unsigned int n) {
    unsigned int total;
    char *buf;
    if (n == 0 || insert == 0) { return; }
    if (self->length == 0) {
        FUN_0030b320(self, insert, n);
    } else {
    total = n + self->length;
    buf = FUN_00300d70(self, total + 1);
    if (at >= self->length) {
        memcpy(buf, self->text, self->length);
        memcpy(buf + self->length, insert, n);
        buf[total] = 0;
    } else if (at == 0) {
        memcpy(buf, insert, n);
        memcpy(buf + n, self->text, self->length + 1);
    } else {
        memcpy(buf, self->text, at);
        memcpy(buf + at, insert, n);
        memcpy(buf + (at + n), self->text + at, (self->length - at) + 1);
    }
    if (self->text != 0) {
        FUN_00300f50(self, self->text);
    }
    self->text = buf;
    self->length = total;
    }
}
