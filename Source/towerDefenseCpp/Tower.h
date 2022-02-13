// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tower.generated.h"

// Tower 
//   |--> TurretTower 
//	 |		|-> GunTower <-- Aim and Shoot
//	 |		|-> MissileTower  <-- Get Target, make projectile track it
//   |      |-> LaserTower <-- like a gun but continuously damage target
//	 |		|-> EmpTower <-- slow all in range
//   |      |-> PowerGeneratorTower <- Gets towers in range and gives them a buff
//	 |		\-> SalvagerTower <- Add gold passively and adds bonus gold to enemies destroyed in range
//   \--> BuildTower

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTowerBuild, class ATower*, tower);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTowerSold, class ATower*, tower);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTowerUpgrade, class ATower*, tower);

UENUM(BlueprintType)
enum class ETowerType : uint8 {
	TE_TargetsLand		UMETA(DisplayName = "Targets Land"), //0
	TE_TargetsAir		UMETA(DisplayName = "Targets Air"), //1
	TE_TargetsBoth		UMETA(DisplayName = "Targets Both") //2
};

USTRUCT(BlueprintType)
struct FTowerStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ETowerType towerType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float damage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float range = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float fireRate = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float turnRate = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int cost = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int sellAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int upgradeCost = 0;
};

UCLASS()
class TOWERDEFENSECPP_API ATower : public APawn
{
	GENERATED_BODY()

	// Variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTowerData* towerData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FTowerStat towerStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UArrowComponent* barrelArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<class ABuildNode*> nodesUsed;

protected:
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* baseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UArrowComponent* baseArrow;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* turretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UArrowComponent* turretArrow;

	UPROPERTY(EditAnywhere)
		class USphereComponent* sphereCollisionRange;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* sphereMeshRange;

	UPROPERTY(EditAnywhere)
		class ATowerAIController* towerAI;

	UPROPERTY(EditAnywhere)
		class UWidgetComponent* towerWidget;

	UPROPERTY(VisibleAnywhere)
		class ATowerGameState* towerGameState;

	UPROPERTY(VisibleAnywhere)
		class ACorePlayerController* playerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float fireRateTrue = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float fireRateCountdown = 0;

	class ATowerGameMode* towerGameMode;

	// Own
public:
	// Sets default values for this pawn's properties
	ATower();

	UFUNCTION()
		bool SetStats(const UTowerData* newData, const int level = 1); // Use real level

	UFUNCTION()
		void SetRange(const float newRange);

	UFUNCTION(BlueprintPure)
		UArrowComponent* GetBaseArrow() { return baseArrow; };

	UFUNCTION(BlueprintPure)
		UStaticMesh* GetBaseMesh() { return baseMesh->GetStaticMesh(); };

	UFUNCTION(BlueprintPure)
		UStaticMesh* GetTurretMesh() { return turretMesh->GetStaticMesh(); };

	UFUNCTION(BlueprintPure)
		UStaticMesh* GetRangeMesh() { return sphereMeshRange->GetStaticMesh(); };

	UFUNCTION(BlueprintCallable)
		virtual bool UpgradeTower() { return false; };

	UFUNCTION(BlueprintCallable)
		virtual void SellTower() {};

protected:
	UFUNCTION() // Click anywhere
		virtual void OnLeftMouseClick() {};

	UFUNCTION() // Click anywhere
		virtual void OnRightMouseClick() {};

	UFUNCTION() // Mouse hover on
		virtual void OnBeginMouseOver(class UPrimitiveComponent* OverlappedComp) {};

	UFUNCTION() // Mouse hover away
		virtual void OnEndMouseOver(class UPrimitiveComponent* OverlappedComp) {};

	UFUNCTION() //Click on the tower
		virtual void OnBeginMouseClick(class UPrimitiveComponent* OverlappedComp, FKey ButtonPressed) {};

	UFUNCTION()
		virtual void OnRangeReached(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult) {};

	UFUNCTION()
		virtual void OnRangeExit(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex) {};

	UFUNCTION(BlueprintImplementableEvent)
		void OnFire();

	virtual void OnTowerBeginPlay() {};


public:
	UPROPERTY(BlueprintAssignable)
		FOnTowerBuild OnTowerBuild;

	UPROPERTY(BlueprintAssignable)
		FOnTowerSold OnTowerSold;

	UPROPERTY(BlueprintAssignable)
		FOnTowerSold OnTowerUpgrade;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
