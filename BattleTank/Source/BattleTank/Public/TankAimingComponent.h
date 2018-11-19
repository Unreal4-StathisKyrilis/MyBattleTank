// Copyright Stathis Kyrilis

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h" 
#include "TankAimingComponent.generated.h"

//Enum for Aiming State
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

// forward declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

//Hold barrels's properties and elevate method
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

protected :
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Locked;


private:
	UTankAimingComponent();

	void MoveBarelTowards(FVector AimDirection);

	UTankBarrel* Barell = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 4000; // 0.40m/s   starting value

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	//UPROPERTY(EditAnywhere, Category = "Firing")	// each tank has its own firing rate
	UPROPERTY(EditDefaultsOnly, Category = "Firing") // all tanks has the same firing speed
		float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;


};
