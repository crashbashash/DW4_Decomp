typedef struct {
    short inter;
    short omode;
    short ffmode;
    unsigned short version;
    int vsync_set;
    int vsync_id;
} GsGParam;

#define GS_CSR (*(volatile unsigned long long *)0x12001000)
#define GS_CSR_RESET 0x200
#define GS_CSR_FLUSH 0x100
#define INTC_VBLANK_START 2

int DisableIntc(int cause);
int RemoveIntcHandler(int cause, int id);
int GsPutIMR(unsigned long long imr);
void SetGsCrt(short interlace, short omode, short ffmode);
GsGParam *sceGsGetGParam(void);

static char __ps2_libinfo__[16] = "PsIIlibgraph2800";

static GsGParam gp = {1, 2, 1, 3, 0, 0};

void sceGsResetGraph(short mode, short inter, short omode, short ffmode)
{
    GsGParam *g;

    switch (mode) {
    case 0:
        g = sceGsGetGParam();
        GS_CSR = GS_CSR_RESET;
        g->inter = inter;
        g->omode = omode;
        g->version = (GS_CSR >> 16) & 0xff;
        GsPutIMR(0xff00);
        g->ffmode = ffmode ? 1 : 0;
        if (g->vsync_set) {
            DisableIntc(INTC_VBLANK_START);
            RemoveIntcHandler(INTC_VBLANK_START, g->vsync_id);
            g->vsync_set = 0;
            g->vsync_id = 0;
        }
        SetGsCrt(inter & 1, omode & 0xff, ffmode & 1);
        break;
    case 1:
        GS_CSR = GS_CSR_FLUSH;
        break;
    case 5:
        g = sceGsGetGParam();
        g->ffmode = ffmode ? 1 : 0;
        g->inter = inter;
        g->omode = omode;
        g->version = (GS_CSR >> 16) & 0xff;
        SetGsCrt(inter & 1, omode & 0xff, ffmode & 1);
        break;
    }
}

GsGParam *sceGsGetGParam(void)
{
    return &gp;
}
