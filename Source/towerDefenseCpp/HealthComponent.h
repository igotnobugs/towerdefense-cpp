// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

//DECLARE_MULTICAST_DELEGATE(FOnHealthZero);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthZero, float, overkillPercentage);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSECPP_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	// Variables
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float maxHealth = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float health = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool startAtMaxHealth = true;

	// Own
public:	
	// Sets default values for this component's properties
	UHealthComponent();

	// Set only health unless max is true, then sets both
	UFUNCTION(BlueprintCallable)
		void SetHealth(const float amount, const bool setMaxToo = true);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetHealth(const bool getPercentage);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetMaxHealth();

	UFUNCTION(BlueprintCallable)
		bool DamageHealth(const float amount);

	UFUNCTION(BlueprintCallable)
		void HealHealth(const float amount);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool AmIDead();

public:
	UPROPERTY()
		FOnHealthZero OnHealthZero;

	// Overrides
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
