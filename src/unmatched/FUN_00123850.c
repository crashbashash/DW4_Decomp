/* 0x00123850 — FUN_00123850 (88 bytes). Reentrant wrapper: clears the global errno, calls FUN_0010b5c8 and copies errno into the reent block when the call fails (newlib _r wrapper shape; name is a hypothesis). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Reent {
    int errorNumber;
} Reent;

int FUN_0010b5c8(int fd);
extern int DAT_0058d244;

int FUN_00123850(Reent *reent, int fd) {
    int result;

    DAT_0058d244 = 0;
    if ((result = FUN_0010b5c8(fd)) == -1 && DAT_0058d244 != 0) {
        reent->errorNumber = DAT_0058d244;
    }
    return result;
}
