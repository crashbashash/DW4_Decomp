struct E { int v; char pad[60]; };
extern struct E DAT_00562dcc[];
int FUN_001eb380(int i) { if (i != -1) return DAT_00562dcc[i].v; return 0; }
