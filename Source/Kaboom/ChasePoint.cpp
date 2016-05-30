// Fill out your copyright notice in the Description page of Project Settings.

#include "Kaboom.h"
#include "ChasePoint.h"
#include "MathUtility.h"


UChasePoint::UChasePoint() :
	m_FollowStrength(5.f),
	m_RotateFollowStrength(5.f)
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


void UChasePoint::BeginPlay()
{
	Super::BeginPlay();
}


void UChasePoint::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	float dt = DeltaTime;

	if ( !m_Target || m_Target->IsPendingKill() )
		return;

	UpdateLocation( FMathUtility::Smooth(m_FollowStrength, dt) );
	UpdateRotation( FMathUtility::Smooth(m_RotateFollowStrength, dt) );
}

void UChasePoint::SetFollowTarget(const AActor* target)
{
	m_Target = target;
	if ( m_Target )
	{
		UpdateLocation( 1.f );
		UpdateRotation( 1.f );
	}
}

const AActor* UChasePoint::GetFollowTarget() const
{
	return m_Target;
}

void UChasePoint::UpdateLocation(float smooth)
{
	FVector ownLoc		 = GetComponentLocation();
	FVector targetLoc	 = m_Target->GetActorLocation() + m_Target->GetActorQuat() * m_FollowOffset;
	ownLoc				+= (targetLoc - ownLoc) * smooth;
	SetWorldLocation(ownLoc, m_Sweep);
}

void UChasePoint::UpdateRotation(float smooth)
{
	FVector viewDir = m_TargetOffset - m_FollowOffset;
	FQuat targetRot = m_Target->GetActorQuat() * viewDir.Rotation().Quaternion();
	FQuat ownRot	= FQuat::Slerp(GetComponentQuat(), targetRot, smooth);
	SetWorldRotation(ownRot, m_Sweep);
}

