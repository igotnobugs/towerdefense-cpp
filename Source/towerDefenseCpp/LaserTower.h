// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretTower.h"
#include "LaserTower.generated.h"

/** A tower that hits target instantly
 * fireRate is ignored, damage is multiplied by deltaTime
 * Quick turn speed to avoid visual bugs
 */
UCLASS()
class TOWERDEFENSECPP_API ALaserTower : public ATurretTower
{
	GENERATED_BODY()

	// Variable
public:
	virtual float Shoot(AEnemy* enemyTarget = nullptr) override;

	virtual bool OverloadTower(const float scale) override;

	virtual void UnOverloadTower(const float scale) override;


	// Overrides
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
