// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Serialization/Archive.h"
#include "Recorder.h"
#include "RecordPlayer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KABOOM_API URecordPlayer : public UActorComponent
{
	GENERATED_BODY()

public:	
	URecordPlayer();
	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	virtual void Sample();

	UFUNCTION(BlueprintCallable, Category ="Player")
		void Load(const FString& name);

	UFUNCTION(BlueprintCallable, Category ="Player")
		void Play(float overrideSpeed = -1);

	UFUNCTION(BlueprintCallable, Category ="Player")
		void Pause();

	UFUNCTION(BlueprintCallable, Category ="Player")
		void Resume();

	UFUNCTION(BlueprintCallable, Category ="Player")
		void GotoNextSample();

	UFUNCTION(BlueprintCallable, Category ="Player")
		void GotoPrevSample();

protected:
	UPROPERTY() bool  m_Playing;
	UPROPERTY() bool  m_Paused;
	UPROPERTY() float m_Time;
	UPROPERTY() int32 m_PrevSampleIdx;
	UPROPERTY() TArray<FRecordSample> m_Samples;
	

	UPROPERTY(EditAnywhere, Category ="Player") 
		float m_PlaySpeed;
	
};
