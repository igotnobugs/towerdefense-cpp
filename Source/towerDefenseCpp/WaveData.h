// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WaveData.generated.h"

UCLASS(BlueprintType)
class TOWERDEFENSECPP_API UWaveData : public UDataAsset
{
	GENERATED_BODY()

public:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//	bool spawnFromAllSpawners = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int waveClearReward = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float delayEachSpawn = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 spawnCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class AEnemy> enemyToSpawn;

};