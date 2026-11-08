/* Reentrant wrapper: clears the global errno, calls sbrk and copies errno into the reent
 * block when the call fails. */
typedef struct Reent {
    int errorNumber;
} Reent;

int sbrk(int fd);
extern int DAT_0058d244;

int FUN_00129828(Reent *reent, int fd) {
    int result;

    DAT_0058d244 = 0;
    if ((result = sbrk(fd)) == -1 && DAT_0058d244 != 0) {
        reent->errorNumber = DAT_0058d244;
    }
    return result;
}
