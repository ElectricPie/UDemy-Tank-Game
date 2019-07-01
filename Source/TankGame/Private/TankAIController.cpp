// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();

	//Checks that the player is possesing a tank
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller not posessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller is possesing: %s"), *(controlledTank->GetName()));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}