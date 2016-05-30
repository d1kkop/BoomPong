// Fill out your copyright notice in the Description page of Project Settings.

#include "Kaboom.h"
#include "Bat.h"
#include "PawnMovement.h"


ABat::ABat()
{
	PrimaryActorTick.bCanEverTick = true;

//	m_Bat = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bat"));
	//RootComponent = m_Bat;

	//m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//m_Camera->AttachParent = nullptr;
}

void ABat::BeginPlay()
{
	Super::BeginPlay();
}

void ABat::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	float s = 1.f;
	this->AddActorWorldOffset(FVector(0, -m_HorizonInput, m_VerticalInput) * s, false);

	ClearInput();
}

void ABat::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis( FName(TEXT("MouseX")), this, &ABat::OnMouseX );
	InputComponent->BindAxis( FName(TEXT("MouseY")),  this, &ABat::OnMouseY );
}

void ABat::OnMouseX(float x)
{
	m_HorizonInput += x;
}

void ABat::OnMouseY(float y)
{

	m_VerticalInput += y;
}

void ABat::ClearInput()
{
	m_VerticalInput = 0;
	m_HorizonInput = 0;
}
