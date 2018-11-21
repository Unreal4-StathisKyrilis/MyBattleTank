// Copyright Stathis Kyrilis


#include "Tank.h"
#include "BattleTank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DamageAmount: %f, DamageToApply:%i, HealthLeft:%i"), DamageAmount, DamageToApply, CurrentHealth)
	}

		//float dummy = (float)DamageToApply;
		//return dummy;

		return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}
