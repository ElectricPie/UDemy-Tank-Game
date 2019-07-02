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

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() 
{
	//Checks that the player has possesd a tank
	if (!GetControlledTank()) {
		return;
	}

	FVector hitLocation; //Out parameter

	if (GetSightRayHitLocation(hitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *hitLocation.ToString())
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const
{
	//Find the crosshairs pixle position
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	auto screenLocation = FVector2D(viewportSizeX * m_crosshairXLocation, viewportSizeY * m_crosshairYLocation);

	return true;
}
