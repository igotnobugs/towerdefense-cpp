// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretTower.h"
#include "SalvagerTower.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSECPP_API ASalvagerTower : public ATurretTower
{
	GENERATED_BODY()


public:
	//UPROPERTY(EditAnywhere)
	//	int salvageReward= 2;

private:
	class ATowerGameMode* towerGameMode;
	class AActor* coreTurret;

	// Own
protected:
	virtual void OnTowerBeginPlay() override;

	void OnRangeReached(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult) override;

	void OnRangeExit(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;

	UFUNCTION()
		virtual void SalvageEnemy(AEnemy* enemy, bool playerKilled);

	UFUNCTION()
		void AddPassiveGold(const int amount);

	// Overrides
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
