/* 0x00273c60 — FUN_00273c60 (136 bytes). Reads an object's status (FUN_00274e30); when its busy word (+4) is clear, refreshes it into DAT_004ab300 (FUN_002745c0) between the 0x8100/0x8101 FUN_002725a0 markers around FUN_00116c80(0), and returns FUN_002739e8's verdict on the pair; returns 1 when busy and 0 for a NULL object. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Status_273c60 {
    int f0;
    int busy;       /* 0x04 */
    int pad8[10];
} Status_273c60;    /* 0x30 bytes */

extern char DAT_004ab300[];
int FUN_00274e30(void *obj, Status_273c60 *status);
void FUN_002745c0(void *obj, char *work);
void FUN_002725a0(int marker);
void FUN_00116c80(int arg);
int FUN_002739e8(Status_273c60 *status, char *work);

int FUN_00273c60(void *obj) {
    Status_273c60 status;

    if (obj == 0) {
        return 0;
    }
    FUN_00274e30(obj, &status);
    if (status.busy == 0) {
        FUN_002745c0(obj, DAT_004ab300);
        FUN_002725a0(0x8100);
        FUN_00116c80(0);
        FUN_002725a0(0x8101);
        if (FUN_002739e8(&status, DAT_004ab300) == 0) {
            return 0;
        }
    }
    return 1;
}

