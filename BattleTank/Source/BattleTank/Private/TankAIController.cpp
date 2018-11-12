// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "BattleTank.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		// ToDo move towards to player

		// ToDo Aim towards to player
		GetAIControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// ToDo Fire at player if ready

	}
}

ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());

}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }

	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller cant Find Player Tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller Found Player Tank Named : %s"),*PlayerTank->GetName());
	}
}
