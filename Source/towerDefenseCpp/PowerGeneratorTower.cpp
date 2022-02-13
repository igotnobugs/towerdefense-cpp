// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerGeneratorTower.h"
#include "Components/LineBatchComponent.h"
#include "Components/ArrowComponent.h"
#include "Math/Color.h"


void APowerGeneratorTower::OnRangeReached(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATurretTower* target = Cast<ATurretTower>(OtherActor);

	if (target != nullptr) {
		if (target->OverloadTower(towerStat.damage)) {
			if (!towersInRange.Contains(target)) {
				towersInRange.Add(target);
			}
			SetActorTickEnabled(true);
		}
	}
}

void APowerGeneratorTower::OnRangeExit(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	ATurretTower* target = Cast<ATurretTower>(OtherActor);
	if (target != nullptr) {
		if (towersInRange.Contains(target)) {
			towersInRange.Remove(target);
			target->UnOverloadTower(towerStat.damage);
			if (towersInRange.Num() <= 0) {
				SetActorTickEnabled(false);
			}
		}
	}
}

bool APowerGeneratorTower::UpgradeTower()
{
	const int pastScale = towerStat.damage;

	if (Super::UpgradeTower()) {
		for (ATurretTower* tower : towersInRange)
		{
			tower->UnOverloadTower(pastScale);
			tower->OverloadTower(towerStat.damage);
		}
		return true;
	}
	return false;
}

void APowerGeneratorTower::Tick(float DeltaTime)
{
	for (ATurretTower* tower : towersInRange)
	{
		GetWorld()->LineBatcher->DrawLine(
			barrelArrow->GetComponentLocation(),
			tower->GetActorLocation(),
			FLinearColor(FColor::Magenta),
			SDPG_World, 40.0f, 0.5f);
	}
}
