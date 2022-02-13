// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretTower.h"
#include "EMPTower.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSECPP_API AEMPTower : public ATurretTower
{
	GENERATED_BODY()


	// Own
protected:
	void OnRangeReached(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult) override;

	void OnRangeExit(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;

	// Overrides
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
