// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;

private:
	UPROPERTY(EditAnywhere)
	float m_crosshairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float m_crosshairYLocation = 0.33f;

	bool GetSightRayHitLocation(FVector& hitLocation) const;

	bool GetLookDirection(FVector2D screenLocation, FVector& worldDirection) const;

	//Moves the Barrel to align with the crosshair
	void AimTowardsCrosshair();
};
