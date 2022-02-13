// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBuff.h"


// Sets default values
AEnemyBuff::AEnemyBuff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//

}

void AEnemyBuff::Init(const float setDamage, const float setDuration)
{
	damage = setDamage;
	duration = setDuration;
}


// Called when the game starts or when spawned
void AEnemyBuff::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(duration);

}

void AEnemyBuff::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	RemoveBuff();

	Super::EndPlay(EndPlayReason);
}

