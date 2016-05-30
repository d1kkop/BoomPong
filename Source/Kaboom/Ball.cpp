// Fill out your copyright notice in the Description page of Project Settings.

#include "Kaboom.h"
#include "Ball.h"
#include "MathUtility.h"


ABall::ABall() :
	m_Friction(0.1f),
	m_Drag(1.1f),
	m_GravityForce(-700),
	m_VelocityFactorOnBounce(.95f),
	m_VelocityAddFromSpinFactor(.9f),
	m_SpinAddFromVelocityFactor(.9f)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	m_PrevPos = GetActorLocation();
}

void ABall::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	float dt = DeltaTime;

	m_Velocity.Z	 += m_GravityForce * dt;
	m_Velocity		 *= FMath::Pow( .5f, dt * m_Friction );
	m_AngVelocity	 *= FMath::Pow( .5f, dt * m_Drag );

	FHitResult hit;
	FVector timedVel = m_Velocity * dt;
	AddActorWorldOffset( timedVel, true, &hit );
	if ( hit.IsValidBlockingHit() )
	{
		// Compute some derivatives
		float oldVelSpeed		= m_Velocity.Size();
		float radius			= FVector::Dist( hit.ImpactPoint, GetActorLocation() );
		float circumference		= 2 * PI * radius;

		// Add velocity from spin
		FVector velAddFromSpin  = FVector::CrossProduct( m_AngVelocity, hit.ImpactNormal ).GetSafeNormal();
		m_Velocity			   += velAddFromSpin * m_AngVelocity.Size() * circumference * m_VelocityAddFromSpinFactor;

		// Clamp velocity to max 
		float maxVel		    = FMath::Max(m_AngVelocity.Size() * circumference, oldVelSpeed);
		m_Velocity			   *= FMath::Min(1.f, oldVelSpeed / m_Velocity.Size());

		// Compute spinning factor based on incoming velocity compared to normal
		float nDotV				= FVector::DotProduct( hit.ImpactNormal, (-m_Velocity).GetSafeNormal() );
		nDotV					= FMath::Clamp(nDotV, -0.9999f, .9999f);
		float spinAngFactor		= FMath::Acos( FMath::Abs(nDotV) ) / (PI *.5f) * FMath::Sign(nDotV);

		// Add spin from (old velocity)
		FVector rotAxis			= FVector::CrossProduct( hit.ImpactNormal, m_Velocity ).GetSafeNormal();
		float spinsPerSecAdd	= oldVelSpeed / circumference;
		FVector spinAdd			= rotAxis * spinAngFactor * spinsPerSecAdd * m_SpinAddFromVelocityFactor;
		m_AngVelocity			+= spinAdd;

		// Clamp max spining to (old) velocity
		m_AngVelocity		   *= FMath::Min(1.f, oldVelSpeed / (m_AngVelocity.Size() * circumference));

		m_Velocity  = FMath::GetReflectionVector( m_Velocity, hit.ImpactNormal );
	}

	AddActorWorldRotation( FQuat(m_AngVelocity.GetSafeNormal(), m_AngVelocity.Size() * dt * 2 * PI), false );

	m_PrevPos = GetActorLocation();
}

void ABall::AddForce(const FVector& force)
{
	m_Velocity += force;
}

void ABall::AddSpin(const FVector& angForce)
{
	m_AngVelocity += angForce;
}
