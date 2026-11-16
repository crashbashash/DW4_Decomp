#ifndef DW4_IGFILEDISPATCHVIEW_H
#define DW4_IGFILEDISPATCHVIEW_H
#include "dw4/igObjectDispatchView.h"

/* igFile's virtual functions as the game calls them on igPsx2File: open by name and mode, close,
 * and read (igPsx2File_<Name>).
 * ABI view only: never instantiated. */
class igFileDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22();
    virtual int OpenFile(const char *fileName, const char *mode);           /* slot 23 */
    virtual void CloseFile();                                               /* slot 24 */
    virtual int Read(void *buffer, int size, int count);                    /* slot 25 */
};

#endif
