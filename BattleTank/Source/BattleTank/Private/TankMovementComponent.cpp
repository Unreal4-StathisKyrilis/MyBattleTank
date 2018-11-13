// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "BattleTank.h"

void UTankMovementComponent::Initilise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}

void UTankMovementComponent::IntendMoveForward(float Throw)
{



	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	// TODO Prevent double speed when using 2 methods at the same time

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{

	//auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("Intend Turn Right :%f"), Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	// TODO Prevent double speed when using 2 methods at the same time

}