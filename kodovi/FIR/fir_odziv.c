#define IN
#define OUT

#define N_BUFFER 512

#include "common\common.h"

extern const int    N_ImpulseResponseCoefficients;
extern const double pImpulseResponseCoefficients[];

CalculateResponse_FIR(
    OUT      double pResultBuffer[],
    IN const double pInputBuffer[],
    IN const int    N_InputBuffer,
    IN const double pImpulseResponse[],
    IN const int    N_ImpulseResponse
)
{
    const int N = N_InputBuffer + N_ImpulseResponse - 1;

    int n;
    for (n = 0; n < N; n++) {

        const int kmin = (n > N_InputBuffer - 1)     ? n - (N_InputBuffer - 1) : 0;
        const int kmax = (n < N_ImpulseResponse - 1) ? n                       : N_ImpulseResponse - 1;

        for (int k = kmin; k <= kmax; k++) {
            pResultBuffer[n] += pImpulseResponse[k] * pInputBuffer[n - k];
        }
    }
}

int main(void)
{
    const char outputFileName_ImpulseResponse[] = "rezultati\\FIR_ImpulseResponse.txt";
    const char outputFileName_StepResponse[]    = "rezultati\\FIR_StepResponse.txt";

    double pImpulseX[N_BUFFER] = { 0 };
    double pStepX[N_BUFFER] = { 0 };
    double pBuffer[N_BUFFER] = { 0 };

    const double stepAmplitude = 1.0f;

    TransformToImpulse(pImpulseX,    N_BUFFER                    );
    TransformToStep   (pStepX,       N_BUFFER,   stepAmplitude   );

    /*********************************IMPULSE*****************************************/

    CalculateResponse_FIR(
        pBuffer, pImpulseX, N_BUFFER,
        pImpulseResponseCoefficients, N_ImpulseResponseCoefficients
    );

    WriteArrayToFile(pBuffer, N_BUFFER, outputFileName_ImpulseResponse);

    /**********************************STEP*******************************************/

    InitializeToZero(pBuffer, N_BUFFER);
    CalculateResponse_FIR(
        pBuffer, pStepX, N_BUFFER,
        pImpulseResponseCoefficients, N_ImpulseResponseCoefficients
    );

    WriteArrayToFile(pBuffer, N_BUFFER, outputFileName_StepResponse);

    return 0;

}



