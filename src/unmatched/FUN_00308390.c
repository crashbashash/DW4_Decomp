int FUN_00308540();
void FUN_00308390(int arg0, ...) {
    int n = __builtin_args_info(2);
    int off;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    FUN_00308540(2, arg0, (char*)__builtin_next_arg(arg0) - off);
}
