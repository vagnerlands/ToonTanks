// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/ForceFeedbackEffect.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile Trail"));
	ProjectileTrail->SetupAttachment(RootComponent);

	ForceFeedbackOnHit = CreateDefaultSubobject<UForceFeedbackEffect>(TEXT("Force feedback on HIT"));

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

	if (ShootSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ShootSound, GetActorLocation());
	}

	PlayerPawnReference = Cast<AActor>(UGameplayStatics::GetPlayerPawn(this, 0));
	UE_LOG(LogTemp, Warning, TEXT(" retrieved player actor reference address 0x%x"), &*PlayerPawnReference)

	// creates a listener to the On Hit event
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
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
			UGameplayStatics::SpawnEmitterAtLocation(this, HitEffect, Hit.Location);
			if (HitSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, HitSound, Hit.Location);
			}

			if (PlayerPawnReference && ForceFeedbackOnHit && (PlayerPawnReference == OtherActor))
			{
				UGameplayStatics::SpawnForceFeedbackAtLocation(this, ForceFeedbackOnHit, Hit.Location);
			}

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

