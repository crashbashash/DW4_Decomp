/* The list pointer member is volatile so it is reloaded per iteration, the loop is tested at the
 * bottom via goto, and the locals are declared in the order a4, n, i. */
struct L { char pad0[8]; int cnt; char pad12[4]; int *data; };
struct E { char pad0[12]; int f12; struct L * volatile f16; };
int StringList_CopyRetained();
void igMetaEnum_GetNameByValue(int *arg0, struct E *arg1, int arg2) {
    int a4;
    int n;
    int i;
    a4 = arg1->f12;
    if (a4 != 0) {
        n = arg1->f16->cnt;
        i = 0;
        goto test;
body:
        if (arg2 == arg1->f16->data[i]) {
            StringList_CopyRetained(arg0, a4, i);
            return;
        }
        i++;
test:
        if (i < n) goto body;
    }
    *arg0 = 0;
}
