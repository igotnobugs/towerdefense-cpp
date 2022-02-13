// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoreDestroyed, class ATowerGameMode*, gameMode);

UCLASS()
class TOWERDEFENSECPP_API ATowerGameMode : public AGameModeBase
{
	GENERATED_BODY()

	// Variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int gold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float waveHpScaling = 0.1f; // Percentage of HP to add per Wave

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float timeBetweenWaves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ASpawnerManager* spawnerManager;

private:
	bool coreDamagedCurrentWave = false;
	bool isGameOngoing = true;

	// Events
public:
	FOnCoreDestroyed OnCoreDestroyed;

	// Own
public:
	UFUNCTION(BlueprintCallable)
		void DamageHealth(const int amount);

	UFUNCTION()
		void OnEnemyReachedCore(AEnemy* enemy);

	UFUNCTION(BlueprintNativeEvent)
		void OnCoreDamaged(const int amount);

	UFUNCTION()
		void OnEnemyKill(AEnemy* enemy, bool playerKilled);

	UFUNCTION(BlueprintCallable)
		bool AddGold(const int amount);

	UFUNCTION(BlueprintCallable)
		bool CheckGold(const int amount);

	UFUNCTION(BlueprintCallable)
		bool UseGold(const int amount);

	UFUNCTION()
		void EvaluateWave(UWaveData* waveData);
};
