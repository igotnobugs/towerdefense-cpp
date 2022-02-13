// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDeath, class AEnemy*, enemy, bool, playerKilled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReachedCore, class AEnemy*, enemy);

UENUM(BlueprintType)
enum class EEnemyType : uint8 {
	EE_Land		UMETA(DisplayName = "Land"), //0
	EE_Air		UMETA(DisplayName = "Air") //1
};

USTRUCT(BlueprintType)
struct FEnemyStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEnemyType enemyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float coreDamage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float goldReward = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float speed = 1000;
};

UCLASS()
class TOWERDEFENSECPP_API AEnemy : public ACharacter
{
	GENERATED_BODY()

	// Variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UEnemyData* enemyData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FEnemyStat enemyStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UHealthComponent* health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBuffManager* buffManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AWaypoint* currentWaypoint; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UArrowComponent* targetArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool isSalvageTracked = false;

protected:
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* enemyMesh;

	UPROPERTY(EditAnywhere)
		class AEnemyAIController* enemyAI;

	// Own
public:
	// Sets default values for this pawn's properties
	AEnemy();

	UFUNCTION()
		void Init(const int waveNumber, const float scale); // waveNumber with first wave as 0

	UFUNCTION()
		void StartMoving(AWaypoint* waypoint);

	UFUNCTION()
		void OnReachedEndPoint();

	UFUNCTION()
		void OnDying(const float overkillPercentage);

	UFUNCTION()
		void SetSpeed(const float newSpeed);

protected:
	UFUNCTION()
		void SetStats(const UEnemyData* newData); // waveNumber with first wave as 0

	// Events
public:
	UPROPERTY(BlueprintAssignable)
		FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable)
		FOnReachedCore OnReachedCore;

	// Overrides
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
