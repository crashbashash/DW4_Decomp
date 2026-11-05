int igObject_IsKindOf(void *, int);
struct P { int pad[6]; int val; };
struct P *FUN_003022c0(int, int, int);
extern int DAT_00585b70[];
extern int DAT_00585be0[];
int FUN_002d8eb0(int arg0, int arg1) {
    struct P *s0;
    s0 = FUN_003022c0(arg0, DAT_00585be0[0], arg1); if (s0 == 0) return 0; if (igObject_IsKindOf(s0, DAT_00585b70[0]) != 0) return s0->val; return 0;
}
