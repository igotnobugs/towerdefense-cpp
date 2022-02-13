// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "BuildTower.generated.h"



UCLASS()
class TOWERDEFENSECPP_API ABuildTower : public ATower
{
	GENERATED_BODY()

	// Variable
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Build Settings")
		bool allowSnap = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Build Settings")
		float distanceToUnsnap = 225.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Build Settings")
		UMaterialInstance* validMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Build Settings")
		UMaterialInstance* invalidMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TSubclassOf<class ATower> towerToBuild;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<class ABuildNode*> nodesCollided;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* nodeBuildBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* levelCamera;

private:
	int goldCost = 0;
	int nodeNeeded = 4;
	int nodeCount = 0;
	bool isBuilt = false;
	bool continueToBuild = false;
	bool isSnapped = false;
	class ATowerGameMode* towerGameMode;

	FVector voidSpace = FVector(0, 0, -9999999.0f);
	FVector worldLoc;
	FVector worldDir; 
	FHitResult hit;
	FCollisionQueryParams collisionParams;

	// Own
public:
	// Sets default values for this pawn's properties
	ABuildTower();

	void Init(const class UTowerData& towerDatatoBuild, const bool continueBuilding = true);

protected:
	virtual void OnLeftMouseClick() override;
	virtual void OnRightMouseClick() override;

	UFUNCTION(BlueprintCallable)
		void BuildTower();

	UFUNCTION()
		void OnBuildBoxEnter(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnBuildBoxExit(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	// Overrides
protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
