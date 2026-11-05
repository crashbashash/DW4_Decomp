/* 0x0029ead0 — FUN_0029ead0 (40 bytes). Fills a status block through FUN_0029dd80 and returns the sum of its words 1 and 3. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdStatus {
    int f0;
    int f4;
    int f8;
    int f12;
    int pad16[4];
} SfdStatus;

extern void FUN_0029dd80(void *handle, int index, SfdStatus *status);

int FUN_0029ead0(void *handle, int index) {
    SfdStatus status;

    FUN_0029dd80(handle, index, &status);
    return status.f4 + status.f12;
}
