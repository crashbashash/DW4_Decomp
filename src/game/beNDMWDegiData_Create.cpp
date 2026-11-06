extern "C" {
int igMetaObject_CreateInstance(int, int);
int beNDMWDegiData_RunStaticInit();
void beNDMWDegiData_Create(int arg0);
}

void beNDMWDegiData_Create(int arg0) {
    beNDMWDegiData_RunStaticInit();
    igMetaObject_CreateInstance(*(int *)0x58BD28, arg0);
}
