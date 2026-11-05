/* 0x002a1770 — FUN_002a1770 (96 bytes). Reports whether position has reached f8 + f12 of the source's FUN_002a17d0 status (0 while f16/f20 are pending and f0 is clear). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Status2a1770 {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
};
struct Status2a1770 *FUN_002a17d0();

/* Returns whether position equals f8 + f12 of the FUN_002a17d0 status (0 while f16/f20 are pending and f0 is clear). */
int FUN_002a1770(void *source, int position) {
    struct Status2a1770 *status = FUN_002a17d0(source);

    if (status->f0 == 0 && (status->f16 != 0 || status->f20 != 0)) {
        return 0;
    }
    return position == status->f8 + status->f12;
}
