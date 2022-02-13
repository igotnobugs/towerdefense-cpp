// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretTower.h"
#include "Components/ArrowComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TowerAIController.h"
#include "Projectile.h"
#include "Enemy.h"
#include "TowerGameState.h"
#include "TowerGameMode.h"
#include "TowerTurretWidget.h"
#include "TowerData.h"


ATurretTower::ATurretTower()
{
	PrimaryActorTick.bCanEverTick = true;

	//towerStat.towerType = ETowerType::TE_TargetsLand;
}

void ATurretTower::RotateTurret(float DeltaTime, const FRotator rotation)
{
	FRotator lerpRotation = UKismetMathLibrary::RLerp(
		turretArrow->GetComponentRotation(),
		rotation,
		DeltaTime * towerStat.turnRate,
		true
	);

	turretArrow->SetWorldRotation(lerpRotation);
}

bool ATurretTower::OverloadTower(const float scale)
{
	if (isOverloaded) return false;
	overloadScale = scale;
	isOverloaded = true;
	towerStat.fireRate *= scale;
	fireRateTrue = 1.0f / towerStat.fireRate;
	return true;
}

void ATurretTower::UnOverloadTower(const float scale)
{
	if (!isOverloaded) return;
	isOverloaded = false;
	towerStat.fireRate /= scale;
	fireRateTrue = 1.0f / towerStat.fireRate;
}

bool ATurretTower::UpgradeTower()
{
	if (!towerData->towerLevels.IsValidIndex(towerStat.level)) return false;

	if (!towerGameMode->UseGold(towerStat.upgradeCost)) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Not enough money for upgrade."));
		return false;
	}

	bool upgradable = false;

	if (isOverloaded) {
		UnOverloadTower(overloadScale);
		upgradable = SetStats(towerData, towerStat.level + 1);
		OverloadTower(overloadScale);
	} else {
		upgradable = SetStats(towerData, towerStat.level + 1);
	}

	if (upgradable) {
		projectile = towerData->towerLevels[towerStat.level - 1].projectile;
		buffToAdd = towerData->towerLevels[towerStat.level - 1].buffToAdd;
	}

	OnTowerUpgrade.Broadcast(this);
	return true;
}

void ATurretTower::SellTower()
{
	towerGameMode->AddGold(towerStat.sellAmount);


	OnTowerSold.Broadcast(this);

	this->Destroy();
}

void ATurretTower::OnTowerBeginPlay()
{
	UTowerTurretWidget* myWidget = Cast<UTowerTurretWidget>(towerWidget->GetUserWidgetObject());


	if (myWidget) {
		myWidget->SetTrackedTurret(this);		
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("no widget"));
	}

	projectile = towerData->towerLevels[towerStat.level].projectile;
	buffToAdd = towerData->towerLevels[towerStat.level].buffToAdd;
}

void ATurretTower::OnLeftMouseClick()
{
	if (towerGameState->isBuildMode) return;
	if (!isHovered) {
		towerWidget->SetVisibility(false);
		sphereMeshRange->SetVisibility(false);
	}
}

void ATurretTower::OnRightMouseClick()
{
	if (towerGameState->isBuildMode) return;
	if (!isHovered) {
		towerWidget->SetVisibility(false);
		sphereMeshRange->SetVisibility(false);
	}
}

void ATurretTower::OnBeginMouseOver(UPrimitiveComponent* OverlappedComp)
{
	isHovered = true;
}

void ATurretTower::OnEndMouseOver(UPrimitiveComponent* OverlappedComp)
{
	isHovered = false;
}

void ATurretTower::OnBeginMouseClick(UPrimitiveComponent* OverlappedComp, FKey ButtonPressed)
{
	if (towerGameState->isBuildMode) return;

	if (ButtonPressed == EKeys::LeftMouseButton) {
		towerWidget->SetVisibility(true);
	}

	if (ButtonPressed == EKeys::RightMouseButton) {
		sphereMeshRange->SetVisibility(true);
	}
}

void ATurretTower::OnRangeReached(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* target = Cast<AEnemy>(OtherActor);
	
	if ((uint8)towerStat.towerType < 2) {
		if ((uint8)target->enemyStat.enemyType != (uint8)towerStat.towerType) return;
	}

	if (target != nullptr) {
		if (!enemiesInRange.Contains(target)) {
			enemiesInRange.Add(target);
		}
		SetActorTickEnabled(true);
	}
}

void ATurretTower::OnRangeExit(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	AEnemy* target = Cast<AEnemy>(OtherActor);
	if (target != nullptr) {
		enemiesInRange.Remove(target);
		if (enemiesInRange.Num() <= 0) {
			SetActorTickEnabled(false);
		}
	}
}

void ATurretTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (fireRateCountdown > 0) {
		fireRateCountdown -= DeltaTime;
	}
}
