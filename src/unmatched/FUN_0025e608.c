/* Runs FUN_0025e4b8 on each of the 16 slots in DAT_00498c80 whose state halfword is 1. */
/* One 260-byte slot of the DAT_00498c80 table; only the leading state is read here. */
typedef struct Slot_25e608 {
    short state;
    char rest[258];
} Slot_25e608;

extern Slot_25e608 DAT_00498c80[16];
void FUN_0025e4b8(Slot_25e608 *slot);

void FUN_0025e608(void) {
    Slot_25e608 *slot = DAT_00498c80;
    int remaining = 15;

    do {
        if (slot->state == 1) {
            FUN_0025e4b8(slot);
        }
        remaining--;
        slot++;
    } while (remaining >= 0);
}
