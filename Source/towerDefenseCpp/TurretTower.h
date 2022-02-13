// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "TurretTower.generated.h"

/** Tower -> TurretTower
 * 
 */
UCLASS()
class TOWERDEFENSECPP_API ATurretTower : public ATower
{
	GENERATED_BODY()
	
	// Variables
protected:
	UPROPERTY(VisibleAnywhere)
		TSubclassOf<class AProjectile> projectile;

	UPROPERTY(VisibleAnywhere)
		TSubclassOf<class AEnemyBuff> buffToAdd;

	UPROPERTY(VisibleAnywhere)
		int fireCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<class AEnemy*> enemiesInRange;

	UPROPERTY(VisibleAnywhere, Category = "Input States")
		bool isHovered = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tower States")
		bool isOverloaded = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tower States")
		float overloadScale = 1;

	// Own
public:
	// Sets default values for this pawn's properties
	ATurretTower();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		int GetNumberOfEnemiesInRange() { return enemiesInRange.Num(); };

	UFUNCTION(BlueprintCallable, BlueprintPure)
		AEnemy* GetFirstTargetEnemy() { return enemiesInRange[0]; };

	UFUNCTION(BlueprintCallable)
		void RotateTurret(float DeltaTime, const FRotator rotation);

	UFUNCTION(BlueprintCallable)
		virtual float Shoot(AEnemy* enemyTarget = nullptr) { return 0; };

	UFUNCTION(BlueprintCallable)
		virtual bool OverloadTower(const float scale);

	UFUNCTION(BlueprintCallable)
		virtual void UnOverloadTower(const float scale);

	virtual bool UpgradeTower() override;
	virtual void SellTower() override;

protected:
	virtual void OnTowerBeginPlay() override;

	virtual void OnLeftMouseClick() override;
	virtual void OnRightMouseClick() override;
	virtual void OnBeginMouseOver(class UPrimitiveComponent* OverlappedComp) override;
	virtual void OnEndMouseOver(class UPrimitiveComponent* OverlappedComp) override;
	virtual void OnBeginMouseClick(class UPrimitiveComponent* OverlappedComp, FKey ButtonPressed) override;

	void OnRangeReached(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, 
		const FHitResult& SweepResult) override;

	void OnRangeExit(class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
