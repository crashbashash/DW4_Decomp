extern "C" {
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
