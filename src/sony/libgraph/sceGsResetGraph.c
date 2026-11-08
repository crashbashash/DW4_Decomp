typedef struct {
    short inter;
    short omode;
    short ffmode;
    unsigned short version;
    int vsync_set;
    int vsync_id;
} GsGParam;
GsGParam *FUN_00102b88(void);
int FUN_0010b9c0(int cause);
int GsPutIMR(unsigned long long imr);
int RemoveIntcHandler(int cause, int id);
void SetGsCrt(short interlace, short omode, short ffmd);
void sceGsResetGraph(short mode, short inter, short omode, short ffmode) {
    GsGParam *gp;

    switch (mode) {
    case 0:
        gp = FUN_00102b88();
        *(volatile unsigned long long *)0x12001000 = 0x200;
        gp->inter = inter;
        gp->omode = omode;
        gp->version = (*(volatile unsigned long long *)0x12001000 >> 16) & 0xFF;
        GsPutIMR(0xFF00);
        gp->ffmode = ffmode ? 1 : 0;
        if (gp->vsync_set) {
            FUN_0010b9c0(2);
            RemoveIntcHandler(2, gp->vsync_id);
            gp->vsync_set = 0;
            gp->vsync_id = 0;
        }
        SetGsCrt(inter & 1, omode & 0xFF, ffmode & 1);
        break;
    case 1:
        *(volatile unsigned long long *)0x12001000 = 0x100;
        break;
    case 5:
        gp = FUN_00102b88();
        gp->ffmode = ffmode ? 1 : 0;
        gp->inter = inter;
        gp->omode = omode;
        gp->version = (*(volatile unsigned long long *)0x12001000 >> 16) & 0xFF;
        SetGsCrt(inter & 1, omode & 0xFF, ffmode & 1);
        break;
    }
}
