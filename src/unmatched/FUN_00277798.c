/* matching construct: hand search — an empty macro after the call keeps it from being a tail call */
#define EMPTY_MACRO() do { } while (0)
void FUN_0027b2b0(void);
void FUN_00277798(void);
void FUN_00277798(void)
{
    FUN_0027b2b0();
    EMPTY_MACRO();
}
