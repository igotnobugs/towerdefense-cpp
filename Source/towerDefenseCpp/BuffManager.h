// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSECPP_API UBuffManager : public UActorComponent
{
	GENERATED_BODY()

	// Variables
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maximumBuffs = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<class AEnemyBuff*> buffs;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class AEnemy* managerOwner;

	// Own
public:	
	// Sets default values for this component's properties
	UBuffManager();

	UFUNCTION()
		bool AddBuff(const TSubclassOf<class AEnemyBuff> theBuff, ATurretTower* fromTurretTower,
			const bool refreshBuff = false);

	UFUNCTION()
		bool RemoveBuff(const TSubclassOf<class AEnemyBuff> theBuff);

	// Overrides
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};
