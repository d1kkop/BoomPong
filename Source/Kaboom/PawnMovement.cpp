// Fill out your copyright notice in the Description page of Project Settings.

#include "Kaboom.h"
#include "PawnMovement.h"


UPawnMovement::UPawnMovement() :
	m_MoveStrength(100000),
	m_MoveFriction(3)
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UPawnMovement::BeginPlay()
{
	Super::BeginPlay();
	ClearInput();
}

void UPawnMovement::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	float dt = DeltaTime;

	// Normalize input so that strafing and moving forward does not provide an advantage
	FVector input(m_FowardInput, m_StrafeInput, 0);
	input.Normalize();

	m_Velocity += input * m_MoveStrength * dt;
	m_Velocity *= FMath::Pow( .5f, m_MoveFriction );
	
	FHitResult hit;
	GetOwner()->AddActorLocalOffset( m_Velocity * dt, true, &hit );

	ClearInput();
}

void UPawnMovement::AddForwardInput(float input)
{
	m_FowardInput += input;
}

void UPawnMovement::AddStrafeInput(float input)
{
	m_StrafeInput += input;
}

void UPawnMovement::ClearInput()
{
	m_FowardInput = 0;
	m_StrafeInput = 0;
}

