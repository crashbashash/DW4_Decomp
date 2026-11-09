typedef struct {
    unsigned int lsn;
    unsigned int size;
    char name[16];
    unsigned char date[8];
    char pad32[16];
} CdFile;

typedef struct {
    unsigned char trycount;
    unsigned char spindlctrl;
    unsigned char datapattern;
    unsigned char pad;
} CdReadMode;

extern char DAT_004ab558[];
extern char DAT_004f03e0[];
void *memcpy(void *dst, const void *src, unsigned int n);
void *memset(void *dst, int value, unsigned int size);
int strcasecmp(const char *a, const char *b);
int FUN_002765e0(const char *name, void *buf);
void FUN_002745c0(const char *name, char *path);
void FUN_002725a0(int mark);
int FUN_00116c80(int mode);
int FUN_002739e8(CdFile *file, const char *path);
int FUN_00117690(unsigned int lsn, unsigned int sectors, void *buf, CdReadMode *mode);

int FUN_00274928(const char *path, void *buf)
{
    CdFile file;
    CdReadMode mode;
    char dev[5];

    memcpy(dev, path, 5);
    dev[4] = 0;
    if (strcasecmp(dev, DAT_004f03e0) == 0) {
        return FUN_002765e0(path + 4, buf);
    }
    memset(DAT_004ab558, 0, 128);
    FUN_002745c0(path, DAT_004ab558);
    FUN_002725a0(0x9000);
    while (FUN_00116c80(1) == 1) {
    }
    FUN_002725a0(0x9001);
    FUN_002725a0(0x9100);
    if (FUN_002739e8(&file, DAT_004ab558) == 0) {
        FUN_002725a0(0x9101);
        return 0;
    }
    FUN_002725a0(0x9102);
    mode.trycount = 0;
    mode.spindlctrl = 1;
    mode.datapattern = 0;
    mode.pad = 0;
    FUN_002725a0(0x9200);
    if (FUN_00117690(file.lsn, 2, buf, &mode) == 0) {
        FUN_002725a0(0x9201);
        return 0;
    }
    FUN_002725a0(0x9202);
    FUN_002725a0(0x9300);
    while (FUN_00116c80(1) == 1) {
    }
    FUN_002725a0(0x9301);
    return 1;
}
