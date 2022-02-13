// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretTower.h"
#include "PowerGeneratorTower.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSECPP_API APowerGeneratorTower : public ATurretTower
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float scaleImprovement = 1.2f;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<class ATurretTower*> towersInRange;

protected:
	void OnRangeReached(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult) override;

	void OnRangeExit(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;

	virtual bool UpgradeTower() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
