// Fill out your copyright notice in the Description page of Project Settings.

#include "Kaboom.h"
#include "RecordPlayer.h"

URecordPlayer::URecordPlayer() :
	m_PlaySpeed(1),
	m_PrevSampleIdx(-1)
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void URecordPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void URecordPlayer::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if ( !m_Playing || m_Paused )
		return;

	Sample();
	m_Time += DeltaTime * m_PlaySpeed;
}

void URecordPlayer::Sample()
{
	if (m_Samples.Num() <= 0)
		return;

	if (m_Samples.Num() == 1)
	{
		FRecordSample& sample = m_Samples[0];
		GetOwner()->SetActorLocation( sample.m_Pos );
		GetOwner()->SetActorRotation( sample.m_Quat );
		return;
	}

	for ( int i = FMath::Max(0, m_PrevSampleIdx); i < m_Samples.Num()-1; i++ )
	{
		FRecordSample& sample	  = m_Samples[i];
		FRecordSample& nextSample = m_Samples[i + 1];
		if (m_Time >= sample.m_Time  && m_Time <= nextSample.m_Time)
		{
			float alpha = (m_Time - sample.m_Time) / (nextSample.m_Time - sample.m_Time);
			FVector p   = FMath::Lerp(sample.m_Pos, nextSample.m_Pos, alpha);
			FQuat   q   = FQuat::Slerp(sample.m_Quat, nextSample.m_Quat, alpha);

			GetOwner()->SetActorLocation( p, false );
			GetOwner()->SetActorRotation( q );

			m_PrevSampleIdx = i;
			break;
		}
	}
}

void URecordPlayer::Load(const FString& name)
{
	TArray<uint8> buffer;
	if ( FFileHelper::LoadFileToArray(buffer, *name) )
	{
		FMemoryReader reader(buffer, true);
		m_PrevSampleIdx = -1;

		int numSamples = 0;
		reader << numSamples;
		m_Samples.Empty( numSamples );

		for(int i = 0; i < numSamples; i++)
		{
			FRecordSample sample;
			reader << sample.m_Pos;
			reader << sample.m_Quat;
			reader << sample.m_Time;

			m_Samples.Add( sample );
		}
	}
}

void URecordPlayer::Play(float overrideSpeed)
{
	m_Playing = true;
}

void URecordPlayer::Pause()
{
	m_Paused = true;
}

void URecordPlayer::Resume()
{
	m_Paused = false;
}

void URecordPlayer::GotoNextSample()
{

}

void URecordPlayer::GotoPrevSample()
{

}

