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
	Locked,
	OutOfAmmo
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

	bool IsBarrelMoving();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	EFiringState GetFiringState() const;
	
	
	UFUNCTION(BlueprintCallable, Category = "Firing")
		int32 GetRoundsLeft() const;


protected :
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Reloading;
	
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;


private:
	UTankAimingComponent();



	void MoveBarelTowards(FVector AimDirection);

	UTankBarrel* Barell = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;
	
	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 4000; // 0.40m/s   starting value
	   
	//UPROPERTY(EditAnywhere, Category = "Firing")	// each tank has its own firing rate
	UPROPERTY(EditDefaultsOnly, Category = "Firing") // all tanks has the same firing speed
		float ReloadTimeInSeconds = 1;

	double LastFireTime = 0;

	FVector AimDirection;
	
	UPROPERTY(VisibleAnyWhere)
	int32 RoundsLeft = 20; // Inital Tank Ammo


};
