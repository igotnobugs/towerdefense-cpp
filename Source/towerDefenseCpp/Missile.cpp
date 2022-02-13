// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Enemy.h"
#include "DrawDebugHelpers.h"
#include "HealthComponent.h"
#include "TurretTower.h"

void AMissile::SetTarget(AEnemy* target)
{
	enemyTarget = target;
	projectileMovement->HomingTargetComponent = enemyTarget->targetArrow;
}

void AMissile::OnCollision(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UHealthComponent* health = OtherActor->FindComponentByClass<UHealthComponent>();

	if (health != nullptr) {
		Explode();
		OnHit(false);
	}
	else {
		OnHit(true);
		if (OtherActor->ActorHasTag("Ground")) {
			Explode();
			this->Destroy();
		}
		return;
	}
	this->Destroy();
}

void AMissile::MoveInToTarget()
{
	// Attempt to get another one
	//if (enemyTarget == nullptr) {
	//	if (towerOwner != nullptr) {
			//if (towerOwner->GetFirstTargetEnemy() != nullptr) {
	//			SetTarget(towerOwner->GetFirstTargetEnemy());
			//}
	//	}
	//}

	projectileMovement->InitialSpeed = speed;
	projectileMovement->MaxSpeed = speed;
	projectileMovement->bIsHomingProjectile = true;
}

void AMissile::Explode()
{
	if (displayExposionRadius) {
		DrawDebugSphere(GetWorld(),
			GetActorLocation(),
			explosionRadius,
			20,
			FColor::Red,
			false, 0.5f,
			SDPG_World,
			5.f);
	}

	TArray<FHitResult> OutHits;
	bool isHit = GetWorld()->SweepMultiByChannel(OutHits,
		GetActorLocation(), GetActorLocation(),
		FQuat::Identity, ECC_WorldDynamic,
		FCollisionShape::MakeSphere(explosionRadius));

	if (isHit) {
		for (auto& target : OutHits) {
			AActor* actor = target.GetActor();
			if (actor != nullptr) {
				UHealthComponent* otherHealth = actor->FindComponentByClass<UHealthComponent>();
				if (otherHealth != nullptr) {
					otherHealth->DamageHealth(damage);
				}
			}
		}
	}
}

void AMissile::BeginPlay()
{
	Super::BeginPlay();
	projectileMovement->bIsHomingProjectile = false;

	sphereBulletCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnCollision);

	projectileMovement->AddForce(GetActorForwardVector() * deploySpeed);
	projectileMovement->MaxSpeed = deploySpeed;

	OnFire();

	FTimerHandle MissileHandle;
	FTimerDelegate MissileDelegate = FTimerDelegate::CreateUObject(
		this, &AMissile::MoveInToTarget
	);
	GetWorldTimerManager().SetTimer(MissileHandle, MissileDelegate, activationTime, false);

#if WITH_EDITOR
	this->SetFolderPath("Projectiles");
#endif
}
