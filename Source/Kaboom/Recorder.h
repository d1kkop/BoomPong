// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Serialization/Archive.h"
#include "Recorder.generated.h"


USTRUCT()
struct FRecordSample
{
	GENERATED_USTRUCT_BODY()

	FRecordSample() { FMemory::Memzero(*this); }

	FVector m_Pos;
	FQuat   m_Quat;
	float	m_Time;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KABOOM_API URecorder : public UActorComponent
{
	GENERATED_BODY()

public:	
	URecorder();
	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	virtual void Sample();

	UFUNCTION(BlueprintCallable, Category ="Record")
		void StartRecord();

	UFUNCTION(BlueprintCallable, Category ="Record")
		void StopRecord();

	UFUNCTION(BlueprintCallable, Category = "Record")
		void SaveRecord(const FString& name);

protected:
	UPROPERTY() bool  m_Recording;
	UPROPERTY() float m_Time;
	UPROPERTY() float m_ResampleTime;
	UPROPERTY() int   m_NumSamples;

	FBufferArchive m_Archive;
	
	// Set sample interval in seconds
	UPROPERTY(EditAnywhere, Category ="Record")
		float m_SampleInterval;
};
