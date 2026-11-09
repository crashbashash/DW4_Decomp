typedef struct {
    char pad0[2];
    signed char stat;
    char pad3[37];
    int f40;
    int req;
} CriDvCiHandle;

extern char DAT_004f08b0[];
extern char DAT_004f08c8[];
void FUN_002753d8(int a0, const char *message);
void FUN_00271b98(int req);
void FUN_00272118(void);
void FUN_002755e8(void);
void FUN_002753a8(void);
int FUN_00275f48(CriDvCiHandle *h);
void FUN_002659a0(const char *format, ...);

void FUN_00275e50(CriDvCiHandle *h)
{
    int i;

    i = 0;
    if (h == 0) {
        FUN_002753d8(0, DAT_004f08b0);
        return;
    }
    if ((unsigned char)h->stat < 2) {
        return;
    }
    if (h->req != 0) {
        FUN_00271b98(h->req);
    }
    while (1) {
        FUN_00272118();
        FUN_002755e8();
        FUN_00275f48(h);
        if (h->stat != 2) {
            break;
        }
        if (++i > 0x63fff6) {
            FUN_002659a0(DAT_004f08c8);
            break;
        }
        FUN_002753a8();
    }
    h->stat = 0;
    h->f40 = 0;
}
