// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "WaveData.h"
#include "Enemy.h"
#include "Waypoint.h"
#include "Kismet/GameplayStatics.h"
#include "TowerGameMode.h"
#include "TowerGameState.h"


// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ASpawner::SpawnWave(UWaveData* wave, const int overrideAmount)
{
	if (!isSpawning) return;

	// Enemy Setup
	AEnemy* spawnedEnemy;
	FVector spawnLocation = spawnPoint->GetActorLocation();
	spawnedEnemy = GetWorld()->SpawnActor<AEnemy>(wave->enemyToSpawn, GetActorLocation(), GetActorRotation());
	spawnedEnemy->Init(towerGameState->currentWave, towerGameMode->waveHpScaling);
	spawnedEnemy->OnDeath.AddDynamic(this, &ASpawner::OnEnemyDeath);
	spawnedEnemy->OnDeath.AddDynamic(towerGameMode, &ATowerGameMode::OnEnemyKill);
	spawnedEnemy->OnReachedCore.AddDynamic(towerGameMode, &ATowerGameMode::OnEnemyReachedCore);
	spawnedEnemy->StartMoving(spawnPoint);

	totalSpawned++;
	OnEnemySpawn.Broadcast();

	if (overrideAmount < 0) {
		enemiesToSpawn = wave->spawnCount;
	}
	else {
		enemiesToSpawn = overrideAmount;
	}

	if (totalSpawned < enemiesToSpawn) {
		FTimerHandle DestroyHandle;
		FTimerDelegate DestroyDelegate = FTimerDelegate::CreateUObject(
			this, &ASpawner::SpawnWave, wave, overrideAmount
		);
		GetWorldTimerManager().SetTimer(DestroyHandle, DestroyDelegate, wave->delayEachSpawn, false);
	}
	else {		
		OnSpawnFinish.Broadcast(this);
	}
}

void ASpawner::ResetSpawner()
{
	totalSpawned = 0;
	totalEnemiesDead = 0;
	isSpawning = true;
}

void ASpawner::StopSpawner()
{
	isSpawning = false;
}

void ASpawner::OnEnemyDeath(AEnemy* enemy, bool playerKilled)
{
	totalEnemiesDead++;
	if (totalEnemiesDead >= totalSpawned) {
		OnAllEnemiesDead.Broadcast(this);
	}
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	towerGameMode = Cast<ATowerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	towerGameState = Cast<ATowerGameState>(UGameplayStatics::GetGameState(GetWorld()));


	ResetSpawner();
}
