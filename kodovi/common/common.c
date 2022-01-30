#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void InitializeToZero(double pArray[], int N)
{
    memset(pArray, 0, N);
}

void TransformToStep(double pArray[], int N, double fAmplitude)
{
    int i;
    for (i = 0; i < N; i++)
    {
        pArray[i] = fAmplitude;
    }
}

void TransformToImpulse(double pArray[], int N)
{
    memset(pArray, 0, N);
    pArray[0] = 1;
}

void WriteArrayToFile(double pArray[], int N, const char szFileName[])
{
    FILE* hFile = NULL;
    errno_t error = fopen_s(&hFile, szFileName, "w");

    if (error || !hFile)
    {
        exit(-1);
        return;
    }

    const int N_ElementsPerLine = 1;
    int i;
    for (i = 0; i < N; i++)
    {
        fprintf_s(hFile, "%lf, ", pArray[i]);
        if (i % N_ElementsPerLine == 0)
        {
            fprintf_s(hFile, "\n");
        }
    }

    fclose(hFile);
}