// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyAIController.h"
#include "Waypoint.h"
#include "HealthComponent.h"
#include "BuffManager.h"
#include "EnemyData.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//SetRootComponent(CreateDefaultSubobject<USceneComponent>("Scene"));

	enemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Base Mesh"));
	enemyMesh->SetupAttachment(RootComponent);
	enemyMesh->bEditableWhenInherited = true;	
	enemyMesh->ComponentTags.Add(FName("Enemy"));

	targetArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Target Arrow"));
	targetArrow->SetupAttachment(enemyMesh);
	targetArrow->bEditableWhenInherited = true;

	health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	health->bEditableWhenInherited = true;
	health->OnHealthZero.AddDynamic(this, &AEnemy::OnDying);

	buffManager = CreateDefaultSubobject<UBuffManager>(TEXT("Buff Manager"));
	buffManager->bEditableWhenInherited = true;
}

void AEnemy::Init(const int waveNumber, const float scale)
{
	float actualWave = waveNumber - 1;
	float newHealth = health->GetMaxHealth() * (1.0f + (actualWave * scale));
	health->SetHealth(newHealth, true);
;}

void AEnemy::SetStats(const UEnemyData* newData)
{
	enemyStat.name = newData->name;
	enemyStat.enemyType = newData->enemyType;
	enemyStat.coreDamage = newData->coreDamage;
	enemyStat.goldReward = newData->goldReward;
	enemyStat.speed = newData->speed;

	health->SetHealth(newData->health, true);
	GetCharacterMovement()->MaxWalkSpeed = newData->speed;
}

void AEnemy::StartMoving(AWaypoint* waypoint)
{
	enemyAI->MoveToWaypoint(waypoint);
}

void AEnemy::OnReachedEndPoint()
{
	this->OnDeath.Broadcast(this, false);
	this->OnReachedCore.Broadcast(this);
	this->Destroy();
}

void AEnemy::OnDying(const float overkillPercentage)
{
	OnDeath.Broadcast(this, true);
	// Maybe do some effects I guess

	this->Destroy();
}

void AEnemy::SetSpeed(const float newSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = newSpeed;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	enemyAI = Cast<AEnemyAIController>(GetController());
	enemyAI->SetControlledEnemy(this);

	SetStats(enemyData);

#if WITH_EDITOR
	this->SetFolderPath("Enemies");
#endif

}