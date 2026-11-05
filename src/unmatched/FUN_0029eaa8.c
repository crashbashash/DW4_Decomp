/* 0x0029eaa8 — FUN_0029eaa8 (40 bytes). Fills a status block through FUN_0029dd98 and returns the sum of its words 1 and 3. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdStatus {
    int f0;
    int f4;
    int f8;
    int f12;
    int pad16[4];
} SfdStatus;

extern void FUN_0029dd98(void *handle, int index, SfdStatus *status);

int FUN_0029eaa8(void *handle, int index) {
    SfdStatus status;

    FUN_0029dd98(handle, index, &status);
    return status.f4 + status.f12;
}
