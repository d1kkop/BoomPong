// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Ball.generated.h"

UCLASS()
class KABOOM_API ABall : public APawn
{
	GENERATED_BODY()

public:
	ABall();
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	// Directional force where length of force is its strength.
	UFUNCTION(BlueprintCallable, Category = Ball)
	void AddForce( const FVector& force );

	// Angular force where length of vector describes the amount of rotation in deg/s, dir is axis of rotation.
	UFUNCTION(BlueprintCallable, Category = Ball)
	void AddSpin( const FVector& angForce );

	UPROPERTY(EditAnywhere, Category = Ball) 
		float m_Friction;
	UPROPERTY(EditAnywhere, Category = Ball)
		float m_Drag;
	UPROPERTY(EditAnywhere, Category = Ball)
		float m_GravityForce;
	UPROPERTY(EditAnywhere, Category = Ball)
		float m_VelocityFactorOnBounce;
	UPROPERTY(EditAnywhere, Category = Ball)
		float m_VelocityAddFromSpinFactor;
	UPROPERTY(EditAnywhere, Category = Ball)
		float m_SpinAddFromVelocityFactor;

protected:
	UPROPERTY() FVector m_Velocity;
	UPROPERTY() FVector m_AngVelocity;
	UPROPERTY() FVector m_PrevPos;
};
