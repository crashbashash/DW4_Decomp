typedef struct {
    char pad0[2];
    signed char stat;
    char pad3[45];
    int fd;
    int err;
} DvCiFile;

void FUN_002725a0(int);
int FUN_00272838(int fd, int mode, int *result);
void FUN_00271940(void);
void FUN_0010d108(const char *format, ...);
extern char DAT_004efc20[];

void FUN_00271998(DvCiFile *f)
{
    int busy;
    int ret;
    int count;

    busy = 1;
    count = 0;
    for (;;) {
        if (busy != 1) {
            return;
        }
        FUN_002725a0(0x1100);
        ret = FUN_00272838(f->fd, 1, &busy);
        FUN_002725a0(0x1101);
        if (ret < 0) {
            f->stat = 9;
            f->err = ret;
            return;
        }
        FUN_00271940();
        if (++count > 0x9000) {
            FUN_0010d108(DAT_004efc20);
            return;
        }
    }
}
