// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCore.h"

// wip

// Sets default values
APlayerCore::APlayerCore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APlayerCore::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

