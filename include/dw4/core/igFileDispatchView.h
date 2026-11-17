#ifndef DW4_IGFILEDISPATCHVIEW_H
#define DW4_IGFILEDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igFile's virtual functions as the game calls them on igPsx2File: open by name and mode, close,
 * read (igPsx2File_<Name>), and complete a file name with the device prefix (slot 39,
 * igPsx2File_MakeCompleteFilename).
 * ABI view only: never instantiated. */
class igFileDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22();
    virtual int OpenFile(const char *fileName, const char *mode);           /* slot 23 */
    virtual void CloseFile();                                               /* slot 24 */
    virtual int Read(void *buffer, int size, int count);                    /* slot 25 */
    virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32();
    virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38();
    virtual char *MakeCompleteFilename(const char *name);                   /* slot 39 */
};

#endif
