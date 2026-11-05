/* 0x00129828 — FUN_00129828 (88 bytes). Reentrant wrapper: clears the global errno, calls FUN_0010b5e0 and copies errno into the reent block when the call fails (newlib _r wrapper shape; name is a hypothesis). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Reent {
    int errorNumber;
} Reent;

int FUN_0010b5e0(int fd);
extern int DAT_0058d244;

int FUN_00129828(Reent *reent, int fd) {
    int result;

    DAT_0058d244 = 0;
    if ((result = FUN_0010b5e0(fd)) == -1 && DAT_0058d244 != 0) {
        reent->errorNumber = DAT_0058d244;
    }
    return result;
}
