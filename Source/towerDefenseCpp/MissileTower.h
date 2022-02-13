// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretTower.h"
#include "MissileTower.generated.h"

/** Tower -> TurretTower -> MissileTower
 *  basically a gun turret created just so it can set the target for missiles
 *  
 */

UCLASS()
class TOWERDEFENSECPP_API AMissileTower : public ATurretTower
{
	GENERATED_BODY()

	// Own
public:
	virtual float Shoot(AEnemy* enemyTarget = nullptr) override;


};
