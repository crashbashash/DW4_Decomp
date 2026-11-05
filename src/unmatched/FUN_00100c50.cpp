extern "C" {
/* 0x00100c50 - FUN_00100c50. Calls each function pointer of a table range; alternate compiler. Verified byte-identical by tools/verify.py. */
void FUN_00100c50(void (**arg0)(), void (**arg1)()) {
    void (**var_s0)();

    var_s0 = arg0;
    if (arg0 < arg1) {
        do {
            (*var_s0)();
            var_s0 += 1;
        } while (var_s0 < arg1);
    }
}
}
