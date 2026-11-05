typedef struct S { char pad[892]; float f892; char pad896[4]; unsigned f900; char pad904[376]; unsigned f1280; } S;

void FUN_0016a380(S *arg0, float fparg0) {
    arg0->f892 = fparg0;
    if (arg0->f1280 & 4) {
        arg0->f900 = (unsigned)(2.1474836e9f * arg0->f892);
        return;
    }
    arg0->f900 = (unsigned)(2.1474836e9f * (1.0f - arg0->f892));
}
