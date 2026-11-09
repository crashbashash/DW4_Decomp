typedef struct {
    char *files;
    unsigned int nfiles;
    int nent;
    int namelen;
} HtTable;

extern HtTable DAT_004ab9f0;
extern char DAT_0056f780[];
extern char DAT_004f09e8[];
extern char DAT_004f0a18[];
extern char DAT_004f0a48[];
extern char DAT_004f0a70[];
void *memset(void *dst, int value, unsigned int size);
void FUN_00276af0(void);
int FUN_002768f8(void);
int FUN_002765e0(const char *path, char *list);
int FUN_00276440(char *buf, const char *list, int n, int nameLen);
int FUN_00276740(char *buf, int n);
void FUN_00265928(const char *format, ...);
void FUN_002753d8(int detail, const char *message);

int FUN_00276b68(const char *path, char *buf, unsigned int size, int nameLen)
{
    int n;
    int found;
    int stride;

    memset(DAT_0056f780, 0, 4096);
    if (DAT_004ab9f0.files == 0) {
        FUN_00276af0();
    }
    FUN_002768f8();
    if (path == 0) {
        return 0;
    }
    if (buf == 0) {
        FUN_00265928(DAT_004f09e8, 0);
        return 0;
    }
    if (size == 0) {
        FUN_00265928(DAT_004f0a18, 0);
        return 0;
    }
    memset(buf, 0, size);
    if (FUN_002765e0(path, DAT_0056f780) == 0) {
        FUN_00265928(DAT_004f0a48, path);
        FUN_002753d8(0, DAT_004f0a70);
        return 0;
    }
    n = FUN_00276440(buf, DAT_0056f780, size / (nameLen + 9), nameLen);
    stride = nameLen + 1;
    found = FUN_00276740(buf, n);
    return size / (nameLen + 9) * 8 + found * stride;
}
