// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h" 



class UTankBarrel; // forward declaration

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::SetBarellReference(UTankBarrel * BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barell = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}



void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	auto TankName = GetOwner()->GetName();
	//auto BarelLocation = Barell->GetComponentLocation().ToString();
	if (!Barell) { return; }
		FVector OutLaunchVelocity(0);                               
		FVector StartLocation = Barell->GetSocketLocation(FName("Projectile"));
		bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);

		if (bHaveAimSolution)
		{
			auto AimDirection = OutLaunchVelocity.GetSafeNormal();
			MoveBarelTowards(AimDirection);

		} else {
			//if no solution do nothing
		}
}

void UTankAimingComponent::MoveBarelTowards(FVector AimDirection)
{

	//Wok-out Difference of Current Barel Rotation and Aim Direction
	auto BarelRotation = Barell->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarelRotation;


	Barell->Elevate(DeltaRotator.Pitch); // -1...1
	Turret->Rotate(DeltaRotator.Yaw);

}