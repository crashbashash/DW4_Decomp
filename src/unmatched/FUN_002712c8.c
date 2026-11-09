typedef struct {
    char pad0[96];
    int (*f96)(int, int, int, int);
} CriHandler;

CriHandler *FUN_0026f890();

int FUN_002712c8(void)
{
    CriHandler *h;

    h = FUN_0026f890();
    if (h != 0) {
        if (h->f96 != 0) {
            return h->f96(0, 100, 0, 0);
        }
        return 0;
    }
    return (int)h;
}
