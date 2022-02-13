// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowBuff.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy.h"

bool ASlowBuff::ApplyBuff(AEnemy* enemy)
{
	if (enemy == nullptr) return false;

	buffOwner = enemy;
	buffOwner->Tags.Add(name);
	buffOwner->GetCharacterMovement()->MaxWalkSpeed 
		= buffOwner->GetCharacterMovement()->GetMaxSpeed() * slowScale;

	return true;
}

void ASlowBuff::RemoveBuff()
{
	if (buffOwner == nullptr) return;

	buffOwner->Tags.RemoveSingle(name);
	
	buffOwner->GetCharacterMovement()->MaxWalkSpeed 
		= buffOwner->GetCharacterMovement()->GetMaxSpeed() / slowScale;
}
