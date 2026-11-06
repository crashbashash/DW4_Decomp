/* Reentrant wrapper: clears the global errno, calls FUN_0010b6b8 and copies errno into the reent
 * block when the call fails (newlib _r wrapper shape; name is a hypothesis). */
typedef struct Reent {
    int errorNumber;
} Reent;

int FUN_0010b6b8(int a, int b);
extern int DAT_0058d244;

int FUN_00129c28(Reent *reent, int a, int b) {
    int result;

    DAT_0058d244 = 0;
    if ((result = FUN_0010b6b8(a, b)) == -1 && DAT_0058d244 != 0) {
        reent->errorNumber = DAT_0058d244;
    }
    return result;
}
