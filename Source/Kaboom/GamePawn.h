// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "GamePawn.generated.h"

UCLASS()
class KABOOM_API AGamePawn : public APawn
{
	GENERATED_BODY()

public:
	AGamePawn();
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void OnInputForward(float value);
	void OnInputStrafe(float value);

	UPROPERTY() class UPawnMovement* m_Movement;
};
