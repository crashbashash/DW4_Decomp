/* 0x003c6830 — beNDMWDegiData_Create. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int beNDMWDegiData_RunStaticInit();
void beNDMWDegiData_Create(int arg0);
}

void beNDMWDegiData_Create(int arg0) {
    beNDMWDegiData_RunStaticInit();
    igMetaObject_CreateInstance(*(int *)0x58BD28, arg0);
}
