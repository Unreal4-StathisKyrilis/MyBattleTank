// Copyright Stathis Kyrilis

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track is used to set max. driving force and to apply forces to the Tank,
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public :
	// sets a throttle between -1 to +1
	UFUNCTION(BlueprintCallable, Category="Input")
		void SetThrottle(float Throttle);

	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
		// assume 40 Tones Tank and 1g acceleration
		float TrackMaxDrivingForce = 40000000;

protected :

	UTankTrack();

	void ApplySidewaysForce();

	virtual void BeginPlay() override;

private :



	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void DriveTrack();

	float CurrentThrottle = 0;


};
