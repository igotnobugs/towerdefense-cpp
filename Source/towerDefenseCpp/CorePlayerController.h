// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CorePlayerController.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerLeftClick);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerRightClick);

UCLASS()
class TOWERDEFENSECPP_API ACorePlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FOnPlayerLeftClick OnPlayerLeftClick;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FOnPlayerRightClick OnPlayerRightClick;
};
