/* Registers the FUN_0029c8d0 callback (slot 2) and sets handle option 15 to 2. */
extern void FUN_0029c8d0(void);
extern int FUN_002af060(void *handle, void (*callback)(void), int slot);
extern int FUN_002ada78(void *handle, int option, int value);

void FUN_0029c890(void *handle) {
    FUN_002af060(handle, FUN_0029c8d0, 2);
    FUN_002ada78(handle, 15, 2);
}
