#ifndef COMMON_H
#define COMMON_H

void InitializeToZero	(double pArray[], int N							);
void TransformToStep	(double pArray[], int N, double fAmplitude		);
void TransformToImpulse	(double pArray[], int N							);
void WriteArrayToFile	(double pArray[], int N, const char szFileName[] );

#endif // !COMMON_H


