int memset();

void FUN_0026f010(int *entry)
{
    if (entry != 0) {
        entry[0] = 0;
        memset(entry, 0, 60);
    }
}
