// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerAIController.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TurretTower.h"
#include "Enemy.h"

ATowerAIController::ATowerAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATowerAIController::SetControlledTower(ATower* tower)
{
	turretTower = Cast<ATurretTower>(tower);
}

FRotator ATowerAIController::GetOptimizeAngle(const AEnemy* target)
{
	const float distance = UKismetMathLibrary::Vector_Distance(
		turretTower->barrelArrow->GetComponentLocation(),
		target->targetArrow->GetComponentLocation()
	);

	const int adjustmentAim = 1.1f;

	const FVector lookAhead = target->GetVelocity() 
		* (distance / projectileSpeed) * adjustmentAim;

	return UKismetMathLibrary::FindLookAtRotation(
		turretTower->barrelArrow->GetComponentLocation(),
		target->targetArrow->GetComponentLocation() + lookAhead
	);
}

void ATowerAIController::BeginPlay()
{
	Super::BeginPlay();

	turretTower = Cast<ATurretTower>(GetPawn());

#if WITH_EDITOR
	this->SetFolderPath("Towers");
#endif

}

void ATowerAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (turretTower == nullptr) return;

	if (turretTower->GetNumberOfEnemiesInRange() > 0) {

		AEnemy& targetEnemy = *turretTower->GetFirstTargetEnemy();

		const FRotator towerRotation = GetOptimizeAngle(&targetEnemy);

		turretTower->RotateTurret(DeltaTime, towerRotation);

		projectileSpeed = turretTower->Shoot(&targetEnemy);
	}
}
