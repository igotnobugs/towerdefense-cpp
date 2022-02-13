// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildNode.generated.h"

UCLASS()
class TOWERDEFENSECPP_API ABuildNode : public AActor
{
	GENERATED_BODY()
	
	// Variables
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMaterialInstance* freeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMaterialInstance* hoveredMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMaterialInstance* takenMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool isTaken;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool isHovered;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* nodeMesh;

	UPROPERTY(EditAnywhere)
		class USphereComponent* nodeCollision;

	// Own
public:	
	// Sets default values for this actor's properties
	ABuildNode();

	UFUNCTION(BlueprintPure)
		bool IsTaken();

	UFUNCTION(BlueprintPure)
		bool IsHovered();

	UFUNCTION()
		void SetTaken(const bool state, const bool updateMaterial = true);

	UFUNCTION()
		void SetHovered(const bool state, const bool updateMaterial = true);

private:
	void UpdateMaterial();

	// Overrides
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
