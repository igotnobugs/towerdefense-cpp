// Fill out your copyright notice in the Description page of Project Settings.


#include "SalvagerTower.h"
#include "Kismet/GameplayStatics.h"
#include "Components/LineBatchComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ArrowComponent.h"
#include "Math/Color.h"
#include "TowerGameMode.h"
#include "Enemy.h"
#include "TowerTurretWidget.h"
#include "TurretTower.h"

void ASalvagerTower::OnTowerBeginPlay()
{
	UTowerTurretWidget* myWidget = Cast<UTowerTurretWidget>(towerWidget->GetUserWidgetObject());

	if (myWidget) {
		myWidget->SetTrackedTurret(this);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("no widget"));
	}

	towerGameMode = Cast<ATowerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	TArray<AActor*> outActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("CoreTurret"), outActors);

	if (outActors.Num() > 0) {
		coreTurret = outActors[0];
	}

	FTimerHandle PassiveSalvageHandle;
	FTimerDelegate PassiveSalvageDelegate = FTimerDelegate::CreateUObject(
		this, &ASalvagerTower::AddPassiveGold, (int)towerStat.damage
	);
	GetWorldTimerManager().SetTimer(PassiveSalvageHandle, PassiveSalvageDelegate, fireRateTrue, true);
}

void ASalvagerTower::OnRangeReached(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* target = Cast<AEnemy>(OtherActor);

	if (target != nullptr) {
		if (target->isSalvageTracked) return;

		target->isSalvageTracked = true;
		if (!enemiesInRange.Contains(target)) {
			enemiesInRange.Add(target);
			target->OnDeath.AddDynamic(this, &ASalvagerTower::SalvageEnemy);				
		}
		SetActorTickEnabled(true);
	}
}

void ASalvagerTower::OnRangeExit(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	AEnemy* target = Cast<AEnemy>(OtherActor);
	if (target != nullptr) {
		enemiesInRange.Remove(target);
		target->OnDeath.RemoveDynamic(this, &ASalvagerTower::SalvageEnemy);
		target->isSalvageTracked = false;
		if (enemiesInRange.Num() <= 0) {
			SetActorTickEnabled(false);
		}
	}
}

void ASalvagerTower::SalvageEnemy(AEnemy* enemy, bool playerKilled)
{
	if (!playerKilled) return;

	GetWorld()->LineBatcher->DrawLine(
		barrelArrow->GetComponentLocation(),
		coreTurret->GetActorLocation(),
		FLinearColor(FColor::Green),
		SDPG_World, 50.0f, 1.0f);

	towerGameMode->AddGold(towerStat.damage);
}

void ASalvagerTower::AddPassiveGold(const int amount)
{
	towerGameMode->AddGold(amount);

	GetWorld()->LineBatcher->DrawLine(
		barrelArrow->GetComponentLocation(),
		coreTurret->GetActorLocation(),
		FLinearColor(FColor::Yellow),
		SDPG_World, 50.0f, 1.5f);
}

void ASalvagerTower::Tick(float DeltaTime)
{
	for (AEnemy* enemy : enemiesInRange)
	{
		GetWorld()->LineBatcher->DrawLine(
			barrelArrow->GetComponentLocation(),
			enemy->targetArrow->GetComponentLocation(),
			FLinearColor(FColor::Green),
			SDPG_World, 15.0f, 0.5f);
	}
}
