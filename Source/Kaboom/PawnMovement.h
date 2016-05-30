// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PawnMovement.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KABOOM_API UPawnMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPawnMovement();
	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void AddForwardInput(float input);
	void AddStrafeInput (float input);
	void ClearInput();

protected:
	UPROPERTY() float	m_FowardInput;
	UPROPERTY() float	m_StrafeInput;
	UPROPERTY() FVector m_Velocity;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
		float m_MoveStrength;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float m_MoveFriction; 
};
