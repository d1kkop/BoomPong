// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Bat.generated.h"

UCLASS()
class KABOOM_API ABat : public APawn
{
	GENERATED_BODY()

public:
	ABat();
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void OnMouseX(float x);
	void OnMouseY(float y);
	void ClearInput();

	UPROPERTY(EditAnywhere, Category = Bat) UStaticMeshComponent* m_Bat;
	UPROPERTY(EditAnywhere, Category = Bat) UCameraComponent* m_Camera;
	UPROPERTY() float m_VerticalInput;
	UPROPERTY() float m_HorizonInput;
};
