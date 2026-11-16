
extern "C" void Gap__Core__igObject__userConstruct(void);
extern "C" void Gap__Core__igObject__userDestruct(void);
extern "C" void beKeyboardReceiver_userConstruct(void);
extern "C" void beKeyboardReceiver_userDestruct(void);
extern "C" int beKeyboardReceiver_OnKeyEvent(void);
extern "C" int beKeyboardReceiver_GetMeta(void);
extern "C" int g_beKeyboardReceiver_metaObject[4];

void beKeyboardReceiver_userConstruct(void)
{
    Gap__Core__igObject__userConstruct();
}

void beKeyboardReceiver_userDestruct(void)
{
    Gap__Core__igObject__userDestruct();
}

/* Slot 21, empty override returning 0. */
int beKeyboardReceiver_OnKeyEvent(void) {
    return 0;
}

/* Slot 20, GetMetaObject. */
int beKeyboardReceiver_GetMeta(void)
{
    return g_beKeyboardReceiver_metaObject[0];
}

