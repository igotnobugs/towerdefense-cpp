// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerManager.h"
#include "Spawner.h"
#include "TowerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TowerGameState.h"
#include "WaveData.h"

// Sets default values
ASpawnerManager::ASpawnerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// First call
void ASpawnerManager::StartSpawning()
{
	if (waves.Num() <= 0) return;

	isSpawning = true;
	numberOfWaves = waves.Num();

	ATowerGameState* gameState = Cast<ATowerGameState>(UGameplayStatics::GetGameState(GetWorld()));
	gameState->maxWave = numberOfWaves;

	totalAmountToSpawn = waves[currentWaveIndex]->spawnCount;
	int amountPerSpawner = totalAmountToSpawn / spawners.Num();

	for (ASpawner* spawner : spawners) {
		spawner->OnAllEnemiesDead.AddDynamic(this, &ASpawnerManager::PrepareNextWave);
		spawner->OnEnemySpawn.AddDynamic(this, &ASpawnerManager::UpdateValues);
		spawner->SpawnWave(waves[currentWaveIndex], amountPerSpawner);
	}
}

void ASpawnerManager::StopSpawning()
{
	for (ASpawner* spawner : spawners) {
		spawner->StopSpawner();
	}

	isSpawning = false;
}

int ASpawnerManager::GetTotalEnemiesInWave()
{
	return totalAmountToSpawn;
}

int ASpawnerManager::GetTotalEnemySpawned()
{
	return totalSpawnedFromAllSpawners;
}

void ASpawnerManager::PrepareNextWave(ASpawner* spawner)
{
	amountOfSpawnersDone++;
	if (amountOfSpawnersDone < spawners.Num()) {
		return; // Wait for the other spawner to finish
	}

	towerGameMode->EvaluateWave(waves[currentWaveIndex]);

	amountOfSpawnersDone = 0;
	ATowerGameState* gameState = Cast<ATowerGameState>(UGameplayStatics::GetGameState(GetWorld()));

	//Check first
	if (gameState->currentWave >= numberOfWaves) {
		AllWavesFinished.Broadcast(this);
		return;
	}

	gameState->currentWave++;
	currentWaveIndex = (gameState->currentWave) - 1;

	if (!isSpawning) return;
	totalAmountToSpawn = waves[currentWaveIndex]->spawnCount;

	float delayNextWave = towerGameMode->timeBetweenWaves;
	FTimerHandle SpawnerHandle;
	FTimerDelegate SpawnerDelegate = FTimerDelegate::CreateUObject(
		this, &ASpawnerManager::SpawnNextWave, waves[currentWaveIndex]
	);
	GetWorldTimerManager().SetTimer(SpawnerHandle, SpawnerDelegate, delayNextWave, false);
}

void ASpawnerManager::SpawnNextWave(UWaveData* waveData)
{
	if (!isSpawning) return;

	currentWaveData = waveData;
	//ATowerGameState* gameState = Cast<ATowerGameState>(UGameplayStatics::GetGameState(GetWorld()));
	//gameState->currentWave++;

	int amountPerSpawner = currentWaveData->spawnCount / spawners.Num();

	for (ASpawner* spawner : spawners) {
		spawner->ResetSpawner();
		spawner->SpawnWave(waveData, amountPerSpawner);
	}

}

void ASpawnerManager::UpdateValues()
{
	int newTotal = 0;

	for (ASpawner* sp : spawners) {
		newTotal += sp->totalSpawned;
	}
	totalSpawnedFromAllSpawners = newTotal;
}

// Called when the game starts or when spawned
void ASpawnerManager::BeginPlay()
{
	Super::BeginPlay();
	
	towerGameMode = Cast<ATowerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));	
	towerGameMode->spawnerManager = this;
}