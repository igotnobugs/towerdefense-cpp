// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TowerAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSECPP_API ATowerAIController : public AAIController
{
	GENERATED_BODY()

	// Variable
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ATurretTower* turretTower;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float projectileSpeed = 2500.0f;

	// Own
public:
	ATowerAIController();

	UFUNCTION()
		void SetControlledTower(ATower* tower);

protected:
	UFUNCTION(BlueprintPure)
		FRotator GetOptimizeAngle(const AEnemy* target);

	// Override
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
