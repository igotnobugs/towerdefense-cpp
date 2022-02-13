// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Missile.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSECPP_API AMissile : public AProjectile
{
	GENERATED_BODY()

	// Variables
public:
	UPROPERTY(EditAnywhere)
		bool displayExposionRadius = false;

	UPROPERTY(EditAnywhere)
		float explosionRadius = 30.0f;

	UPROPERTY(EditAnywhere)
		float activationTime = 0.5f;

	UPROPERTY(EditAnywhere)
		float deploySpeed = 2000.0f;

	UPROPERTY(EditAnywhere)
		class AEnemy* enemyTarget;

	// Own
public:
	UFUNCTION()
		void SetTarget(AEnemy* target);

	virtual void OnCollision(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	UFUNCTION()
		void MoveInToTarget();

private:
	void Explode();

	// Overrides
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
