/* Per-frame step of a small state machine (states 1..4 are active): when the 'pending' flag at +68 is set, clears it, times the work with FUN_002b5a10 and
 * advances the state at +72 through the per-state handlers; the elapsed time is reported to FUN_002afbc8. The flag is volatile in the source (it is set elsewhere);
 * without that the compiler fills the delay slot of the timer call with the clearing store, which the retail code does not do. */
typedef struct Obj { char pad[68]; volatile int pending; int state; } Obj;
extern long FUN_002b5a10(void);
extern void FUN_002aa980(Obj *);
extern int FUN_002aa9c0(Obj *);
extern int FUN_002aa9f0(Obj *);
extern int FUN_002aad88(Obj *);
extern int FUN_002aae28(Obj *);
extern int FUN_002aae98(Obj *);
extern void FUN_002afbc8(void *, long);

void FUN_002aa868(Obj *o)
{
    int st = o->state;
    long t0;
    if (st >= 1 && st <= 4) {
        if (o->pending) {
            o->pending = 0;
            t0 = FUN_002b5a10();
            if (st >= 2 && st <= 4)
                FUN_002aa980(o);
            st = o->state;
            switch (st) {
            case 1: st = FUN_002aa9c0(o); break;
            case 2: st = FUN_002aa9f0(o); break;
            case 3: st = FUN_002aad88(o); break;
            case 4: st = FUN_002aae28(o); break;
            case 6: st = FUN_002aae98(o); break;
            case 0:
            case 5:
            default:
                break;
            }
            o->state = st;
            FUN_002afbc8((char *)o + 14040, FUN_002b5a10() - t0);
        }
    }
}
