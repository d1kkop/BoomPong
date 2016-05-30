// Fill out your copyright notice in the Description page of Project Settings.

#include "Kaboom.h"
#include "MathUtility.h"

float FMathUtility::Smooth(float strength, float dt)
{
	return 1.f - FMath::Pow( .5f, strength * dt );
}

void FMathUtility::ClampVec(FVector& vec, float toLength)
{
	vec *= FMath::Min(1.f, toLength / vec.Size());
}
