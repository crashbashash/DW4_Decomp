int StringChunk_Destroy();
struct P { int pad; struct C *head; };
struct C { int pad; struct C *next; };
void StringPool_DestroyChunks(struct P *arg0) {
    struct C *c = arg0->head;
    while (c != 0) {
        struct C *t = c;
        c = c->next;
        StringChunk_Destroy(t, 1);
    }
}
