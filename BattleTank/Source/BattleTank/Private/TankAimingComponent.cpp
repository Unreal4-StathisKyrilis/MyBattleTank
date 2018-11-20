// Copyright Stathis Kyrilis

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h" 
#include "ConstructorHelpers.h"
#include "Projectile.h"


//class UTankBarrel; // forward declaration

// UTankAimingComponent Constructor. Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	//Sets manually the AimingComponenent to ProjectileBP due to a bug , cant save it in Unreal Editor)
		static ConstructorHelpers::FClassFinder<AProjectile> Proj(TEXT("/Game/3D/Tank/Projectile_BP"));
		if (Proj.Class)
		{
			ProjectileBlueprint = Proj.Class;
		}
		PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	//wait the initial reload time before firing
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (RoundsLeft<=0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;

	}

	//TODO Handle aiming and Firing State
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}
EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}




void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barell = BarrelToSet;
	Turret = TurretToSet;
}

bool UTankAimingComponent::IsBarrelMoving()
{

	if (!ensure(Barell)) { return false; }
	auto BarrelForward = Barell->GetForwardVector();
	return (!BarrelForward.Equals(AimDirection, 0.01)); // not equal
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	auto TankName = GetOwner()->GetName();
	//auto BarelLocation = Barell->GetComponentLocation().ToString();
	if (!ensure(Barell)) { return; }
		FVector OutLaunchVelocity(0);                               
		FVector StartLocation = Barell->GetSocketLocation(FName("Projectile"));
		TArray<AActor*> ActorIgnoreList;
		ActorIgnoreList.Add(GetOwner());
		ActorIgnoreList.Add(GetWorld()->GetFirstPlayerController()->GetPawn());


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
			ESuggestProjVelocityTraceOption::DoNotTrace,
			FCollisionResponseParams::DefaultResponseParam,
			ActorIgnoreList,
			false); // Draw Line of Trajectory
		

		if (bHaveAimSolution)
		{
			AimDirection = OutLaunchVelocity.GetSafeNormal();
			MoveBarelTowards(AimDirection);
			//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 5.f);

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

	// always , yaw the shortest way 
	Barell->Elevate(DeltaRotator.Pitch); // -1...1
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else // avoid going the long way
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Fire()
{
	if ((FiringState == EFiringState::Locked) || (FiringState == EFiringState::Aiming))
	{
		if (!ensure(Barell && ProjectileBlueprint)) { return; }
		// spawn a projectile at the socket location on the  barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint, 
			Barell->GetSocketLocation(FName("Projectile")),
			Barell->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}

}



