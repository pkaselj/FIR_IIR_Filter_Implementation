#include<stdio.h>
#include<string.h>

void InitializeToZero(double* array, int N)
{
    memset(array, 0, N);
}

void TransformToStep(double* array, int N, double fAmplitude)
{
    int i;
    for (i = 0; i < N; i++)
    {
        array[i] = fAmplitude;
    }
}

void TransformToImpulse(double* array, int N)
{
    memset(array, 0, N);
    array[0] = 1;
}

void WritedoubleArrayToFile(double* array, int N, const char szFileName[])
{
    FILE* hFile = NULL;
    fopen_s(&hFile, szFileName, "w");

    if (!hFile)
    {
        exit(-1);
        return;
    }

    const int iElementsPerLine = 1;
    int i;
    for (i = 0; i < N; i++)
    {
        fprintf_s(hFile, "%lf, ", array[i]);
        if (i % iElementsPerLine == 0)
        {
            fprintf_s(hFile, "\n");
        }
    }

    fclose(hFile);
}