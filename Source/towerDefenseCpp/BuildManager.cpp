// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildManager.h"
#include "Kismet/GameplayStatics.h"
#include "TowerData.h"
#include "TowerGameMode.h"
#include "BuildTower.h"
#include "Tower.h"

// Sets default values
ABuildManager::ABuildManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

bool ABuildManager::BuildTowerAt(int index)
{
	// Tower will always exist
	//if (index < 0 && index > towerDatas.Num() - 1) {
		// That tower doesnt exist
	//	return false;
	//} 

	bool hasEnoughGold = towerGameMode->CheckGold(towerDatas[index]->towerLevels[0].cost);

	if (!hasEnoughGold) {
		// You dont have enough gold
		return false;
	}

	ABuildTower* spawnedBuildTower;
	FTransform buildTransform = FTransform(FVector(0,0,0));
	spawnedBuildTower = GetWorld()->SpawnActor<ABuildTower>(buildTower, buildTransform);
	spawnedBuildTower->Init(*towerDatas[index], continueBuilding);

	spawnedBuildTower->OnTowerBuild.AddDynamic(this, &ABuildManager::OnTowerBuilt);

	return true;
}

void ABuildManager::OnTowerBuilt_Implementation(ATower* tower)
{
	tower->OnTowerSold.AddDynamic(this, &ABuildManager::OnTowerSold);
	tower->OnTowerUpgrade.AddDynamic(this, &ABuildManager::OnTowerUpgrade);
}

void ABuildManager::OnTowerSold_Implementation(ATower* tower)
{
	tower->OnTowerSold.RemoveDynamic(this, &ABuildManager::OnTowerSold);
}

void ABuildManager::OnTowerUpgrade_Implementation(ATower* tower)
{

}

// Called when the game starts or when spawned
void ABuildManager::BeginPlay()
{
	Super::BeginPlay();

	towerGameMode = Cast<ATowerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	for (ATower* tower : alreadyBuiltTowers) {
		tower->OnTowerSold.AddDynamic(this, &ABuildManager::OnTowerSold);
		tower->OnTowerUpgrade.AddDynamic(this, &ABuildManager::OnTowerUpgrade);
	}
}
