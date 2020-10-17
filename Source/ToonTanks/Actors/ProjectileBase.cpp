// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->InitialSpeed = MovementSpeed;
	// avoid having too many objects of this type on the screen
	InitialLifeSpan = 3.f;

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	// creates a listener to the On Hit event
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	UE_LOG(LogTemp, Error, TEXT("AProjectileBase::BeginPlay()"))
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// check if the owner still exists
	AActor* MyOwner = GetOwner();
	//UE_LOG(LogTemp, Warning, TEXT("Projectile On Hit Called"))
	if (MyOwner)
	{
		if (OtherActor && (OtherActor != this) && (OtherActor != MyOwner))
		{
			//UE_LOG(LogTemp, Error, TEXT("Projectile hits %s"), *OtherActor->GetName())
			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
		}

		Destroy();
	}


}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

