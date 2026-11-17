/* CRI SJERR: the stream joints' error report, handed to the CRI error callback. */
#include "dw4/cri/svm.h"
#include "dw4/cri/sj.h"


void SJERR_CallErr(const char *message)
{
    SVM_CallErr1(message);
}
