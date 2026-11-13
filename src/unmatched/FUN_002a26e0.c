/* Clears options 6 and 5 once their streams (2 and 1) are idle and flags 6/7 allow it. */
typedef struct SfdStatus8052 {
    int f0;
    int f4;                 /* +4 */
    int f8;                 /* +8 */
} SfdStatus8052;

typedef struct SfdHandle {
    char pad0[8052];
    SfdStatus8052 *status;  /* +8052 */
} SfdHandle;

extern int SFD_GetCond(SfdHandle *handle, int option);
extern int FUN_0029e2d0(SfdHandle *handle, int stream);
extern int sftrn_GetFlagA(SfdHandle *handle, int flag);
extern int FUN_002ada78(SfdHandle *handle, int option, int value);

void FUN_002a26e0(SfdHandle *handle) {
    SfdStatus8052 *status = handle->status;

    if (SFD_GetCond(handle, 6) != 0 && SFD_GetCond(handle, 80) != 0) {
        if (FUN_0029e2d0(handle, 2) == 0 && status->f8 == 0) {
            if (sftrn_GetFlagA(handle, 6) != 0) {
                FUN_002ada78(handle, 6, 0);
            }
        }
    }
    if (SFD_GetCond(handle, 5) != 0 && SFD_GetCond(handle, 79) != 0 && FUN_0029e2d0(handle, 1) == 0
        && status->f4 == 0 && sftrn_GetFlagA(handle, 7) != 0) {
        FUN_002ada78(handle, 5, 0);
    }
}
