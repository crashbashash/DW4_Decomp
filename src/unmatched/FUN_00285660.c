/* Once FUN_0028b098 accepts the handle, polls `stream` with FUN_00290898 (advancing with
 * FUN_00290ac0 while it returns 4) until a status in mask 0xCC appears, then reports 0 or
 * 0xFF030305 through FUN_002855d8. */
int FUN_0028b098(void *handle); /* 0 when handle is non-null and in state 2, else -1 */
void FUN_002855d8(void *handle, int error);
int FUN_00290898(void *stream);
int FUN_00290ac0(void *stream, int a, int b);

void FUN_00285660(void *handle, void *stream) {
    int error;
    int status;

    if (FUN_0028b098(handle) != 0) {
        FUN_002855d8(0, 0xFF03020A);
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
    FUN_002855d8(handle, error);
}
