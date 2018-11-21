// Copyright Stathis Kyrilis

#include "TankAIController.h"
#include "Engine/World.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h" // We need it for the OnDeath Event

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	
	if (!ensure(PlayerTank && ControlledTank)) { return; }
	//move towards to player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

	// Aim towards to player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
		
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
	
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PosessedTank = Cast<ATank>(InPawn);
		if (!ensure(PosessedTank)) { return; }

		//Subscribe our local method to the Tank Death Event
		PosessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPosessedTankDeath);
	}
}

void ATankAIController::OnPosessedTankDeath()
{

	UE_LOG(LogTemp, Warning, TEXT("Death"));

}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();


}
