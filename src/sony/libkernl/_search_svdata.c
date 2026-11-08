typedef struct N { int id; char pad[52]; struct N *next; } N;
typedef struct T { int pad[2]; N *list; int pad2[2]; struct T *next; } T;
typedef struct { char pad[40]; T *first; } G;
N *_search_svdata(int id, G *g) {
    T *t;
    N *n;
    for (t = g->first; t != 0; t = t->next) {
        for (n = t->list; n != 0; n = n->next) {
            if (n->id == id) return n;
        }
    }
    return 0;
}
