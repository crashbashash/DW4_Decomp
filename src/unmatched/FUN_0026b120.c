/* Calls FUN_00276b68 with fields 0, 8, 12 and 4 of a descriptor, or with zeros for a null
 * descriptor. */
typedef struct Desc_26b120 {
    int f0;
    int f4;
    int f8;
    int f12;
} Desc_26b120;

void FUN_00276b68(int a0, int a1, int a2, int a3);

/* matching construct: manual — declared int with no return statement; retail makes plain calls (no tail call), which ee-gcc emits only when an int function falls off its end */
int FUN_0026b120(Desc_26b120 *desc) {
    if (desc != 0) {
        FUN_00276b68(desc->f0, desc->f8, desc->f12, desc->f4);
    } else {
        FUN_00276b68(0, 0, 0, 0);
    }
}
