// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBuff.h"
#include "BurnBuff.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSECPP_API ABurnBuff : public AEnemyBuff
{
	GENERATED_BODY()

	// Own
public:
	virtual bool ApplyBuff(AEnemy* enemy) override;

	virtual void RemoveBuff() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
