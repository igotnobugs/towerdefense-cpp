// Fill out your copyright notice in the Description page of Project Settings.


#include "MissileTower.h"
#include "Missile.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TowerAIController.h"
#include "Enemy.h"


float AMissileTower::Shoot(AEnemy* enemyTarget)
{
	if (fireRateCountdown > 0) return 2000.0f;

	AMissile* newProjectile;

	newProjectile = GetWorld()->SpawnActor<AMissile>(
		projectile, barrelArrow->GetComponentLocation(), barrelArrow->GetComponentRotation()
		);
	fireCount++;

	newProjectile->Init(towerStat.damage, this);
	newProjectile->SetTarget(enemyTarget);

	fireRateCountdown = fireRateTrue;
	OnFire();

	return 2000.0f;
}