#define IN
#define OUT

#define N_BUFFER 512

#include "common\common.h"

extern const int    N_FeedforwardCoefficients;
extern const double pFeedforwardCoefficients[];
extern const int    N_FeedbackCoefficients;
extern const double pFeedbackCoefficients[];


double CalculateResponseSample_IIR(
    IN        int     iSample,
    IN  const double  pOutputBuffer[],
    IN  const double  pInputBuffer[],
    IN  const double  pFeedforwardCoefficients[],
    IN        int     N_FeedforwardCoefficients,
    IN  const double  pFeedbackCoefficients[],
    IN        int     N_FeedbackCoefficients
)
{
    int i;

    double fSum = 0;

    int N_AvailableFeedforwardCoefficents    = (iSample >= N_FeedforwardCoefficients)   ? N_FeedforwardCoefficients  : iSample + 1;
    int N_AvailableFeedbackCoefficients      = (iSample >= N_FeedbackCoefficients)      ? N_FeedbackCoefficients     : iSample + 1;

    for (i = 0; i < N_AvailableFeedforwardCoefficents; i++)
    {
        fSum += pFeedforwardCoefficients[i] * pInputBuffer[iSample - i];
    }

    for (i = 1; i < N_AvailableFeedbackCoefficients; i++)
    {
        fSum -= pFeedbackCoefficients[i] * pOutputBuffer[iSample - i];
    }

    return fSum;

}

void CalculateResponse_IIR(
    OUT       double  pOutputBuffer[],
    IN  const double  pInputBuffer[],
    IN        int     N_InputSamples,
    IN  const double  pFeedforwardCoefficients[],
    IN        int     N_FeedforwardCoefficients,
    IN  const double  pFeedbackCoefficients[],
    IN        int     N_FeedbackCoefficients
)
{
    double currentSampleValue = 0;
    int i;

    for (i = 0; i < N_InputSamples; i++)
    {
        currentSampleValue = CalculateResponseSample_IIR(
            i,
            pOutputBuffer,
            pInputBuffer,
            pFeedforwardCoefficients,   N_FeedforwardCoefficients,
            pFeedbackCoefficients,      N_FeedbackCoefficients
        );

        pOutputBuffer[i] = currentSampleValue;
    }
}

int main(void)
{
    const char outputFileName_ImpulseResponse[] = "rezultati\\IIR_ImpulseResponse.txt";
    const char outputFileName_StepResponse[]    = "rezultati\\IIR_StepResponse.txt";

    double pImpulseX[N_BUFFER]  = { 0 };
    double pStepX[N_BUFFER]     = { 0 };
    double pBuffer[N_BUFFER]    = { 0 };

    const double stepAmplitude = 1.0f;

    TransformToImpulse  ( pImpulseX,   N_BUFFER                     );
    TransformToStep     ( pStepX,      N_BUFFER,    stepAmplitude   );

    /*********************************IMPULSE*****************************************/

    CalculateResponse_IIR(
        pBuffer, pImpulseX, N_BUFFER,
        pFeedforwardCoefficients,       N_FeedforwardCoefficients,
        pFeedbackCoefficients,          N_FeedbackCoefficients
    );

    WriteArrayToFile(pBuffer, N_BUFFER, outputFileName_ImpulseResponse);

    /**********************************STEP*******************************************/

    InitializeToZero(pBuffer, N_BUFFER);
    CalculateResponse_IIR(
        pBuffer, pStepX, N_BUFFER,
        pFeedforwardCoefficients,   N_FeedforwardCoefficients,
        pFeedbackCoefficients,      N_FeedbackCoefficients
    );

    WriteArrayToFile(pBuffer, N_BUFFER, outputFileName_StepResponse);

    return 0;
    
}



