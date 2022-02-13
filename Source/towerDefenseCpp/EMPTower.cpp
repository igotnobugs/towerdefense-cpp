// Fill out your copyright notice in the Description page of Project Settings.


#include "EMPTower.h"
#include "Components/LineBatchComponent.h"
#include "Components/ArrowComponent.h"
#include "Math/Color.h"
#include "Enemy.h"
#include "BuffManager.h"

// fireRate = maximumTargets

void AEMPTower::OnRangeReached(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* target = Cast<AEnemy>(OtherActor);

	if (target != nullptr) {
		if (enemiesInRange.Num() >= towerStat.fireRate) return;

		if (target->buffManager->AddBuff(buffToAdd, this, false)) {
			if (!enemiesInRange.Contains(target)) {
				enemiesInRange.Add(target);
			}
			SetActorTickEnabled(true);
		}
	}
}

void AEMPTower::OnRangeExit(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	AEnemy* target = Cast<AEnemy>(OtherActor);
	if (target != nullptr) {
		enemiesInRange.RemoveSingle(target);
		target->buffManager->RemoveBuff(buffToAdd);

		if (enemiesInRange.Num() <= 0) {
			SetActorTickEnabled(false);
		}
	}
}

void AEMPTower::Tick(float DeltaTime)
{
	for (AEnemy* enemy : enemiesInRange)
	{
		GetWorld()->LineBatcher->DrawLine(
			barrelArrow->GetComponentLocation(),
			enemy->targetArrow->GetComponentLocation(),
			FLinearColor(FColor::Purple),
			SDPG_World, 30.0f, 0.5f);
	}
}
