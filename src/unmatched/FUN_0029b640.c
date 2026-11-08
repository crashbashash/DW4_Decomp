int FUN_0026c2d8(int);
int FUN_0026c328(int);
void FUN_0029ee80(void *, int, int);

void FUN_0029b640(char *obj) {
    char *sub = obj + 3368;
    int h = **(int **)(obj + 8188);
    int w;
    int ht;

    if (*(int *)(sub + 500) == *(int *)(sub + 504)) {
        w = FUN_0026c2d8(h);
        ht = FUN_0026c328(h);
        if (w > 0 && ht > 0) {
            FUN_0029ee80(obj, w, ht);
            return;
        }
    }
}
