// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"

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

	auto playerTank = GetPlayerTank();

	//Error check to prevent pointer issues
	if (!playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No player tank in world"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Targeting: %s"), *(playerTank->GetName()));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank()) {
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}