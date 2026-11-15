typedef struct {
    short inter;
    short omode;
    short ffmode;
    unsigned short version;
    int vsync_set;
    int vsync_id;
} GsGParam;

#define GS_CSR (*(volatile unsigned long long *)0x12001000)
#define GS_CSR_FIELD 13

GsGParam *sceGsGetGParam(void);
void VSync(void);
long long VSync2(void);

int sceGsSyncV(void)
{
    GsGParam *g = sceGsGetGParam();
    long long field;

    if (g->vsync_set == 0) {
        VSync();
        if (g->inter != 1) return 1;
        return (GS_CSR >> GS_CSR_FIELD) & 1;
    }
    field = (VSync2() >> GS_CSR_FIELD) & 1;
    if (g->inter != 1) return 1;
    return field;
}
