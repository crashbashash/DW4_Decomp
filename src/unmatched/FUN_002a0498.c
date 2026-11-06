/* Reads four settings through getter callbacks into +16..+28 of a record; a missing third one
 * defaults to 2. */
typedef struct SfdSettings {
    char pad0[16];
    int f16;
    int f20;
    int f24;
    int f28;
} SfdSettings;

extern int FUN_002b1f88(void *handle, int *value);
extern int FUN_002b1fd8(void *handle, int *value);
extern int FUN_002b2028(void *handle, int *value);
extern int FUN_002b2078(void *handle, int *value);
extern int FUN_002a0888(void *handle, int (*getter)(void *handle, int *value));

void FUN_002a0498(void *handle, SfdSettings *out) {
    out->f16 = FUN_002a0888(handle, FUN_002b1f88);
    out->f20 = FUN_002a0888(handle, FUN_002b1fd8);
    out->f24 = FUN_002a0888(handle, FUN_002b2028);
    if (out->f24 == -1) {
        out->f24 = 2;
    }
    out->f28 = FUN_002a0888(handle, FUN_002b2078);
}
