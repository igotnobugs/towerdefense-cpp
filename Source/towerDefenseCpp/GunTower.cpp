// Fill out your copyright notice in the Description page of Project Settings.


#include "GunTower.h"
#include "Components/ArrowComponent.h"
#include "Projectile.h"

float AGunTower::Shoot(AEnemy* enemyTarget)
{
	if (fireRateCountdown > 0) return projectileSpeed;

	AProjectile* newProjectile;

	if (barrelCount > 0) {
		float barrelUse = 1;
		if (fireCount % 2 == 0) {
			barrelUse = 1;
		}
		else {
			barrelUse = -1;
		}
		FVector fireLocation = barrelArrow->GetComponentLocation() +
			barrelArrow->GetRightVector() * (barrelWidth * barrelUse);

		newProjectile = GetWorld()->SpawnActor<AProjectile>(
			projectile, fireLocation, barrelArrow->GetComponentRotation()
			);
	}
	else {
		newProjectile = GetWorld()->SpawnActor<AProjectile>(
			projectile, barrelArrow->GetComponentLocation(), barrelArrow->GetComponentRotation()
			);
	}
	fireCount++;

	newProjectile->Init(towerStat.damage);
	projectileSpeed = newProjectile->speed;
	fireRateCountdown = fireRateTrue;
	OnFire();

	return projectileSpeed;
}

bool AGunTower::UpgradeTower()
{
	//Hard code
	if (Super::UpgradeTower()) {
		if (towerStat.level >= 3) {
			barrelCount = 2;
		}
		return true;
	}

	return false;
}
