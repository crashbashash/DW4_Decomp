extern int DAT_00568f60[4];
struct N { long long a; int pad; int next; int fn; };
struct H { char pad[16]; struct N *head; };
int FUN_001efec0(int arg0) {
    int var_s0;
    int var_v0;
    struct N *var_s1;
    var_s1 = ((struct H *)DAT_00568f60[arg0])->head;
    var_s0 = 1;
    while (var_s1 != 0) { var_v0 = ((int (*)(long long))var_s1->fn)(var_s1->a) != 0 ? 1 : 0; var_s0 &= var_v0; if (var_s0 == 0) break; var_s1 = (struct N *)var_s1->next; }
    return var_s0;
}
