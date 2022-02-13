// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserTower.h"
#include "Components/LineBatchComponent.h"
#include "Components/ArrowComponent.h"
#include "Math/Color.h"
#include "Enemy.h"
#include "HealthComponent.h"
#include "EnemyBuff.h"
#include "BuffManager.h"

float ALaserTower::Shoot(AEnemy* enemyTarget)
{
	GetWorld()->LineBatcher->DrawLine(
		barrelArrow->GetComponentLocation(),
		enemyTarget->targetArrow->GetComponentLocation(),
		FLinearColor(FColor::Red),
		SDPG_World, 50.0f, 0.5f);

	enemyTarget->buffManager->AddBuff(buffToAdd, this, true);

	return 9999999.0f; //speed of light
}

bool ALaserTower::OverloadTower(const float scale)
{
	if (isOverloaded) return false;
	towerStat.damage *= scale;

	isOverloaded = true;
	return true;
}

void ALaserTower::UnOverloadTower(const float scale)
{
	isOverloaded = false;
	towerStat.damage /= scale;
}

void ALaserTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (enemiesInRange.Num() > 0) {
		enemiesInRange[0]->health->DamageHealth(towerStat.damage * DeltaTime);
	}
}
