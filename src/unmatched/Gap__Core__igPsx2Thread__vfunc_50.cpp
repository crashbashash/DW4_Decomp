struct R { int v; R() {} R(const R &o) : v(o.v) {}
  bool operator==(const R &o) const { return v == o.v; }
  bool operator!=(const R &o) const { return v != o.v; }
};
extern "C" {
int ChangeThreadPriority(int, int);
extern R DAT_004fb410;
extern R DAT_004fb418;
}
extern "C" R FUN_0030e430(void *);
struct Thread { char pad[24]; int priority; char pad2[32]; int id; };
extern "C" R Gap__Core__igPsx2Thread__vfunc_50(Thread *t) {
    if (FUN_0030e430(t) != DAT_004fb410) {
        return DAT_004fb418;
    }
    if (t->id != -1) {
        return ChangeThreadPriority(t->id, t->priority / 2) < 0 ? DAT_004fb418 : DAT_004fb410;
    }
    return DAT_004fb410;
}
