struct S { char pad[24]; int a; char pad2[16]; int b; char pad3[8]; int c; int d; };
extern "C" int FUN_0010f738(int, int, int);
extern "C" int FUN_0010fbd0(int, int, int);
extern "C" int FUN_0032b870(S *arg0);
int FUN_0032b870(S *arg0) {
    if (arg0->d != 0) return 0; FUN_0010f738(arg0->a, 0, 0); FUN_0010fbd0(arg0->a, arg0->b, arg0->c); return 0;
}
