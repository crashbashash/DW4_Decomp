struct List { char pad[8]; int *data; int count; };
struct Meta { char pad[40]; List *f40; };
struct Meta2 { char pad[40]; Meta *f40; };
class V88 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual Meta * vX(); };
class V52 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void vX(int); };

extern "C" {
int igMetaField_Reset(...);
extern Meta *DAT_00587198[4];
void igObject_ResetFields(void **arg0);
}
void igObject_ResetFields(void **arg0) {
    /* matching construct: variant search — decl order [2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    List *temp_s2;
    int temp_s1;
    int var_s0;

    temp_s2 = ((V88 *)arg0)->vX()->f40;
    var_s0 = DAT_00587198[0]->f40->count;
    temp_s1 = temp_s2->count;
    while (var_s0 < temp_s1) {
        igMetaField_Reset(temp_s2->data[var_s0], arg0);
        var_s0++;
    }
    ((V52 *)arg0)->vX(1);
}