typedef struct DvciList {
    int w0, w4;
    int count;
    int nameLen;
} DvciList;

extern DvciList D_004ab430;
extern char DAT_0056e780[];
extern char DAT_004f04d0[];
extern char DAT_004f0500[];
extern char DAT_004f0530[];
extern char DAT_004f0558[];
void *memset(void *dst, int value, unsigned int size);
void FUN_00274d08(void);
int FUN_00274928(const char *path, char *text);
int FUN_00274790(char *buf, const char *text, int textlen, int n, int nameLen);
int FUN_00274ab0(char *buf, int n);
void FUN_00265928(const char *format, ...);
void FUN_002739b8(int detail, const char *message);

int FUN_00274f10(const char *path, char *buf, unsigned int size, int nameLen)
{
    int n;
    int found;

    memset(DAT_0056e780, 0, 4096);
    if (D_004ab430.w0 != 0) {
        FUN_00274d08();
    }
    if (path == 0 || buf == 0 || size == 0) {
        FUN_00274d08();
    }
    if (path == 0) {
        return 0;
    }
    if (buf == 0) {
        FUN_00265928(DAT_004f04d0, 0);
        return 0;
    }
    if (size == 0) {
        FUN_00265928(DAT_004f0500, 0);
        return 0;
    }
    memset(buf, 0, size);
    if (FUN_00274928(path, DAT_0056e780) == 0) {
        FUN_00265928(DAT_004f0530, path);
        FUN_002739b8(0, DAT_004f0558);
        return 0;
    }
    n = FUN_00274790(buf, DAT_0056e780, 4096, size / (nameLen + 9), nameLen);
    found = FUN_00274ab0(buf, n);
    return size / (nameLen + 9) * 8 + found * (nameLen + 1);
}
