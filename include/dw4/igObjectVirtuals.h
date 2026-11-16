#ifndef DW4_IGOBJECTVIRTUALS_H
#define DW4_IGOBJECTVIRTUALS_H

/* Placeholders that hold the vtable slots in front of a named one, so that a view class places each
 * virtual it names at its retail slot. `p` keeps the names of two runs in one class apart. */
#define DW4_SLOTS_1(p) virtual void p();
#define DW4_SLOTS_5(p) \
    virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4();
#define DW4_SLOTS_20(p) DW4_SLOTS_5(p##a) DW4_SLOTS_5(p##b) DW4_SLOTS_5(p##c) DW4_SLOTS_5(p##d)
#define DW4_SLOTS_100(p) DW4_SLOTS_20(p##a) DW4_SLOTS_20(p##b) DW4_SLOTS_20(p##c) DW4_SLOTS_20(p##d) DW4_SLOTS_20(p##e)

/* An igObject seen through its vtable, for the virtual calls a class makes on itself: slot 20 is
 * the meta-object getter every igObject class overrides. */
class igObjectVirtuals {
public:
    DW4_SLOTS_20(s)
    virtual int getMeta();
};

#endif
