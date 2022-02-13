// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretTower.h"
#include "GunTower.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSECPP_API AGunTower : public ATurretTower
{
	GENERATED_BODY()
	
	//Variables
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int barrelCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int barrelWidth = 30;

private:
	float projectileSpeed = 2000.0f;

	//Own
public:
	virtual float Shoot(AEnemy* enemyTarget = nullptr) override;

	virtual bool UpgradeTower() override;
};
