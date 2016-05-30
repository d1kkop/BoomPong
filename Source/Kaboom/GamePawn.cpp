// Fill out your copyright notice in the Description page of Project Settings.

#include "Kaboom.h"
#include "GamePawn.h"
#include "PawnMovement.h"


AGamePawn::AGamePawn()
{
	PrimaryActorTick.bCanEverTick = true;
	m_Movement = CreateDefaultSubobject<UPawnMovement>(TEXT("MovementAA"));
}

void AGamePawn::BeginPlay()
{
	Super::BeginPlay();
}

void AGamePawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AGamePawn::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis( FName(TEXT("Forward")), this, &AGamePawn::OnInputForward );
	InputComponent->BindAxis( FName(TEXT("Strafe")),  this, &AGamePawn::OnInputStrafe );
}

void AGamePawn::OnInputForward(float value)
{
	if (m_Movement)
	{
		m_Movement->AddForwardInput( value );
	}
}

void AGamePawn::OnInputStrafe(float value)
{
	if (m_Movement)
	{
		m_Movement->AddStrafeInput( value );
	}
}

