typedef struct Obj { int vt; int refs; int pad; int id; } Obj;
typedef struct List { int vt; int r; int count; int cap; Obj **data; } List;
typedef struct Owner { char pad[304]; List *a; List *b; } Owner;
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
void igObject_Destroy(Obj *);
#define REL(o) if(o){ --(o)->refs; if((((unsigned long long)(long long)(o)->refs)&0x7fffffULL)==0) igObject_Destroy(o);}
void FUN_00155c00(int *out, Owner *owner, int id) {
    int i;
    List *l = owner->a;
    if (id >= l->count || l->data[id] == 0) {
        *out = DAT_004fb418[0];
        return;
    }
    for (i = 0; i < owner->b->count; i++) {
        List *lb = owner->b;
        Obj *o = lb->data[i];
        if (o && id == o->id) {
            REL(o);
            if (lb->count && i >= 0 && i < lb->count) lb->data[i] = 0;
        }
    }
    {
        List *la = owner->a;
        Obj *o = la->data[id];
        REL(o);
        if (la->count && id >= 0 && id < la->count) la->data[id] = 0;
    }
    *out = DAT_004fb410[0];
}
