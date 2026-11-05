int memcpy();
struct F { int a, b; int off; int c[2]; unsigned short sz; short d; int e[2]; int def; };
void igMetaField_SetToDefault(struct F *arg0, int arg1) {
    memcpy(arg1 + arg0->off, arg0->def, arg0->sz);
}
