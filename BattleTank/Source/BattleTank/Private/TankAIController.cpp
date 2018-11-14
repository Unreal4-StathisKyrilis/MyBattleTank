// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "BattleTank.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (PlayerTank)
	{
		//move towards to player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

		// Aim towards to player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		
		// TODO dont fire Evere frame

		// Fire every frame
		ControlledTank->Fire();

	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();


}
