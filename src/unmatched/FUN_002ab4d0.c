/* 0x002ab4d0 — FUN_002ab4d0 (200 bytes). With a request pending, combines the FUN_002b03d0 checks 6 and 7 according to the mode in slot 25 (0 both, 1 check 7, 2 check 6, 3 either); returns 1 when nothing is pending. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b03d0(int obj, int code);
int FUN_002adc40(int obj, int slot);

struct PendingPair {
    char pad0[20];
    int request1; /* +20 */
    int request2; /* +24 */
};

int FUN_002ab4d0(int obj) {
    struct PendingPair *pending = (struct PendingPair *)(obj + 0xA04);
    int check6;
    int check7;
    unsigned int mode;
    int result;

    if (pending->request2 == 0 && pending->request1 == 0) {
        return 1;
    }
    check6 = FUN_002b03d0(obj, 6);
    check7 = FUN_002b03d0(obj, 7);
    mode = FUN_002adc40(obj, 25);
    result = 0;
    switch (mode) {
    case 0:
        result = check7 & check6;
        break;
    case 1:
        result = check7;
        break;
    case 2:
        result = check6;
        break;
    case 3:
        result = check7 | check6;
        break;
    }
    return result;
}
