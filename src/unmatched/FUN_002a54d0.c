typedef struct {
    int w[11];
} Rec2a54d0;

void FUN_002af070(void *, int *, int *);

void FUN_002a54d0(char *obj, char *src) {
    int t[2];
    char *sub;
    int d;

    sub = obj + 3368;
    FUN_002af070(src + 16, &t[0], &t[1]);
    d = t[0] - *(int *)(sub + 96);
    *(int *)(src + 12) = 1;
    *(int *)(src + 48) = d;
    *(int *)(src + 52) = t[1];
    if (d >= *(int *)(sub + 140)) {
        *(Rec2a54d0 *)(obj + 3472) = *(Rec2a54d0 *)(src + 12);
    }
}
