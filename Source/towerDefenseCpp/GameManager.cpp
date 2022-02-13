// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "SpawnerManager.h"
#include "TowerGameState.h"
#include "TowerGameMode.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AGameManager::StartPreparing()
{
	OnGamePrepare.Broadcast(this);
	OnPrepareGameStart();
}

void AGameManager::OnPrepareGameStart_Implementation()
{
	OnGameStart.Broadcast(this);

	FTimerHandle GameHandle;
	FTimerDelegate GameDelegate = FTimerDelegate::CreateUObject(
		this, &AGameManager::GameStart
	);
	GetWorldTimerManager().SetTimer(GameHandle, GameDelegate, delayToStart, false);
}

void AGameManager::GameStart()
{
	if (spawnerManager == nullptr) {
		return;
	}
	spawnerManager->StartSpawning();
	spawnerManager->AllWavesFinished.AddDynamic(this, &AGameManager::OnGameWon);
}

void AGameManager::OnGameOver_Implementation(ATowerGameMode* gameMode)
{
	spawnerManager->StopSpawning();
}

void AGameManager::OnGameWon_Implementation(ASpawnerManager* spawnManager)
{
	spawnerManager->StopSpawning(); 
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	towerGameMode = Cast<ATowerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	towerGameMode->OnCoreDestroyed.AddDynamic(this, &AGameManager::OnGameOver);

	towerGameState = Cast<ATowerGameState>(GetWorld()->GetGameState());
	towerGameState->currentWave = 1;

}