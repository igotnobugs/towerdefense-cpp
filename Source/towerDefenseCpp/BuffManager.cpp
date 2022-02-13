// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffManager.h"
#include "Components/ChildActorComponent.h"
#include "Components/ArrowComponent.h"
#include "TurretTower.h"
#include "EnemyBuff.h"
#include "Enemy.h"

// Sets default values for this component's properties
UBuffManager::UBuffManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


}


bool UBuffManager::AddBuff(const TSubclassOf<class AEnemyBuff> theBuff, ATurretTower* fromTurretTower, 
	const bool refreshBuff)
{
	if (theBuff == nullptr) return false;
	if (buffs.Num() >= maximumBuffs) return false;
	
	const AEnemyBuff* incomingEnemyBuff = theBuff->GetDefaultObject<AEnemyBuff>();

	if (!incomingEnemyBuff->stackable) {
		if (managerOwner->ActorHasTag(incomingEnemyBuff->name)) {
			if (refreshBuff) {
				FName nameToFind = incomingEnemyBuff->name;
				AEnemyBuff* buffToRefresh = *buffs.FindByPredicate([&](AEnemyBuff* eBuff) {
					return eBuff->name == nameToFind;
				});
				if (buffToRefresh == nullptr) return false;
				if (fromTurretTower == nullptr) return false;
				buffToRefresh->Init(fromTurretTower->towerStat.fireRate, incomingEnemyBuff->duration);
				return false;
			}
			return false;
		}		
	}

	AEnemyBuff* newBuff = GetWorld()->SpawnActor<AEnemyBuff>(
		theBuff, managerOwner->targetArrow->GetComponentTransform());

	newBuff->Init(fromTurretTower->towerStat.fireRate, incomingEnemyBuff->duration);
	newBuff->AttachToActor(managerOwner, FAttachmentTransformRules::KeepWorldTransform);

	buffs.Add(newBuff);
	return newBuff->ApplyBuff(managerOwner);
}

bool UBuffManager::RemoveBuff(const TSubclassOf<class AEnemyBuff> theBuff)
{
	if (theBuff == nullptr) return false;
	if (buffs.Num() <= 0) return false;

	const AEnemyBuff* buffToDetect = theBuff->GetDefaultObject<AEnemyBuff>();

	if (!managerOwner->ActorHasTag(buffToDetect->name)) {
		return false;
	}

	FName nameToFind = buffToDetect->name;
	
	AEnemyBuff* buffToRemove = *buffs.FindByPredicate([&](AEnemyBuff* eBuff) {
		return eBuff->name == nameToFind;
	});

	if (buffToRemove == nullptr) return false;

	buffs.Remove(buffToRemove);
	buffToRemove->Destroy();

	return true;
}

// Called when the game starts
void UBuffManager::BeginPlay()
{
	Super::BeginPlay();

	managerOwner = Cast<AEnemy>(GetOwner());
}

void UBuffManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	buffs.Shrink();
	for (auto buff : buffs) {
		if (buff != nullptr)
			buff->Destroy();
	}

	Super::EndPlay(EndPlayReason);
}