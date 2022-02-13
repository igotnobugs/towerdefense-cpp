// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TowerGameState.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSECPP_API ATowerGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool isBuildMode = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int currentWave = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxWave = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float currentWaveProgress = 0;

};
