// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Enemy.h"
#include "Waypoint.h"


void AEnemyAIController::SetControlledEnemy(AEnemy* enemy)
{
	enemyPawn = enemy;
}

void AEnemyAIController::MoveToNextWaypoint()
{
	if (currentWaypoint == nullptr) return;

	currentWaypoint = currentWaypoint->GetNextWaypoint();

	if (currentWaypoint == nullptr) {
		// current waypoint is probably the end
		enemyPawn->OnDeath.Broadcast(enemyPawn, false);
		enemyPawn->OnReachedCore.Broadcast(enemyPawn);
		enemyPawn->Destroy();
		return;
	}

	MoveToWaypoint(currentWaypoint);
}

void AEnemyAIController::MoveToWaypoint(AWaypoint* waypoint)
{	
	if (waypoint == nullptr) return;

	currentWaypoint = waypoint;
	FVector waypointLocation = currentWaypoint->GetActorLocation();
	waypointLocation.Z = enemyPawn->GetActorLocation().Z;

	MoveToLocation(waypointLocation, 5.f, false);
}

// Called when the game starts or when spawned
void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

#if WITH_EDITOR
	this->SetFolderPath("Enemies");
#endif

}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{

	if (enemyPawn == nullptr) return;

	MoveToNextWaypoint();
}
