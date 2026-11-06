/* True when stream slot \`index\` is active and its fill (+8) has reached its size (+4). */
typedef struct SfdSlotFill {
    int active;             /* +0 */
    int size;               /* +4 */
    int fill;               /* +8 */
} SfdSlotFill;

typedef struct SfdStreamSlot {
    char pad0[44];
    SfdSlotFill fill;       /* +44 */
    char pad56[60];
} SfdStreamSlot;

typedef struct SfdHandle {
    char pad0[4884];
    SfdStreamSlot slots[1]; /* +4884, 116 bytes each */
} SfdHandle;

int FUN_002acaf0(SfdHandle *handle, int index) {
    SfdSlotFill *fill = &handle->slots[index].fill;

    if (fill->active == 0) {
        return 0;
    }
    return fill->fill >= fill->size;
}
