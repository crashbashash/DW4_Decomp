typedef struct S1 { char pad52[52]; int f34; char pad68[12]; int f44; } S1;
int FUN_001d9ac0();

void FUN_001d5e00(void *arg0, S1 *arg1) {
    if (*(unsigned char *)((char *)(arg0) + 236) != 0) {
        FUN_001d9ac0(arg1->f44, *(int *)((char *)(arg0) + 228), arg1->f34);
        FUN_001d9ac0(arg1->f44, *(int *)((char *)(arg0) + 232), arg1->f34);
    }
}
