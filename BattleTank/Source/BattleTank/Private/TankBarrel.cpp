// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"
#include "BattleTank.h"




void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Move the Barel the right ammount this frame
	//Given a max elevation speed, and the frame time
	//float dummy = GetWorld()->DeltaTimeSeconds();
	auto Time = GetWorld()->GetTimeSeconds();
	//auto TimeSeconds = GetWorld()->GetTimeSeconds();

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = 0.f;
	//ElevationChange = GetWorld()->DeltaTimeSeconds() * RelativeSpeed * MaxDegreesPerSecond;
	ElevationChange = Time * RelativeSpeed * MaxDegreesPerSecond;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(Elevation, 0, 0));

	UE_LOG(LogTemp, Warning, TEXT("%f Aim Solution Found at : %f"), Time,RelativeSpeed);
}
