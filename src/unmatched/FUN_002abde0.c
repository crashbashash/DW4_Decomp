/* Validates the handle, picks FUN_002aa538 or FUN_002abe60 by option 47, then sets +68. */
typedef struct SfdHandle {
    char pad0[68];
    int f68;                /* +68 */
} SfdHandle;

extern int FUN_002a0dd8(SfdHandle *handle);
extern int FUN_002a0bb8(SfdHandle *handle, int code);
extern int FUN_002adc40(SfdHandle *handle, int option);
extern void FUN_002aa538(SfdHandle *handle);
extern void FUN_002abe60(SfdHandle *handle);

int FUN_002abde0(SfdHandle *handle) {
    if (FUN_002a0dd8(handle) != 0) {
        return FUN_002a0bb8(0, 0xFF000132);
    }
    if (FUN_002adc40(handle, 47) == 1) {
        FUN_002aa538(handle);
    } else {
        FUN_002abe60(handle);
    }
    handle->f68 = 1;
}
