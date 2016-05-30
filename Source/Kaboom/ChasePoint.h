// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "ChasePoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KABOOM_API UChasePoint : public USceneComponent
{
	GENERATED_BODY()

public:
	UChasePoint();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = ChasePoint)
	void SetFollowTarget(const AActor* follow);
	const AActor* GetFollowTarget() const;

	void UpdateLocation(float smooth);
	void UpdateRotation(float smooth);


protected:
	UPROPERTY() const AActor* m_Target;

	UPROPERTY(EditAnywhere, Category = "Behaviour")
		float m_FollowStrength;
	UPROPERTY(EditAnywhere, Category = "Behaviour")
		float m_RotateFollowStrength;

	UPROPERTY(EditAnywhere, Category = "Behaviour")
		FVector m_FollowOffset;
	UPROPERTY(EditAnywhere, Category = "Behaviour")
		FVector m_TargetOffset;

	UPROPERTY(EditAnywhere, Category = "Behaviour")
		bool m_Sweep;
};
