/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int TextOrder_PublishLine(int, int, int, int);
struct Q { int a; int b; int c; };
struct E { unsigned int id:20; unsigned int pad:12; int w4; struct Q *list; };
struct R { int w[20]; };
extern struct E DAT_004cda40[];
extern struct R DAT_004ceb30[];
void TextOrder_PublishLineListOnly(int arg0, int arg1) {
    struct E *e; int i; struct Q *q;
    i = 0;
    e = DAT_004cda40;
    for (;;) { if (e->id == arg1) break; e = e + 1; i = i + 1; }
    if (i != -1) {
        q = DAT_004cda40[i].list;
        for (;;) {
            if (q->a == 0) break;
            TextOrder_PublishLine(arg0, q->a, DAT_004ceb30[q->b].w[q->c], q->b);
            q = q + 1;
        }
    }
}
} /* extern "C" */
