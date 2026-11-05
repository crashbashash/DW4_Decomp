typedef struct S { int f0; int f4; int f8; int pad[2]; int f20; } S;
int List_InsertWords(int a, int b, int c, void *d);
void FUN_0023b3b0(S *arg0, int *arg1) { int *volatile sp2C = arg1; int *t; int i = arg0->f20; int b = arg0->f8; if ((t = sp2C) != 0) { t[1] = t[1] + 1; } List_InsertWords(b, i, 1, (void*)&sp2C); arg0->f20 = arg0->f20 + 1; }
