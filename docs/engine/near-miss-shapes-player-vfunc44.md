# beNDMWMdlPlayer::vfunc_44 (0x003d4390): typed recovery and the last wall

`Gap::Bec::beNDMWMdlPlayer::vfunc_44` (608 bytes) is the player's idle player-number-badge handler
(findings [#1090](../findings/findings-1001-1250.md#f1090) and [#1092](../findings/findings-1001-1250.md#f1092)). It is **not banked**: the best source below is byte-identical to retail except
for one 5-word cluster, so it stays assembly until that is solved.

## What it does (typed)

* `msg` is a command object: `+8` the player number, `+12` a record whose `+8` is a receiver name, `+40` a
  lazily created reference-counted cache (23-bit refcount at `+4`; `igObject_Destroy` at zero).
* `FindByName(msg->cache, <class>, "ONE")` then `+20` is the `beNDMWMdlPlayerInfoWork`; its `+20` is
  `_seqCodeName` and its `+292` is `_isPanel`.
* While the sequence name is `"SQ_WAIT"` it sends
  `MODELCTRL <receiver> SETEFFECT i_pcnumic SQ_OPENP<n> 480.0 V<0,10,0> true true` through
  `self->_messenger` (`beNDMWMdlPlayer` `+20`). `480.0` is a delay in frames: the badge appears after about
  8 s in `SQ_WAIT` (measured live, finding [#1092](../findings/findings-1001-1250.md#f1092)).
* If `_isPanel` is set and the current sequence name is a known enum value (`igMetaEnum_GetValueByName`
  status equals `DAT_004fb410`, "found"), it clears `_isPanel` and sends `NDMWPANEL ... REMOVE`.
* It ends by calling the base handler `FUN_00445200(self, msg)`.

Strings: `DAT_00516110` "ONE", `DAT_00516290` "SQ_WAIT", `DAT_00516228` "MODELCTRL", `DAT_005164b8`
"i_pcnumic", `DAT_005164c8` "SQ_OPENP%d", `DAT_005164d8` "SETEFFECT", `DAT_00516148` "NDMWPANEL",
`DAT_005164b0` "REMOVE".

## Source that matches except one cluster

Compile with the alternate compiler at `-O3,p` (`local/mwcps2/combat/mwccps2.exe`, see
[unit-compilers](unit-compilers.md)). It supplies the padding `nop`s of the release block and the
`SETEFFECT` block by itself; only the trailing `nop` after `SendNamed` needs `asm { nop }`.

```cpp
struct EV { int v; static int rd(EV *p) { return p->v; } };
extern "C" {
#include "dw4/reflected.h"

typedef struct Ref { int vt; unsigned rc; } Ref;
typedef struct Msg {
    char _pad0[8];
    int number;            /* +8  player number */
    char *info;            /* +12 */
    char _pad16[24];
    Ref *cache;            /* +40 */
} Msg;

void *igObject_GetAllocator(Msg *);
void *Memory_GetAllocatorBySelector(int);
Ref *FUN_0036ae80(void *);
void igObject_Destroy(Ref *);
char *igProperty_FindByName(Ref *, int, const char *);
int igStrCmp(int, const char *);
void beMessenger_SelectReceivers(int, const char *, const char *, int);
void beMessenger_AppendString(int, const char *);
void FUN_00129e60(char *, const char *, int);
void beMessenger_AppendFloat(int, float);
void beMessenger_AppendVec3(int, int *);
void beMessenger_AppendBool(int, int);
void beMessenger_DispatchSelected(int, const char *);
void *FUN_003bf830(void);
void igMetaEnum_GetValueByName(EV *, void *, int, int *);
void beMessenger_SendNamed(int, const char *, int, int, const char *);
void FUN_00445200(void *, Msg *);

extern unsigned char GPR_00554c14;
extern char DAT_004e0858[], DAT_00516110[], DAT_00516148[], DAT_00516228[], DAT_00516290[], DAT_005164b0[], DAT_005164b8[], DAT_005164c8[], DAT_005164d8[];
}
struct Tmp { Ref *p; ~Tmp() { Ref *q = p; if (q) { q->rc--; if ((q->rc & 0x7fffff) == 0) igObject_Destroy(q); } } };
extern int DAT_00587110[4], DAT_00585be0[4], DAT_004fb410[4];

extern "C" void Gap__Bec__beNDMWMdlPlayer__vfunc_44(beNDMWMdlPlayer *self, Msg *msg)
{
    beNDMWMdlPlayerInfoWork *pinfo;
    Ref *r;
    char *minfo = msg->info;
    char name[24];
    int vec[3];
    int tmp; EV en;
    if (msg->cache == 0) {
        void *al = igObject_GetAllocator(msg);
        void *al2;
        if (GPR_00554c14 != 0) {
            al2 = al;
        } else {
            al2 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        Tmp t;
        t.p = FUN_0036ae80(al2);
        r = t.p;
        if (r) r->rc++;
        Ref *old = msg->cache;
        if (old) {
            old->rc--;
            if ((old->rc & 0x7fffff) == 0) igObject_Destroy(old);
        }
        msg->cache = r;
    }
    Ref *c0 = msg->cache;
    pinfo = *(beNDMWMdlPlayerInfoWork **)(igProperty_FindByName(c0, DAT_00585be0[0], DAT_00516110) + 20);
    if (igStrCmp(pinfo->_seqCodeName, DAT_00516290) == 0) {
        const char *who = *(char **)(minfo + 8);
        int num = msg->number;
        const char *w2 = who ? who : DAT_004e0858;
        beMessenger_SelectReceivers(self->_messenger, DAT_00516228, w2, num);
        beMessenger_AppendString(self->_messenger, DAT_005164b8);
        FUN_00129e60(name, DAT_005164c8, msg->number);
        beMessenger_AppendString(self->_messenger, name);
        beMessenger_AppendFloat(self->_messenger, 480.0f);
        vec[0] = 0; vec[1] = 0x41200000; vec[2] = 0;
        beMessenger_AppendVec3(self->_messenger, vec);
        beMessenger_AppendBool(self->_messenger, 1);
        beMessenger_AppendBool(self->_messenger, 1);
        beMessenger_DispatchSelected(self->_messenger, DAT_005164d8);
    }
    if (pinfo->_isPanel != 0) {
        igMetaEnum_GetValueByName(&en, FUN_003bf830(), pinfo->_seqCodeName, &tmp);
        if (EV::rd(&en) == DAT_004fb410[0]) {
            pinfo->_isPanel = 0;
            beMessenger_SendNamed(self->_messenger, DAT_00516148, 0, msg->number, DAT_005164b0);
            asm { nop }
        }
    }
    FUN_00445200(self, msg);
}
```

## The wall

Words 126 to 130 differ. Retail compares the status through a pointer register that survives the call:

    addiu a3,sp,124 ; jal igMetaEnum_GetValueByName      (delay slot)
    addiu v1,sp,120 ; lui at,0x50 ; lw v0,-19440(at) ; lw v1,0(v1) ; bne v1,v0,...

while every shape tried folds the read into `lw v1,120(sp)` (one word short). Tried without effect: a
pointer local before or after the call, `volatile`, a one-element array, a static member accessor (it
inlines and folds), a member comparison (becomes `xor`/`sltiu`), a struct with a copy constructor (forces
the hidden-pointer return, which matches the call but swaps the two stack slots and still folds), a class
with a destructor, and `-O4,p`, `-O3,s` and `-inline off` (the last turns the accessor into a real call).
The stack slots match only with `int tmp; EV en;` declared at the top and the smart-pointer temporary
inside the `if` block.
