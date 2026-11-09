unsigned int strlen(const char *s);
void FUN_00267580(const char *text, int length, unsigned short *a, unsigned short *b, unsigned short *c);

typedef struct VersionHolder {
    char pad0[720];
    unsigned short major;
    unsigned short minor;
    unsigned short patch;
} VersionHolder;

void FUN_002698d8(VersionHolder *self, const char *text) {
    unsigned short a, b, c;
    FUN_00267580(text, strlen(text), &a, &b, &c);
    self->major = a;
    self->minor = b;
    self->patch = c;
}
