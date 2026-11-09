typedef struct {
    char pad0[2];
    signed char stat;
    char pad3[17];
    int f20;
    char pad24[4];
    int req;
} CriDvCiHandle;

extern char DAT_004f0348[];
extern char DAT_004f03a8[];
void FUN_002739b8(int a0, const char *message);
void FUN_00271b98(int req);
void FUN_00272118(void);
void FUN_00273b58(void);
int FUN_00274330(CriDvCiHandle *h);
void FUN_002659a0(const char *format, ...);

void FUN_00274248(CriDvCiHandle *h)
{
    int i;

    i = 0;
    if (h == 0) {
        FUN_002739b8(0, DAT_004f0348);
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
        FUN_00273b58();
        FUN_00274330(h);
        if (h->stat != 2) {
            break;
        }
        if (++i > 0x9ffff) {
            FUN_002659a0(DAT_004f03a8);
            break;
        }
    }
    h->stat = 0;
    h->f20 = 0;
}
