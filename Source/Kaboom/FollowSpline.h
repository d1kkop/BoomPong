// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "FollowSpline.generated.h"

UENUM() // BlueprintType
enum class FollowState : uint8
{
	NotStarted,
	Accelerate,
	Turbo
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KABOOM_API UFollowSpline : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFollowSpline();
	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	virtual void UpdateBehaviour(float dt);
	virtual void UpdateMovement(float dt);

protected:
	UPROPERTY() float m_Distance;
	UPROPERTY() float m_Velocity;
	UPROPERTY() float m_Time;
	UPROPERTY() float m_TargetTime;
	UPROPERTY() FollowState m_FollowState;
	UPROPERTY() class USplineComponent* m_Spline;

	// Forward acceleration (normal speed)
	UPROPERTY(EditAnywhere, Category = "MoveSpline")
		float m_AccelSpeed;

	// Forward turbo (added on top of accel)
	UPROPERTY(EditAnywhere, Category = "MoveSpline")
		float m_TurboSpeed;

	// Friction applied to velocity
	UPROPERTY(EditAnywhere, Category = "MoveSpline")
		float m_Friction;

	// Random time between min/max to do normal accelerating
	UPROPERTY(EditAnywhere, Category = "MoveSpline")
		FVector2D m_AccelerateMinMaxTime;

	// Random time between min/max to do turboing
	UPROPERTY(EditAnywhere, Category = "MoveSpline")
		FVector2D m_TurboMinMaxTime;
};
