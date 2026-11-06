typedef struct { int pad[3]; volatile int a; float b; } S2;
void FUN_00174770(int, int);
void FUN_001747b0(int, float);
void Gap__Core__igAlphaFunctionAttr__vfunc_24(S2* p, int q) { FUN_00174770(q, p->a); FUN_001747b0(q, p->b); }
