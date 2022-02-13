// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TowerAIController.h"
#include "TowerGameState.h"
#include "TowerGameMode.h"
#include "CorePlayerController.h"
#include "TowerData.h"
#include "BuildNode.h"

// Sets default values
ATower::ATower()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Scene")));

	baseArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Base Arrow"));
	baseArrow->SetupAttachment(RootComponent);
	baseArrow->bEditableWhenInherited = true;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(baseArrow);
	baseMesh->bEditableWhenInherited = true;

	turretArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Turret Arrow"));
	turretArrow->SetupAttachment(baseArrow);
	turretArrow->bEditableWhenInherited = true;

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turretMesh->SetupAttachment(turretArrow);
	turretMesh->bEditableWhenInherited = true;

	barrelArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Barrel Arrow"));
	barrelArrow->SetupAttachment(turretMesh, TEXT("BarrelSocket"));
	barrelArrow->bEditableWhenInherited = true;

	sphereCollisionRange = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Range"));
	sphereCollisionRange->SetupAttachment(RootComponent);	
	sphereCollisionRange->bEditableWhenInherited = true;

	sphereMeshRange = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere Range Mesh"));
	sphereMeshRange->SetupAttachment(RootComponent);
	sphereMeshRange->bEditableWhenInherited = true;
	sphereMeshRange->SetVisibility(false);

	towerWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Tower Context Widget"));
	towerWidget->SetupAttachment(RootComponent);
	towerWidget->bEditableWhenInherited = true;
	towerWidget->SetVisibility(false);
}

bool ATower::SetStats(const UTowerData* newData, const int level)
{
	if (newData == nullptr) return false;
	if (!newData->towerLevels.IsValidIndex(level - 1)) return false;

	towerStat.level = level;
	const int indexLevel = level - 1;	

	baseMesh->SetStaticMesh(newData->towerLevels[indexLevel].towerBaseMesh);
	turretMesh->SetStaticMesh(newData->towerLevels[indexLevel].towerTurretMesh);

	towerStat.name = newData->towerLevels[indexLevel].name;
	towerStat.towerType = newData->towerLevels[indexLevel].towerType;
	towerStat.damage = newData->towerLevels[indexLevel].damage;
	towerStat.range = newData->towerLevels[indexLevel].range;
	towerStat.fireRate = newData->towerLevels[indexLevel].fireRate;
	towerStat.turnRate = newData->towerLevels[indexLevel].turnRate;
	towerStat.sellAmount += (newData->towerLevels[indexLevel].cost / 2);

	if (newData->towerLevels.IsValidIndex(indexLevel + 1)) {
		towerStat.upgradeCost = newData->towerLevels[indexLevel + 1].cost;
	}
	else {
		towerStat.upgradeCost = 0;
	}

	SetRange(towerStat.range);
	fireRateTrue = 1.0f / towerStat.fireRate;
	return true;
}

// Sets collision range and the visual mesh range
void ATower::SetRange(const float newRange)
{
	sphereCollisionRange->SetSphereRadius(newRange);
	
	float sphereScale = newRange / 50; // 50 -> The radius of the sphereMesh used
	sphereMeshRange->SetWorldScale3D(FVector(sphereScale, sphereScale, sphereScale));
	sphereMeshRange->SetRelativeLocation(FVector(0, 0, -50 * sphereScale));
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
	towerAI = Cast<ATowerAIController>(GetController());
	if (towerAI != nullptr) {
		towerAI->SetControlledTower(this);
	}

	towerGameState = Cast<ATowerGameState>(UGameplayStatics::GetGameState(GetWorld()));
	towerGameMode = Cast<ATowerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	playerController = Cast<ACorePlayerController>(GetWorld()->GetFirstPlayerController());
	playerController->OnPlayerLeftClick.AddDynamic(this, &ATower::OnLeftMouseClick);
	playerController->OnPlayerRightClick.AddDynamic(this, &ATower::OnRightMouseClick);
	
	turretMesh->OnBeginCursorOver.AddDynamic(this, &ATower::OnBeginMouseOver);
	turretMesh->OnEndCursorOver.AddDynamic(this, &ATower::OnEndMouseOver);

	baseMesh->OnBeginCursorOver.AddDynamic(this, &ATower::OnBeginMouseOver);
	baseMesh->OnEndCursorOver.AddDynamic(this, &ATower::OnEndMouseOver);

	turretMesh->OnClicked.AddDynamic(this, &ATower::OnBeginMouseClick);
	baseMesh->OnClicked.AddDynamic(this, &ATower::OnBeginMouseClick);

	sphereCollisionRange->OnComponentBeginOverlap.AddDynamic(this, &ATower::OnRangeReached);
	sphereCollisionRange->OnComponentEndOverlap.AddDynamic(this, &ATower::OnRangeExit);
	
	SetStats(towerData, 1);

	OnTowerBeginPlay();

#if WITH_EDITOR
	this->SetFolderPath("Towers");
#endif
}

void ATower::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	playerController->OnPlayerLeftClick.RemoveDynamic(this, &ATower::OnLeftMouseClick);
	playerController->OnPlayerRightClick.RemoveDynamic(this, &ATower::OnRightMouseClick);

	for (ABuildNode* node : nodesUsed) {
		node->SetHovered(false, false);
		node->SetTaken(false);
	}

	Super::EndPlay(EndPlayReason);
}
