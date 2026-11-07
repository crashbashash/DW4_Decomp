typedef struct N { int pad0; struct N *next; int pad2[4]; struct N *head; } N;
typedef struct L { int pad0; N *f4; } L;
extern N *DAT_00568f60[];
extern N *DAT_005691c0[4];
void FUN_001f0090(int arg0) {
    N *temp_a2;
    N *var_a1;
    N *temp_a0;

    temp_a2 = DAT_00568f60[arg0];
    var_a1 = temp_a2->head;
    while (var_a1 != 0) {
        temp_a0 = var_a1->next;
        var_a1->next = DAT_005691c0[0];
        DAT_005691c0[0] = var_a1;
        var_a1 = temp_a0;
    }
    temp_a2->head = 0;
}
