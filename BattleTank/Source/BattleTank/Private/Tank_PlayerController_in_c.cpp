// Copyright Stathis Kyrilis

#include "Tank_PlayerController_in_c.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATank_PlayerController_in_c::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetPawn();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATank_PlayerController_in_c::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}


void ATank_PlayerController_in_c::AimTowardsCrossHair()
{
	if (!GetPawn()) { return; } //eg if not posessing a Tank
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation;
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if (bGotHitLocation) 
		{
			AimingComponent->AimAt(HitLocation);
		}
}
// Get world location of lineTrace through Crosshair, true if hits landscape
bool ATank_PlayerController_in_c::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	// find the crosshair position in pixel Coordinates
	int32 ViewportSizeX, ViewPortSizeY;
	GetViewportSize(ViewportSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation, ViewPortSizeY*CrosshairYLocation);
	
	//" De-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line trace along that look direction , an see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return false;
}

bool ATank_PlayerController_in_c::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection*LineTraceRange);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetPawn());

	if (GetWorld()->LineTraceSingleByChannel( 
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility,
		Params)
		)
	{ //IF Line Trace Succeeds
		//set hit location;
		HitLocation = HitResult.Location;
		return true;

	}
	HitLocation = FVector(0);
	return false; // Line Trace Didnt succed
}

bool ATank_PlayerController_in_c::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);

}
