/* 0x3081d0 - 104 bytes. Varargs forwarder (va_start via __builtin_args_info/next_arg); alternate compiler -O3. */
int FUN_00308540();
void FUN_003081d0(int arg0, ...) {
    int n = __builtin_args_info(2);
    int off;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    FUN_00308540(4, arg0, (char*)__builtin_next_arg(arg0) - off);
}
