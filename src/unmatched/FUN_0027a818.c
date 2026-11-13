/* Unless mode ps2rna_setup_voice is 1 with no pending count in ps2rna_nvoice, stores the busy flag (+88);
 * a flag other than 1 then runs FUN_00272fc8 on each of the object's channel handles (count at
 * +82, handles at +16), marking +89 and clearing the busy flag after each. */
typedef struct Obj_27a818 {
    char pad0[16];
    int handles[16];        /* 0x10 */
    char pad80[2];
    signed char count;      /* 0x52 */
    char pad83[5];
    signed char busy;       /* 0x58 */
    signed char done;       /* 0x59 */
} Obj_27a818;

extern int ps2rna_setup_voice;
extern int ps2rna_nvoice;
void FUN_00272fc8(int handle);

void FUN_0027a818(Obj_27a818 *obj, int flag) {
    int count = obj->count;
    int i;

    if (ps2rna_setup_voice == 1 && ps2rna_nvoice <= 0) {
        return;
    }
    obj->busy = flag;
    if (flag == 1) {
        return;
    }
    for (i = 0; i < count; i++) {
        FUN_00272fc8(obj->handles[i]);
        obj->done = 1;
        obj->busy = 0;
    }
}

