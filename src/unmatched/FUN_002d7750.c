struct S { char pad[8]; int x; };
int ObjectList_RemoveFirstRetained(int, int, int, int);
void FUN_002d7750(int arg0, struct S *arg1, int arg2) {
    ObjectList_RemoveFirstRetained(arg0, arg1->x, arg2, 0);
}
