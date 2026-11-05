extern "C" {
int __floatdidf(long long);
int __adddf3(int, int);

void FUN_00100240(long long arg0) {
    int temp_v0;

    if (arg0 > 0) {
        __floatdidf(arg0);
        return;
    }
    temp_v0 = __floatdidf(((unsigned long long)arg0 >> 1) | (arg0 & 1));
    __adddf3(temp_v0, temp_v0);
}
}
