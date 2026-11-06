extern unsigned char g_DataPumpLibrary_registered[4];
void DataPumpLibrary_MarkRegistered(void) {
    if (g_DataPumpLibrary_registered[0] == 0) {
        g_DataPumpLibrary_registered[0] = 1;
    }
}
