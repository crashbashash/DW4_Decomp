extern int DAT_00560a2c[4];
struct R { char pad[8]; int v; char pad2[68]; char flag; char pad3[55]; };
struct Tab { char pad[16]; struct R *arr; };
struct O { char pad[324]; struct Tab *tab; };
void Gap__Gfx__igPsx2VisualContext__vfunc_140(struct O *arg0, int arg1, int arg2) {
    struct R *e = arg0->tab->arr + arg1; if (arg2 == e->v) { DAT_00560a2c[0] += 1; } e = arg0->tab->arr + arg1; e->v = arg2; e = arg0->tab->arr + arg1; e->flag = 1;
}
