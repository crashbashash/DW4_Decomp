struct S { char p[36]; unsigned f; };
extern "C" {
int FUN_00340800();
extern S *DAT_00587bb8[4];
void *FUN_00340770(void);
}
void *FUN_00340770(void) {
    bool ok;
    if (DAT_00587bb8[0] == 0) goto make;
    ok = !!(DAT_00587bb8[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_00340800();
done:;
    return DAT_00587bb8[0];
}
