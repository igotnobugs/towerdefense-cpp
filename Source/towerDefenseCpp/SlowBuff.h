// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBuff.h"
#include "SlowBuff.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSECPP_API ASlowBuff : public AEnemyBuff
{
	GENERATED_BODY()

	// Variable
protected:
	UPROPERTY(EditAnywhere)
		float slowScale = 0.5f;

	// Overrides
public:
	virtual bool ApplyBuff(AEnemy* enemy) override;

	virtual void RemoveBuff() override;
};
