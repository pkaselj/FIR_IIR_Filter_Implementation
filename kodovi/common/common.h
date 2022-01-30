#ifndef COMMON_H
#define COMMON_H

void InitializeToZero(double* array, int N);
void TransformToStep(double* array, int N, double fAmplitude);
void TransformToImpulse(double* array, int N);
void WritedoubleArrayToFile(double* array, int N, const char szFileName[]);

#endif // !COMMON_H


