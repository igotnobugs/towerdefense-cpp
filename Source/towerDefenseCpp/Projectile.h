// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOWERDEFENSECPP_API AProjectile : public AActor
{
	GENERATED_BODY()

	// Variables
public:
	UPROPERTY(VisibleAnywhere)
		class  UProjectileMovementComponent* projectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float speed = 5000.0f;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* bulletMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USphereComponent* sphereBulletCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float damage = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class ATurretTower* towerOwner;

	// Own
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UFUNCTION()
		void Init(const float bulletDamage, ATurretTower* shooter = nullptr);

	UFUNCTION()
		virtual void OnCollision(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void OnFire();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void OnHit(const bool inGround);

	// Overrides
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
