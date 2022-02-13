// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildManager.generated.h"

UCLASS()
class TOWERDEFENSECPP_API ABuildManager : public AActor
{
	GENERATED_BODY()
	
	// Variables
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool continueBuilding = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class ABuildTower> buildTower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class UTowerData*> towerDatas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AGameManager* gameManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class ATower*> alreadyBuiltTowers;

private:
	class ATowerGameMode* towerGameMode;

	// Own
public:	
	// Sets default values for this actor's properties
	ABuildManager();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void ToggleBuildMenu(bool state);

	UFUNCTION(BlueprintCallable)
		bool BuildTowerAt(int index);

	UFUNCTION(BlueprintNativeEvent)
		void OnTowerBuilt(ATower* tower);

	UFUNCTION(BlueprintNativeEvent)
		void OnTowerSold(ATower* tower);

	UFUNCTION(BlueprintNativeEvent)
		void OnTowerUpgrade(ATower* tower);

	// Overrides
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
