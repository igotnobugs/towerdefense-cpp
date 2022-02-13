// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enemy.h"
#include "EnemyData.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSECPP_API UEnemyData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TEnumAsByte<EEnemyType> enemyType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float health = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float coreDamage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float goldReward = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float speed = 100;
};
