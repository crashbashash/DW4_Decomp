/* Transition check for the state field at +60 against the requested state k: returns 0 for the terminal state 100, for requested states 1, 4, 5, 21, 22 and
 * (unless FUN_002b30e8(+52) reports 1) 2 when they equal the current state; 1 otherwise. */
typedef struct Obj { char pad[52]; int f52; int pad2; int f60; } Obj;
extern int FUN_002b30e8(int);
int FUN_002b3490(Obj *o, unsigned int k)
{
    int ret = 1;
    if (o->f60 == 100)
        return 0;
    if (o->f60 == k) {
        switch (k) {
        case 2:
            if (FUN_002b30e8(o->f52) == 1)
                break;
        case 1:
        case 4:
        case 5:
        case 21:
        case 22:
            ret = 0;
            break;
        case 0:
        case 3:
        case 6 ... 20:
        case 23 ... 100:
        default:
            break;
        }
    }
    return ret;
}
