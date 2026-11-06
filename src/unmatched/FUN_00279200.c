/* Forwards its second argument to FUN_002607e8 (the ADX error reporter); the first is ignored. */
extern void FUN_002607e8(const char *message);

void FUN_00279200(int unused, const char *message) {
    FUN_002607e8(message);
}
