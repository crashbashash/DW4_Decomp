/* Typed struct fields (no address CSE of base+16) and a typed element array for the stride-4
 * table. */
typedef struct N { int pad[3]; int f12; int f16; struct N *f20; } N;
extern N *DAT_00568f60[];
extern int DAT_005691b8[4];
void FUN_001efe70(int arg0) {
    N *temp_a1;

    temp_a1 = DAT_00568f60[arg0];
    if (temp_a1->f16 != 0) {
        temp_a1->f20->f12 = DAT_005691b8[0];
        DAT_005691b8[0] = temp_a1->f16;
        temp_a1->f16 = 0;
    }
}
