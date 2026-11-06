int FUN_003044a0();
void FUN_00304430(int arg0, ...) {
    int n = __builtin_args_info(2);
    int off;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    FUN_003044a0(arg0, (char*)__builtin_next_arg(arg0) - off);
}
