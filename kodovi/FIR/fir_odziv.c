#define IN
#define OUT

#define N_BUFFER 512

#include "common\common.h"

extern const int iN_CoefficientsH;
extern const double fCoefficientsH[];

CalculateResponse_FIR(
    OUT      double fResultBuffer[],
    IN const double fX[],
    IN const int    iNX,
    IN const double fH[],
    IN const int    iNH
)
{
    const int N = iNX + iNH - 1;

    int n;
    for (n = 0; n < N; n++) {

        const int kmin = (n > iNX - 1) ? n - (iNX - 1) : 0;
        const int kmax = (n < iNH - 1) ? n : iNH - 1;

        for (int k = kmin; k <= kmax; k++) {
            fResultBuffer[n] += fH[k] * fX[n - k];
        }
    }
}

int main(void)
{
    const char szOutputFileName_ImpulseResponse[] = "rezultati\\FIR_ImpulseResponse.txt";
    const char szOutputFileName_StepResponse[] = "rezultati\\FIR_StepResponse.txt";

    double fImpulseX[N_BUFFER] = { 0 };
    double fStep[N_BUFFER] = { 0 };
    double fBuffer[N_BUFFER] = { 0 };

    const double fStepAmplitude = 1.0f;

    TransformToImpulse(fImpulseX, N_BUFFER);
    TransformToStep(fStep, N_BUFFER, fStepAmplitude);

    /*********************************IMPULSE*****************************************/

    CalculateResponse_FIR(
        fBuffer, fImpulseX, N_BUFFER,
        fCoefficientsH, iN_CoefficientsH
    );

    WritedoubleArrayToFile(fBuffer, N_BUFFER, szOutputFileName_ImpulseResponse);

    /**********************************STEP*******************************************/

    InitializeToZero(fBuffer, N_BUFFER);
    CalculateResponse_FIR(
        fBuffer, fStep, N_BUFFER,
        fCoefficientsH, iN_CoefficientsH
    );

    WritedoubleArrayToFile(fBuffer, N_BUFFER, szOutputFileName_StepResponse);

    return 0;

}



