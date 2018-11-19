// Copyright Stathis Kyrilis

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h" 
#include "Projectile.h"


//class UTankBarrel; // forward declaration

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barell = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	auto TankName = GetOwner()->GetName();
	//auto BarelLocation = Barell->GetComponentLocation().ToString();
	if (!ensure(Barell)) { return; }
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
	if (!ensure(Barell) || (!ensure(Turret))) { return; }
	auto BarelRotation = Barell->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarelRotation;


	Barell->Elevate(DeltaRotator.Pitch); // -1...1
	Turret->Rotate(DeltaRotator.Yaw);

}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barell && ProjectileBlueprint)) { return; }

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (isReloaded) {
		// spawn a projectile at the socket location on the  barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint, 
			Barell->GetSocketLocation(FName("Projectile")),
			Barell->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}

}