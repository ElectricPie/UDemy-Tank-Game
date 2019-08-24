// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"


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
		GetControlledTank()->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const
{
	//Find the crosshairs pixle position
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	auto screenLocation = FVector2D(viewportSizeX * m_crosshairXLocation, viewportSizeY * m_crosshairYLocation);

	//Deproject

	FVector lookDirection;

	if (GetLookDirection(screenLocation, lookDirection))
	{
		FVector hitLocation;

		if (GetLookVectorHitLocation(hitLocation, lookDirection)) {
			//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *hitLocation.ToString());
			outHitLocation = hitLocation;
		}
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const
{
	FVector cameraWorldLocation;

	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector &outHitLocation, FVector lookDirection) const
{
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection * m_lineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_Visibility)) {
		outHitLocation = hitResult.Location;
		return true;
	}
	
	//Return false if not looking at visable target
	outHitLocation = FVector(0.0f);
	return false;
}