 // Copyright Stathis Kyrilis

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "Tank_PlayerController_in_c.generated.h"

class UTankAimingComponent;

/**
 * helps the player Aim !!!
 */
UCLASS()
class BATTLETANK_API ATank_PlayerController_in_c : public APlayerController
{
	GENERATED_BODY()

protected :
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);



public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	//Start the Tank moving the barrel so tha a shot would 
	void AimTowardsCrossHair();

	// return an OUT parameter, true if hit the landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.3333;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;
};
