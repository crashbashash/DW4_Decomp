/* Sets streams +8068, +8064 and +8072 to 1 through FUN_0029ea68, then calls FUN_002a9d70. */
typedef struct SfdStreamIds {
    char pad0[20];
    int f20;                /* handle +8064 */
    int f24;                /* handle +8068 */
    int f28;                /* handle +8072 */
} SfdStreamIds;

typedef struct SfdHandle {
    char pad0[8044];
    SfdStreamIds ids;       /* +8044 */
} SfdHandle;

extern int FUN_0029ea68(SfdHandle *handle, int index, int value);
extern void FUN_002a9d70(SfdHandle *handle, int value);

void FUN_002a21d8(SfdHandle *handle, int value) {
    SfdStreamIds *ids = &handle->ids;

    FUN_0029ea68(handle, ids->f24, 1);
    FUN_0029ea68(handle, ids->f20, 1);
    FUN_0029ea68(handle, ids->f28, 1);
    FUN_002a9d70(handle, value);
}
