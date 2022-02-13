// Fill out your copyright notice in the Description page of Project Settings.


#include "BurnBuff.h"
#include "Enemy.h"
#include "HealthComponent.h"


bool ABurnBuff::ApplyBuff(AEnemy* enemy)
{
	if (enemy == nullptr) return false;

	buffOwner = enemy;
	buffOwner->Tags.Add(name);

	SetActorTickEnabled(true);

	return true;
}

void ABurnBuff::RemoveBuff()
{
	if (buffOwner == nullptr) return;
	buffOwner->Tags.RemoveSingle(name);
}

void ABurnBuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (buffOwner != nullptr) {
		buffOwner->health->DamageHealth(damage * DeltaTime);
	}
}
