// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerBuff.generated.h"

// WIP?

UCLASS()
class TOWERDEFENSECPP_API ATowerBuff : public AActor
{
	GENERATED_BODY()
	
	// Variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isStackable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float powerIncrease = 1.1f; // 10%

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	class ATurretTower* owner;

public:	
	// Sets default values for this actor's properties
	ATowerBuff();

	UFUNCTION()
		bool ApplyBuff(ATurretTower* towerToBuff);

	UFUNCTION()
		bool RemoveBuff(ATurretTower* towerToBuff);

protected:

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
