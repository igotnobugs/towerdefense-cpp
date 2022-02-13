// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"
#include "HealthComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	bulletMesh->SetupAttachment(RootComponent);
	bulletMesh->bEditableWhenInherited = true;

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	projectileMovement->bEditableWhenInherited = true;

	sphereBulletCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Bullet Collision"));
	sphereBulletCollision->SetupAttachment(bulletMesh);
	sphereBulletCollision->bEditableWhenInherited = true;	
}

void AProjectile::Init(const float bulletDamage, ATurretTower* shooter)
{
	damage = bulletDamage;
	towerOwner = shooter;
}

void AProjectile::OnCollision(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UHealthComponent* health = OtherActor->FindComponentByClass<UHealthComponent>();

	if (health != nullptr) {	
		health->DamageHealth(damage);
		OnHit(false);
	}
	else {
		OnHit(true);
		if (OtherActor->ActorHasTag("Ground")) {
			this->Destroy();
		}
		return;
	}
	this->Destroy();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	sphereBulletCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnCollision);

	projectileMovement->InitialSpeed = speed;
	projectileMovement->MaxSpeed = speed;

	OnFire();

#if WITH_EDITOR
	this->SetFolderPath("Projectiles");
#endif

}