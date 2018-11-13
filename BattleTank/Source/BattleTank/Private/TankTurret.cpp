// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"
#include "BattleTank.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	//float dummy = GetWorld()->DeltaTimeSeconds();
	auto Time = GetWorld()->GetTimeSeconds();
	//auto TimeSeconds = GetWorld()->GetTimeSeconds();

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = 0.f;
	//RotationChange = GetWorld()->DeltaTimeSeconds() * RelativeSpeed * MaxDegreesPerSecond;
	RotationChange = Time * RelativeSpeed * MaxDegreesPerSecond;
	auto Rotation = RelativeRotation.Yaw + RotationChange; // 

	SetRelativeRotation(FRotator(0,Rotation, 0));

	//UE_LOG(LogTemp, Warning, TEXT("%f Aim Solution Found at : %f"), Time, RelativeSpeed);
}
