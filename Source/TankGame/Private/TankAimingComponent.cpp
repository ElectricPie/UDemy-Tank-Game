// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * barrelToSet)
{
	m_barrel = barrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	//Returns if no barrel is found
	if (!m_barrel)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing barrel"))
		return;
	}


	FVector outLaunchVelocity;
	//Attempts to get the socket location with provided name, otherwises gets barrel location
	FVector startLocation = m_barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(
			this,
			outLaunchVelocity,
			startLocation,
			hitLocation,
			launchSpeed,
			false,
			0.0f,
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace)) 
	{
		auto ourTankName = GetOwner()->GetName();
		auto aimDirection = outLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("%s firing at %s"), *ourTankName, *aimDirection.ToString())
	}
	
}

