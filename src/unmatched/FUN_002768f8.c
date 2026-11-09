typedef struct {
    int fd;
    int f4;
} HtFile;

typedef struct {
    HtFile *files;
    unsigned int nfiles;
    int nent;
    int namelen;
} HtTable;

extern HtTable DAT_004ab9f0;
extern char DAT_004f0988[];
extern char DAT_004f09b0[];
extern char DAT_004f09d0[];
void FUN_00276220(const char *name, char *path);
void FUN_002725a0(int);
int FUN_00272918(int fd);
void FUN_002659a0(const char *format, ...);
void FUN_00276af0(void);

int FUN_002768f8(void)
{
    char path[256];
    HtFile *files;
    char *name;
    unsigned int i;
    unsigned int n;
    int closed;
    int ret;

    closed = 0;
    files = DAT_004ab9f0.files;
    if (files == 0) {
        return 0;
    }
    n = DAT_004ab9f0.nfiles;
    for (i = 0; i < n; i++) {
        name = (char *)files + (DAT_004ab9f0.nent * 8 + (DAT_004ab9f0.namelen + 1) * i);
        FUN_00276220(name, path);
        if (name[0] == 0) {
            continue;
        }
        FUN_002725a0(0x6900);
        ret = FUN_00272918(files[i].fd);
        FUN_002725a0(0x6901);
        if (ret < 0) {
            FUN_002659a0(DAT_004f0988, path);
        } else {
            FUN_002659a0(DAT_004f09b0, path);
            closed++;
        }
    }
    FUN_002659a0(DAT_004f09d0, closed);
    FUN_00276af0();
    return 1;
}
