// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Waypoint.generated.h"

UCLASS()
class TOWERDEFENSECPP_API AWaypoint : public AActor
{
	GENERATED_BODY()

	// Variables
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isWaypointCore = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class AWaypoint* nextWaypoint;

	// Own
public:	
	// Sets default values for this actor's properties
	AWaypoint();

public:
	UFUNCTION(BlueprintPure)
		bool IsWaypointCore() { return isWaypointCore; };

	UFUNCTION(BlueprintPure)
		AWaypoint* GetNextWaypoint() { return nextWaypoint; };

};
