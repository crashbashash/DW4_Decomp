typedef struct {
    char f0;
    signed char stat;
    char pad2[10];
    int size;
    char pad16[4];
    int pos;
} AdxfFile;

extern char DAT_004ede18[];
extern char DAT_004ede40[];
void FUN_00260c20(int id, int kind, void *a0, int a1, int a2);
void FUN_00262118(AdxfFile *f);
void FUN_002607e8(const char *message);

int FUN_002623f8(AdxfFile *f, int ofst, int whence)
{
    FUN_00260c20(6, 0, f, ofst, whence);
    if (f == 0) {
        FUN_002607e8(DAT_004ede18);
        return -3;
    }
    if (f->stat == 2) {
        FUN_00262118(f);
    }
    if (whence == 0) {
        f->pos = ofst;
    } else if (whence == 1) {
        f->pos = f->pos + ofst;
    } else if (whence == 2) {
        f->pos = f->size + ofst;
    } else {
        FUN_002607e8(DAT_004ede40);
        return -3;
    }
    if (f->pos < 0) {
        f->pos = 0;
    } else if (f->size < f->pos) {
        f->pos = f->size;
    }
    FUN_00260c20(6, 1, f, ofst, whence);
    return f->pos;
}
