// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerTurretWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSECPP_API UTowerTurretWidget : public UUserWidget
{
	GENERATED_BODY()

	// Variables
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ATurretTower* trackedTurretTower;
	
	// Own
public:
	UFUNCTION(BlueprintCallable)
		void SetTrackedTurret(ATurretTower* setTrackedTower);

};
