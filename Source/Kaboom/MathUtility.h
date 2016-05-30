// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
struct KABOOM_API FMathUtility
{
	static float Smooth(float strength, float dt);
	static void  ClampVec(FVector& vec, float toLength);
};
