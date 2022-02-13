// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBuff.h"
#include "TurretTower.h"

// Sets default values
ATowerBuff::ATowerBuff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool ATowerBuff::ApplyBuff(ATurretTower* towerToBuff)
{
	//if (towerToBuff->isOverloaded) return false;

	//towerToBuff

	//towerToBuff->isOverloaded = true;
	return true;
}

// Called when the game starts or when spawned
void ATowerBuff::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ATowerBuff::RemoveBuff(ATurretTower* towerToBuff)
{
	return false;
}


// Called every frame
void ATowerBuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

