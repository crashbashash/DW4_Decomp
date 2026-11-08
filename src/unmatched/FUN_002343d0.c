int printf();
int fptodp(float);
extern int DAT_004e9680[4];
void FUN_002343d0(int arg0, int arg1, void *arg2) {
    /* matching construct: variant search — decl order [2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int temp_s2;
    int temp_s1;
    int temp_s0;
    temp_s2 = fptodp(*(float *)((char *)(arg2) + 0));
    temp_s1 = fptodp(*(float *)((char *)(arg2) + 4));
    temp_s0 = fptodp(*(float *)((char *)(arg2) + 12));
    printf(&DAT_004e9680[0], arg0, arg1, temp_s2, temp_s1, temp_s0, fptodp(*(float *)((char *)(arg2) + 8)));
}
