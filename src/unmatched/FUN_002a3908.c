/* When stream +8132 is not 1 but stream +8128 is, and FUN_002a39b8 agrees, sets stream +8132 to 1
 * and calls FUN_002a3b48. */
typedef struct SfdStreamPair {
    char pad0[16];
    int f16;                /* handle +8128 */
    int f20;                /* handle +8132 */
} SfdStreamPair;

typedef struct SfdHandle {
    char pad0[8112];
    SfdStreamPair pair;     /* +8112 */
} SfdHandle;

extern int FUN_0029ea48(SfdHandle *handle, int index);
extern int FUN_002a39b8(SfdHandle *handle);
extern int FUN_0029ea28(SfdHandle *handle, int index, int value);
extern void FUN_002a3b48(SfdHandle *handle);

void FUN_002a3908(SfdHandle *handle) {
    SfdStreamPair *pair = &handle->pair;
    int target = pair->f20;
    int source = pair->f16;

    if (FUN_0029ea48(handle, target) != 1 && FUN_0029ea48(handle, source) == 1 && FUN_002a39b8(handle) != 0) {
        FUN_0029ea28(handle, target, 1);
        FUN_002a3b48(handle);
    }
}
