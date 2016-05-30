// Fill out your copyright notice in the Description page of Project Settings.

#include "Kaboom.h"
#include "Components/SplineComponent.h"
#include "FollowSpline.h"


UFollowSpline::UFollowSpline() :
	m_AccelSpeed(1000),
	m_TurboSpeed(600),
	m_Friction(3),
	m_AccelerateMinMaxTime(10, 20),
	m_TurboMinMaxTime(5, 12)
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UFollowSpline::BeginPlay()
{
	Super::BeginPlay();
	m_FollowState = FollowState::NotStarted;

	for (TObjectIterator<USplineComponent> Itr; Itr; ++Itr)
	{
		if (Itr->GetWorld() != GetWorld())
		{
			continue;
		}
		
		m_Spline = *Itr;
		break;
	}
}

void UFollowSpline::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	float dt = DeltaTime;

	if( !m_Spline )
		return;

	UpdateBehaviour( dt );
	UpdateMovement ( dt );
}

void UFollowSpline::UpdateBehaviour(float dt)
{
	m_Time += dt;

	switch (m_FollowState)
	{
	case FollowState::NotStarted:
		m_Time = 0;
		m_TargetTime = FMath::RandRange(m_AccelerateMinMaxTime.X, m_AccelerateMinMaxTime.Y);
		m_FollowState = FollowState::Accelerate;
		break;

	case FollowState::Accelerate:
		m_Time += dt;
		if (m_Time >= m_TargetTime)
		{
			m_Time = 0;
			m_TargetTime = FMath::RandRange(m_TurboMinMaxTime.X, m_TurboMinMaxTime.Y);
		}
		break;

	case FollowState::Turbo:
		m_Time += dt;
		if (m_Time >= m_TargetTime)
		{
			m_FollowState = FollowState::NotStarted;
		}
		break;
	}
}

void UFollowSpline::UpdateMovement(float dt)
{
	float totalAccel = 0;

	if (m_FollowState == FollowState::Accelerate)
		totalAccel = m_AccelSpeed;
	else if (m_FollowState == FollowState::Accelerate)
		totalAccel = m_TurboSpeed + m_AccelSpeed;

	m_Velocity += totalAccel * dt;
	m_Velocity *= FMath::Pow( .5f, dt * m_Friction );

	m_Distance += m_Velocity * dt;

	FVector  pos = m_Spline->GetWorldLocationAtDistanceAlongSpline( m_Distance );
	FRotator rot = m_Spline->GetWorldRotationAtDistanceAlongSpline( m_Distance );

	GetOwner()->SetActorLocation( pos, false );
	GetOwner()->SetActorRotation( rot );
}

