typedef struct MwsfdHandle {
    char pad0[476];
    int f476;
} MwsfdHandle;

void FUN_00296818(MwsfdHandle *h, int a, int b);

void FUN_00295ab8(MwsfdHandle *h)
{
    int n = h->f476;

    FUN_00296818(h, n * 0.8, n);
}
