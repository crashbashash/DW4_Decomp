/* Once FUN_002913f8 accepts the handle, polls `stream` with FUN_00290898 (advancing with
 * FUN_00290ac0 while it returns 4) until a status in mask 0xCC appears, then reports 0 or
 * 0xFF030305 through FUN_0028eb38. */
int FUN_002913f8(void *handle); /* handle check; non-zero rejects */
void FUN_0028eb38(void *handle, int error);
int FUN_00290898(void *stream);
int FUN_00290ac0(void *stream, int a, int b);

void FUN_0028ed30(void *handle, void *stream) {
    int error;
    int status;

    if (FUN_002913f8(handle) != 0) {
        FUN_0028eb38(0, 0xFF03020A);
        return;
    }
    error = 0xFF030305;
    for (;;) {
        status = FUN_00290898(stream);
        if (status == 0) {
            break;
        }
        if (status & 0xCC) {
            error = 0;
            break;
        }
        if (FUN_00290ac0(stream, 1, 4) != 4) {
            break;
        }
    }
    FUN_0028eb38(handle, error);
}
