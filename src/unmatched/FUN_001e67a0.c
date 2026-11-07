int FUN_001e6490();
typedef struct L { char pad[8]; int count; int pad2; int *data; } L;
typedef struct S { char pad[8]; L *list; } S;

int FUN_001e67a0(S *arg0, int arg1) {
    int i;
    int n;

    n = arg0->list->count;
    for (i = 0; i < n; i++) {
        FUN_001e6490(arg0->list->data[i], arg1);
    }
    return 1;
}
