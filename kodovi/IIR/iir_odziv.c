#define IN
#define OUT

#define N_BUFFER 512

#include "common\common.h"

extern const int iN_CoefficientsY;
extern const double fCoefficientsY[];
extern const int iN_CoefficientsX;
extern const double fCoefficientsX[];

double CaluclateResponseSample_IIR(
    IN        int     iSample,
    IN  const double  fY[],
    IN  const double  fX[],
    IN  const double  fCoeffX[],
    IN        int     iNCoeffX,
    IN  const double  fCoeffY[],
    IN        int     iNCoeffY
)
{
    int i;

    double fSum = 0;

    int iNAvailableCoeffX = (iSample >= iNCoeffX) ? iNCoeffX : iSample + 1;
    int iNAvailableCoeffY = (iSample >= iNCoeffY) ? iNCoeffY : iSample + 1;

    for (i = 0; i < iNAvailableCoeffX; i++)
    {
        fSum += fCoeffX[i] * fX[iSample - i];
    }

    for (i = 1; i < iNAvailableCoeffY; i++)
    {
        fSum -= fCoeffY[i] * fY[iSample - i];
    }

    return fSum;

}

void CalculateResponse_IIR(
    OUT       double  fY[],
    IN  const double  fX[],
    IN        int     iNX,
    IN  const double  fCoeffX[],
    IN        int     iNCoeffX,
    IN  const double  fCoeffY[],
    IN        int     iNCoeffY
)
{
    double fValue = 0;
    int i;

    for (i = 0; i < iNX; i++)
    {
        fValue = CaluclateResponseSample_IIR(
            i,
            fY,
            fX,
            fCoefficientsX, iN_CoefficientsX,
            fCoefficientsY, iN_CoefficientsY
        );

        fY[i] = fValue;
    }
}

int main(void)
{
    const char szOutputFileName_ImpulseResponse[] = "rezultati\\IIR_ImpulseResponse.txt";
    const char szOutputFileName_StepResponse[]    = "rezultati\\IIR_StepResponse.txt";

    double fImpulseX[N_BUFFER]  = { 0 };
    double fStep[N_BUFFER]      = { 0 };
    double fBuffer[N_BUFFER]    = { 0 };

    const double fStepAmplitude = 1.0f;

    TransformToImpulse  ( fImpulseX,  N_BUFFER                  );
    TransformToStep     ( fStep,      N_BUFFER, fStepAmplitude  );

    /*********************************IMPULSE*****************************************/

    CalculateResponse_IIR(
        fBuffer, fImpulseX, N_BUFFER,
        fCoefficientsX, iN_CoefficientsX,
        fCoefficientsY, iN_CoefficientsY
    );

    WritedoubleArrayToFile(fBuffer, N_BUFFER, szOutputFileName_ImpulseResponse);

    /**********************************STEP*******************************************/

    InitializeToZero(fBuffer, N_BUFFER);
    CalculateResponse_IIR(
        fBuffer, fStep, N_BUFFER,
        fCoefficientsX, iN_CoefficientsX,
        fCoefficientsY, iN_CoefficientsY
    );

    WritedoubleArrayToFile(fBuffer, N_BUFFER, szOutputFileName_StepResponse);

    return 0;
    
}



