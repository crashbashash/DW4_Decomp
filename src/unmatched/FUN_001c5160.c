extern float DAT_0048da28[4];
typedef struct S0 { char pad552[552]; float f552; float f556; } S0;
int FUN_001c5160(S0 *arg0, float fparg0) {
    if (fparg0 < arg0->f556 && !(fparg0 < 1.0f)) { arg0->f552 = fparg0; DAT_0048da28[0] = 1.0f / fparg0; return 1; } return 0;
}
