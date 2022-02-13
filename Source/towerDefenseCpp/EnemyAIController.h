// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSECPP_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	// Variables
public:
	class AWaypoint* currentWaypoint;

private:
	class AEnemy* enemyPawn;

	// Own
public:
	UFUNCTION()
		void SetControlledEnemy(AEnemy* enemy);

	UFUNCTION()
		void MoveToNextWaypoint();

	UFUNCTION()
		void MoveToWaypoint(AWaypoint* waypoint);

	// Overrides
protected:
	virtual void BeginPlay() override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
