// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBuff.generated.h"

UCLASS()
class TOWERDEFENSECPP_API AEnemyBuff : public AActor
{
	GENERATED_BODY()
	
	// Variables
public:
	UPROPERTY(EditAnywhere)
		FName name;

	UPROPERTY(EditAnywhere)
		float damage = 3.0f; //Could be anything

	UPROPERTY(EditAnywhere)
		float duration = 3.0f;

	UPROPERTY(EditAnywhere)
		bool stackable = false;

protected:
	UPROPERTY(VisibleAnywhere)
		class AEnemy* buffOwner;

public:	
	// Sets default values for this actor's properties
	AEnemyBuff();


public:
	UFUNCTION()
		virtual void Init(const float setDamage, const float setDuration);

	UFUNCTION()
		virtual bool ApplyBuff(AEnemy* enemy) {return false;};

	UFUNCTION()
		virtual void RemoveBuff() {};


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};
