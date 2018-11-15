// Copyright Stathis Kyrilis

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


//Forward Declarations
class UTankBarrel;
class UTankAimingComponent;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 4000; // 0.40m/s   starting value

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;  

	//UPROPERTY(EditAnywhere, Category = "Firing")	// each tank has its own firing rate
	UPROPERTY(EditDefaultsOnly, Category = "Firing") // all tanks has the same firing speed
		float ReloadTimeInSeconds = 3;
	
	double LastFireTime = 0;

	//local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr; //TODO Remove

protected:
	UPROPERTY(BlueprintReadOnly)
		UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
		UTankMovementComponent* TankMovementComponent = nullptr;


public:	
	void AimAt(FVector HitLocation);
	
	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();
};
