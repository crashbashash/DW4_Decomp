int FUN_002adc40(int, int);
int FUN_0029c380(int);
void FUN_0029b788(int);
int FUN_0029b790(int, int *);
void FUN_0029bfe8(int);
void FUN_0029c0b8(int, int);
void FUN_0029c3b8(int);
void FUN_0029c498(int);
void FUN_0029b640(int);

int FUN_0029b6e8(int h) {
    int out;
    int r;

    if (FUN_002adc40(h, 6) == 0) {
        return 0;
    }
    if (FUN_0029c380(h) == 1) {
        return 0;
    }
    FUN_0029b788(h);
    r = FUN_0029b790(h, &out);
    FUN_0029bfe8(h);
    FUN_0029c0b8(h, out);
    FUN_0029c3b8(h);
    FUN_0029c498(h);
    FUN_0029b640(h);
    return r;
}
