// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "BattleTank.h"



void UTankBarrel::Elevate(float DegreesPerSecond)
{
	//Move the Barel the right ammount this frame
	//Given a max elevation speed, and the frame time

	UE_LOG(LogTemp, Warning, TEXT("Barrel Elevate Called at speed %f"),DegreesPerSecond);
}
