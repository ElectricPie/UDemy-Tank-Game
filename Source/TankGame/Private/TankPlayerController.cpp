// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();

	//Checks that the player is possesing a tank
	if (!controlledTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller not posessing a tank"));
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller is possesing: %s"), *(controlledTank->GetName()));
	}
}

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}