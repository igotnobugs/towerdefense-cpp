// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAllWavesFinished, class ASpawnerManager*, spawnerManager);

UCLASS()
class TOWERDEFENSECPP_API ASpawnerManager : public AActor
{
	GENERATED_BODY()

	// Variables
public:
	UPROPERTY(VisibleAnywhere)
		int numberOfWaves = 0;

	UPROPERTY(EditAnywhere)
		int currentWaveIndex = 0; // with 0 as 1

protected:
	UPROPERTY(EditAnywhere)
		TArray<class ASpawner*> spawners;

	UPROPERTY(EditAnywhere)
		TArray<class UWaveData*> waves;

	UPROPERTY(VisibleAnywhere)
		int totalAmountToSpawn = 0;

	UPROPERTY(VisibleAnywhere)
		int totalSpawnedFromAllSpawners = 0;

private:
	class ATowerGameMode* towerGameMode;
	class UWaveData* currentWaveData;
	int amountOfSpawnersDone = 0;
	bool isSpawning = false;

	// Events
public:
	FAllWavesFinished AllWavesFinished;

	// Own
public:	
	// Sets default values for this actor's properties
	ASpawnerManager();

	UFUNCTION(BlueprintCallable)
		void StartSpawning();

	UFUNCTION(BlueprintCallable)
		void StopSpawning();

	UFUNCTION(BlueprintPure)
		int GetTotalEnemiesInWave();

	UFUNCTION(BlueprintPure)
		int GetTotalEnemySpawned();

protected:
	UFUNCTION()
		void PrepareNextWave(ASpawner* spawner);
	
	UFUNCTION()
		void SpawnNextWave(UWaveData* waveData);

	UFUNCTION()
		void UpdateValues();

	// Overrides
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
