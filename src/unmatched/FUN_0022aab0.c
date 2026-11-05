struct S { char pad[12]; int x; };
int FUN_0022aa60(struct S *);
void FUN_0022aab0(struct S *arg0) {
    arg0->x++;
    FUN_0022aa60(arg0);
}
