typedef struct { char pad[1022]; unsigned char b; char pad2; int i; float f; } S;
int FUN_001e8550(); extern int DAT_0048a500[4];
void FUN_001747f0(S *s) { if (s->b == 1) { int a = (int)(128.0f * (float)s->f); FUN_001e8550(DAT_0048a500[s->i], a, 0); } }
