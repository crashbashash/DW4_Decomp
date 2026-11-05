int FUN_0017a870();
int FUN_001edbc0();
int p2LoadTexture();

void FUN_0017a7e0(void *arg0) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int sp2C;
    int sp28;
    int sp24;
    int sp20;

    FUN_0017a870(arg0, 0);
    FUN_001edbc0(&sp2C, &sp28, &sp24, &sp20);
    *(int *)((char *)(arg0) + 1524) = p2LoadTexture(0, sp2C, sp28, sp24, 1);
    *(int *)((char *)(arg0) + 1528) = p2LoadTexture(0, sp2C, sp28, sp24, 2);
    *(int *)((char *)(arg0) + 1532) = p2LoadTexture(0, sp2C, sp28, sp20, 3);
}
