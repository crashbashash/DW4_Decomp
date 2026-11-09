int strlen();

int FUN_00274d30(char *name)
{
    if (strlen(name) != 17) {
        return 0;
    }
    return name[8] == '.';
}
