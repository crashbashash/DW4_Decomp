/* Reads one value through a temporary FUN_002b17d8 handle (FUN_002b19f0, then FUN_002b18a0);
 * returns 0 when unavailable. */
void *FUN_002b17d8();
void FUN_002b18a0();
int FUN_002b19f0();

int FUN_0029fff0(void) {
    void *handle;
    int value;

    handle = FUN_002b17d8();
    if (handle == 0) {
        return 0;
    }
    if (FUN_002b19f0(handle, &value) == 0) {
        value = 0;
    }
    FUN_002b18a0(handle);
    return value;
}
