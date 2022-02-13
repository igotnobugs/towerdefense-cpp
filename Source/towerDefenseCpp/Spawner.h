// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnemySpawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpawnFinish, class ASpawner*, spawner);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAllDead, class ASpawner*, spawner);

UCLASS()
class TOWERDEFENSECPP_API ASpawner : public AActor
{
	GENERATED_BODY()
	
	// Variables
public:
	UPROPERTY(EditAnywhere)
		class AWaypoint* spawnPoint;

	UPROPERTY(VisibleAnywhere)
		int totalSpawned = 0;

	UPROPERTY(VisibleAnywhere)
		int totalEnemiesDead = 0;

protected:
	UPROPERTY(VisibleAnywhere)
		bool isSpawning = true;

private:
	class ATowerGameMode* towerGameMode;
	class ATowerGameState* towerGameState;
	int enemiesToSpawn = 0;

	// Own
public:	
	// Sets default values for this actor's properties
	ASpawner();

	UPROPERTY(BlueprintAssignable)
		FEnemySpawn OnEnemySpawn;

	UPROPERTY(BlueprintAssignable)
		FSpawnFinish OnSpawnFinish;

	UPROPERTY(BlueprintAssignable)
		FAllDead OnAllEnemiesDead;

	UFUNCTION(BlueprintCallable)
		void SpawnWave(UWaveData* wave, const int overrideAmount = -1);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		int GetTotalSpawned() { return totalSpawned; };

	UFUNCTION(BlueprintCallable)
		void ResetSpawner();

	UFUNCTION(BlueprintCallable)
		void StopSpawner();

private:
	UFUNCTION()
		void OnEnemyDeath(AEnemy* enemy, bool playerKilled);

	// Overrides
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
