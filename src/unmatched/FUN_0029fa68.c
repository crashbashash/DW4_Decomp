typedef struct {
    unsigned char b[11];
} Hdr29fa68;

extern int DAT_004f4bf0[][16];
extern int DAT_004f4cf0[];
extern int DAT_004f4be0[];
int FUN_0029fbc8(Hdr29fa68 *, int, int);

int FUN_0029fa68(int data, int size) {
    Hdr29fa68 hdr;
    int v;

    if (FUN_0029fbc8(&hdr, data, size) == 0) {
        return -1;
    }
    v = DAT_004f4bf0[hdr.b[0]][hdr.b[2]];
    if (v == -1) {
        return -1;
    }
    return DAT_004f4cf0[hdr.b[0]] * v * 1000 / (DAT_004f4be0[hdr.b[3]] * 8);
}
