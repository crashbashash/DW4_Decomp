typedef struct {
    int f[5];
} Cfg2a0d10;

typedef struct {
    char pad0[412];
    Cfg2a0d10 cfg;
} Global2a0d10;

extern Global2a0d10 DAT_004be8d8;
int sfd_CheckHn(void *);
int sfd_ReportError(int, int);

int FUN_002a0d10(char *obj, Cfg2a0d10 *out) {
    if (obj == 0) {
        *out = DAT_004be8d8.cfg;
    } else {
        if (sfd_CheckHn(obj) != 0) {
            return sfd_ReportError(0, 0xff000102);
        }
        *out = *(Cfg2a0d10 *)(obj + 2544);
    }
    return 0;
}
