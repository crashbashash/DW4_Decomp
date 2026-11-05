int memcpy();
typedef struct S { int pad0[2]; int f8; int pad1[2]; unsigned short f20; short pad2; int pad3[2]; int f32; } S;
void igMetaField_CopyDefaultToValue(S *arg0, int arg1) {
    memcpy(arg1 + arg0->f8, arg0->f32, arg0->f20);
}
