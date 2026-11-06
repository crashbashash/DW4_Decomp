extern unsigned char g_DataPumpLibrary_registered;
void DataPumpLibrary_MarkRegistered(void) {
    if (g_DataPumpLibrary_registered == 0) {
        g_DataPumpLibrary_registered = 1;
    }
}
