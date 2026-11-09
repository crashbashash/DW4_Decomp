#include "dw4/reflected.h"

typedef struct UCodeProgram {
    char pad0[68];
    int resident;
} UCodeProgram;

typedef struct UCodeSlot {
    char pad0[20];
    int kind;
    char pad24[28];
    UCodeProgram *program;
    char pad56[16];
    int *buffers;
    int buffer;
    char pad80[20];
    int altHandle;
    int handle;
    int bufferIndex;
    char pad112[24];
} UCodeSlot;

typedef struct UCodeSlotList {
    int _pad0[4];
    UCodeSlot *_data;
} UCodeSlotList;

typedef struct UCodeContextView {
    char pad0[324];
    UCodeSlotList *slots;
    char pad328[8];
    int current;
} UCodeContextView;

void FUN_0016b1d0(UCodeContextView *context, int handle);
void FUN_0020c8b0(int buffer);
int FUN_0020b270(int buffer);
void FUN_001f05a0(int channel, int size);
void FUN_0020c9f0(int buffer);

void Gap__Gfx__igPsx2VisualContext__vfunc_130(UCodeContextView *context, int index) {
    UCodeSlot *slot = &context->slots->_data[index];
    int i;

    context->current = -1;
    if (slot->handle >= 0) {
        if (slot->program->resident != 0) {
            FUN_0016b1d0(context, slot->handle);
        }
        slot->buffers[slot->bufferIndex] = 0;
    } else if (slot->altHandle >= 0) {
        FUN_0016b1d0(context, slot->altHandle);
        slot->buffers[slot->bufferIndex] = 0;
    }
    if (slot->kind == 3) {
        if (slot->buffers[0] != 0) {
            FUN_0020c8b0(slot->buffers[0]);
            if (slot->buffer != 0) {
                FUN_0020c8b0(slot->buffer);
            }
        }
    } else if (slot->buffers != 0) {
        for (i = 0; i < 8; i++) {
            if (slot->buffers[i] != 0) {
                FUN_001f05a0(2, FUN_0020b270(slot->buffers[i]));
                FUN_0020c9f0(slot->buffers[i]);
                slot->buffers[i] = 0;
            }
        }
    }
}
