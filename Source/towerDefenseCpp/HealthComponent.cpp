// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::SetHealth(const float amount, const bool setMaxToo)
{
	if (setMaxToo) {
		maxHealth = amount;
		health = amount;
	}
	else {
		if (amount > maxHealth) {
			health = maxHealth;
		}
		else {
			health = amount;
		}
	}
}

float UHealthComponent::GetHealth(const bool getPercentage)
{
	if (getPercentage) return health / maxHealth;
	return health;
}

float UHealthComponent::GetMaxHealth()
{
	return maxHealth;
}

bool UHealthComponent::DamageHealth(const float amount)
{
	health -= amount;
	if (health <= 0) {
		const float overkill = (health * -1) / maxHealth;
		OnHealthZero.Broadcast(overkill);

		health = 0;
		return true;
	}
	return false;
}

void UHealthComponent::HealHealth(const float amount)
{
	health += amount;
	if (health > maxHealth) {
		health = maxHealth;
	}
}

bool UHealthComponent::AmIDead()
{
	return health <= 0;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	if (maxHealth <= 0) maxHealth = 1;

	if (startAtMaxHealth) {
		health = maxHealth;
	}
	
}
