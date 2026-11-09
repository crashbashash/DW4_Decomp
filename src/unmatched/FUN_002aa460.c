typedef struct SofdecHandle { char pad0[76]; int state; } SofdecHandle;

void FUN_002af428(void);
int FUN_002aa4c8(SofdecHandle *h, int arg);

int FUN_002aa460(SofdecHandle *h, int arg) {
    if (h->state != 3 && h->state != 4) {
        return 0;
    }
    FUN_002af428();
    return FUN_002aa4c8(h, arg);
}
