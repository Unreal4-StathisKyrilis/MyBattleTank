// Copyright Stathis Kyrilis

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected :

	//How close AI Tank gets to the player (in cm)
	UPROPERTY(EditDefaultsOnly, Category = "Setup") // TODO Consider putting EditDefaultsOnly here
		float AcceptanceRadius = 10000;

private :
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


	
};



