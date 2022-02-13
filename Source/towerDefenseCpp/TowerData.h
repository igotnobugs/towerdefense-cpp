// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Tower.h"
#include "TowerData.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct FTowerLevel
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UStaticMesh* towerBaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UStaticMesh* towerTurretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<ETowerType> towerType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AProjectile> projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AEnemyBuff> buffToAdd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0))
		float damage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0))
		float range = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0))
		float fireRate = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0))
		float turnRate = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0))
		int cost = 1;
};


UCLASS()
class TOWERDEFENSECPP_API UTowerData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower Base")
		TSubclassOf<class ATower> tower;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower Base")
		FText name; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Display Stat Settings")
		FText damageLabel = FText::FromString(FString(TEXT("Damage:")));

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Display Stat Settings")
		FText rangeLabel = FText::FromString(FString(TEXT("Range:")));

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Display Stat Settings")
		FText fireRateLabel = FText::FromString(FString(TEXT("Fire Rate:")));

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower Levels")
		TArray<struct FTowerLevel> towerLevels;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Build Settings", meta = (ClampMin = 0))
		int nodes = 4;

};
