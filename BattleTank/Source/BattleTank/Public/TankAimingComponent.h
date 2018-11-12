// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h" 
#include "TankAimingComponent.generated.h"

// forward declaration
class UTankBarrel; 

//Hold barrels's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void SetBarellReference(UTankBarrel* BarrelToSet );

	void AimAt(FVector HitLocation, float LaunchSpeed);

	//TODO add SetTurret Reference

	void MoveBarelTowards(FVector AimDirection);

//private:
	UTankBarrel* Barell = nullptr;
		
};
