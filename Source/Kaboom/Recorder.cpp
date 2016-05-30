// Fill out your copyright notice in the Description page of Project Settings.

#include "Kaboom.h"
#include "Recorder.h"


// Sets default values for this component's properties
URecorder::URecorder() :
	m_SampleInterval(.05f)
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void URecorder::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void URecorder::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if ( !m_Recording )
		return;

	if (m_Time == 0.f || m_ResampleTime > m_SampleInterval)
	{
		Sample();
		m_ResampleTime = 0;
	}

	m_Time		   += DeltaTime;
	m_ResampleTime += DeltaTime;
}

void URecorder::Sample()
{
	FRecordSample sample;
	
	sample.m_Pos  = GetOwner()->GetActorLocation();
	sample.m_Quat = GetOwner()->GetActorQuat();
	sample.m_Time = m_Time;

	m_Archive << sample.m_Pos;
	m_Archive << sample.m_Quat;
	m_Archive << m_Time;

	m_NumSamples++;
}

void URecorder::StartRecord()
{
	m_Archive.FlushCache();
	m_Archive.Empty();
	m_Recording = true;
	m_Time = 0;
	m_NumSamples = 0;
	m_Archive << m_NumSamples;
}

void URecorder::StopRecord()
{
	m_Recording = false;
}

void URecorder::SaveRecord(const FString& name)
{
	// Write num samples at start of file
	int64 p = m_Archive.Tell();
	m_Archive.Seek( 0 );
	m_Archive << m_NumSamples;
	m_Archive.Seek( p );

	FFileHelper::SaveArrayToFile(m_Archive, *name);
}

