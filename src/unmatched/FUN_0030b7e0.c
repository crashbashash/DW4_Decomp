/* 0x0030b7e0 - 96 bytes. Varargs forwarder with two named arguments; alternate compiler -O3. */
int FUN_0030b840();
void FUN_0030b7e0(int arg0, int arg1, ...) {
    int n = __builtin_args_info(2);
    int off;
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    FUN_0030b840(arg0, arg1, (char*)__builtin_next_arg(arg1) - off);
}
