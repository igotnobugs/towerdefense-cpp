// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStart, class AGameManager*, gameManager);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamePrepare, class AGameManager*, gameManager);

UCLASS()
class TOWERDEFENSECPP_API AGameManager : public AActor
{
	GENERATED_BODY()

	// Variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ACameraActor* titleCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ACameraActor* overviewCamera;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float delayToStart = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ASpawnerManager* spawnerManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ABuildManager* buildManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ATowerGameMode* towerGameMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ATowerGameState* towerGameState;

	// Events
public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
		FOnGamePrepare OnGamePrepare;

	UPROPERTY(BlueprintCallable)
		FOnGameStart OnGameStart;

	// Own
public:	
	// Sets default values for this actor's properties
	AGameManager();

protected:
	UFUNCTION(BlueprintCallable)
		void StartPreparing();

	UFUNCTION(BlueprintNativeEvent)
		void OnPrepareGameStart();

	UFUNCTION()
		void GameStart();

	UFUNCTION(BlueprintNativeEvent)
		void OnGameWon(ASpawnerManager* spawnManager);

	UFUNCTION(BlueprintNativeEvent)
		void OnGameOver(ATowerGameMode* gameMode);




	// Overrides
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
