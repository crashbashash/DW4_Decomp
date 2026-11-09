int memset();

void FUN_00267c18(char *entry)
{
    if (entry != 0) {
        entry[0] = 0;
        memset(entry, 0, 12);
    }
}
