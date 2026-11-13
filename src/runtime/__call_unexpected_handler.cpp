extern "C" {
extern int (*DAT_00481c18[4])();
void __call_unexpected_handler(void);
}
void __call_unexpected_handler(void) {
    DAT_00481c18[0]();
}
