#include "dw4/reflected.h"
extern "C" {
int sprintf(...);
int FUN_002d6e60(...);
int FUN_002f89a0(...);
void *FUN_0032a100(...);
int FUN_0032a180(...);
int FUN_0032a1b0(...);
void *FUN_0032a1e0(...);
int List_InsertWords(...);
void FUN_0032a260(void);  /* code at 0x32a260, passed by address (was DAT_32a260; docs/engine/function-inventory.md) */
extern int DAT_004fc3e0[4];
void FUN_003123b0(igArenaMemoryPool *arg0, int arg1);
}
class V1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int v31(); };
class V2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual long long v34(); };
struct Rng { int a; int b; };
struct Big { char p[2020]; int *tab; int pad; int n; };
void FUN_003123b0(igArenaMemoryPool *arg0, int arg1) {
    void *spEC;
    int sp60[35];
    int temp_s0;
    int var_s1;
    int temp_v0;
    Big *temp_s2;
    Rng *r;
    void *var_v0_2;
    int var_v0, var_a3;
    long long temp_a4;
    void *temp_v1;
    int temp_a0;

    temp_s2 = (Big *)(arg0->_arenaState);
    if (((V1 *)(arg0))->v31() != 0) {
        var_s1 = 0;
        if (temp_s2->n != 0) {
            while (var_s1 < temp_s2->n) {
                temp_s0 = FUN_002f89a0(arg0);
                temp_a4 = (long long)(int)((V2 *)(arg0))->v34();
                var_v0 = var_s1 / 2;
                temp_v0 = temp_s2->n;
                var_a3 = temp_v0 / 2;
                sprintf(&sp60[0], &DAT_004fc3e0[0], var_v0 + 1, var_a3, temp_a4);
                var_v0_2 = (void *)(FUN_0032a1e0(0xA8));
                if (var_v0_2 != 0) {
                    var_v0_2 = (void *)(FUN_0032a100(var_v0_2));
                }
                spEC = (void *)(var_v0_2);
                *(int *)((char *)(var_v0_2) + 0) = temp_s2->tab[var_s1];
                r = (Rng *)(temp_s2->tab + var_s1);
                *(int *)((char *)(spEC) + 4) = r->b - r->a;
                FUN_0032a180(spEC, &sp60[0]);
                FUN_0032a1b0(spEC, temp_s0);
                List_InsertWords(arg1, FUN_002d6e60(arg1, &spEC, FUN_0032a260), 1, &spEC);
                var_s1 += 2;
            }
        }
    }
}
