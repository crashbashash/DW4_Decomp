
extern "C" void beMemory_Activate(void);
extern "C" void beMemory_Deactivate(void);
extern "C" void beMemory_Start(void);
extern "C" void beMemory_Stop(void);
extern "C" int beMemory_AddInfo(void);
extern "C" void beMemory_RemoveAllInfo(void);
extern "C" void beMemory_Update(void);
extern "C" int beMemory_GetMeta(void);
extern "C" int g_beMemory_metaObject[4];

/* Slot 21, empty override. */
void beMemory_Activate(void)
{
}

/* Slot 22, empty override. */
void beMemory_Deactivate(void)
{
}

/* Slot 23, empty override. */
void beMemory_Start(void)
{
}

/* Slot 24, empty override. */
void beMemory_Stop(void)
{
}

/* Slot 25, empty override returning 0. */
int beMemory_AddInfo(void) {
    return 0;
}

/* Slot 26, empty override. */
void beMemory_RemoveAllInfo(void)
{
}

/* Slot 27, empty override. */
void beMemory_Update(void)
{
}

int beMemory_GetMeta(void)
{
    return g_beMemory_metaObject[0];
}
