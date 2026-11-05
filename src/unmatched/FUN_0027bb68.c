/* 0x0027bb68 — FUN_0027bb68 (192 bytes). Grants a request against a handle: mode 0 grants nothing, mode 1 grants min(request, available (+12)), any other mode is reported to the error callback (+28, object +32, code -3). Stores the grant and returns 1 when it equals the request; a NULL or unused (+4 clear) handle is reported through FUN_0027b2e0 and returns 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Handle_27bb68 {
    int pad0;
    int used;                                   /* 0x04 */
    int pad8;
    int available;                              /* 0x0c */
    char pad16[12];
    void (*error)(int object, int code);        /* 0x1c */
    int error_object;                           /* 0x20 */
} Handle_27bb68;

extern char s_E2004090247_NULL_pointer_is_specified_004f1d18[];   /* 'E2004090247 : NULL pointer is specified.' */
extern char s_E2004090248_Specified_handle_is_invalid_004f1d48[]; /* 'E2004090248 : Specified handle is invalid.' */
int FUN_0027b2e0(const char *message);

int FUN_0027bb68(Handle_27bb68 *handle, int mode, int request, int *granted) {
    int amount;

    if (handle == 0) {
        FUN_0027b2e0(s_E2004090247_NULL_pointer_is_specified_004f1d18);
        return 0;
    }
    if (handle->used == 0) {
        FUN_0027b2e0(s_E2004090248_Specified_handle_is_invalid_004f1d48);
        return 0;
    }
    switch (mode) {
    case 0:
        amount = 0;
        break;
    case 1:
        amount = handle->available < request ? handle->available : request;
        break;
    default:
        amount = 0;
        if (handle->error != 0) {
            handle->error(handle->error_object, -3);
        }
        break;
    }
    *granted = amount;
    return amount == request;
}

