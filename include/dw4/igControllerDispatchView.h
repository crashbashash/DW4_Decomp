#ifndef DW4_IGCONTROLLERDISPATCHVIEW_H
#define DW4_IGCONTROLLERDISPATCHVIEW_H
#include "dw4/igObjectDispatchView.h"

/* igController's virtual functions as the game calls them on igPsx2Controller: the pressed buttons,
 * a joystick's axes, the controller's id and whether it is plugged in.
 * ABI view only: never instantiated. */
class igControllerDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual unsigned int getButtons();                                      /* slot 28 */
    virtual void getStick(int stick, float *x, float *y);                   /* slot 29 */
    virtual unsigned short getId();                                         /* slot 30 */
    virtual void d31();
    virtual int isConnected();                                              /* slot 32 */
};

#endif
