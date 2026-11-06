/* Returns the record at +2768 of the handle's work area while the state's count at +136 is not
 * positive, else NULL. */
typedef struct SfdPlayState {
    char pad0[136];
    int f136;               /* +136 */
} SfdPlayState;

typedef struct SfdHandle {
    char pad0[8120];
    SfdPlayState *play;     /* +8120 */
    char pad8124[5740];
    char *work;             /* +13864 */
} SfdHandle;

void *FUN_002a82c8(SfdHandle *handle) {
    char *work = handle->work;
    SfdPlayState *play = handle->play;

    if (work == 0) {
        return 0;
    }
    if (play->f136 > 0) {
        return 0;
    }
    return work + 2768;
}
