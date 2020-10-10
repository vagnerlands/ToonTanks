// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets de fault values
APawnBase::APawnBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	// in the 
	RootComponent = CapsuleComp;

	TankMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Base Mesh"));
	TankMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Turret Mesh"));
	TurretMesh->SetupAttachment(TankMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Tank Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void APawnBase::RotateTurret(FVector LookAtTarget)
{
	FVector LookAtTargetPlain = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();

	FRotator TurretRotation = FVector(LookAtTargetPlain - StartLocation).Rotation();

	// Update Turret Mesh rotation to face towards the LookAtTarget
	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire()
{
	// Get ProjectileSpawnPoint Location & Rotation -> spawn projectile and projects it forward
	UE_LOG(LogTemp, Display, TEXT("Fire Towards"))
}

void APawnBase::HandleDestruction()
{
	// play death effects, particles, sound and camera shade

	// call to child overrides
	// 1 - PawnTurret - Inform gamemode turret died
	// 2 - PawnTank - Inform gamemode player died (hide all components and disable player input)
}
