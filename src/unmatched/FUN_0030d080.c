typedef struct B { char pad8[8]; int cnt; char pad12[4]; char *data; } B;
typedef struct A { char pad16[16]; B *b; } A;
int FUN_0030d080(A *arg0) {
    int i;
    int n;
    int count;
    char *p;
    B *b;

    b = arg0->b;
    p = b->data;
    n = b->cnt;
    count = 0;
    if (p == 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (*p == 0) {
            count++;
        }
        p++;
    }
    return count;
}
