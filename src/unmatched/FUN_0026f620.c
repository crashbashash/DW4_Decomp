typedef struct {
    void *pad0[5];
    void (*close)(int fd);
} CvFsVtbl;

typedef struct {
    CvFsVtbl *vt;
    int fd;
} CvFsHandle;

typedef struct {
    int value;
    char name[12];
} NameEntry;

extern int DAT_004a9284;
extern CvFsHandle DAT_0056e0e0[40];
extern NameEntry DAT_0056e220[32];
extern char DAT_0056e420[9];
int memset();

void FUN_0026f620(void)
{
    int i;

    if (--DAT_004a9284 != 0) {
        return;
    }
    for (i = 0; i < 40; i++) {
        if (DAT_0056e0e0[i].vt != 0) {
            DAT_0056e0e0[i].vt->close(DAT_0056e0e0[i].fd);
        }
        DAT_0056e0e0[i].vt = 0;
        DAT_0056e0e0[i].fd = 0;
    }
    for (i = 31; i >= 0; i--) {
        DAT_0056e220[i].name[0] = 0;
    }
    memset(DAT_0056e420, 0, sizeof(DAT_0056e420));
    DAT_0056e420[0] = 0;
}
