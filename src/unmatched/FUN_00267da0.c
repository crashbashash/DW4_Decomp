int memset();

void FUN_00267da0(char *entry)
{
    if (entry != 0) {
        entry[0] = 0;
        memset(entry, 0, 144);
    }
}
