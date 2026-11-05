struct L { int pad[2]; int len; int cap; };
struct T { int pad[7]; struct L *list; };
int List_Resize(struct L *, int, int);
extern int DAT_004fb410[];
void Gap__Core__igSymbolTable__vfunc_24(int *arg0, struct T *arg1, int arg2) {
    struct L *l = arg1->list;
    int n = arg2 << 2;
    if (n >= 0) {
        if (n <= l->cap) {
            l->len = n;
        } else {
            List_Resize(l, n, 4);
        }
    }
    *arg0 = DAT_004fb410[0];
}
