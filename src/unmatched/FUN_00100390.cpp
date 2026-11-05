extern "C" {
void FUN_00100390(int base, void (*fn)(int, int), int stride, int n) {
    int p = base + stride * n;
    if (n != 0) {
        do {
            p -= stride;
            fn(p, -1);
            n--;
        } while (n != 0);
    }
}
}
