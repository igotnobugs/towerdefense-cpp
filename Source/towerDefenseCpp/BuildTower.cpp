// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildTower.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "BuildNode.h"
#include "TowerData.h"
#include "TowerGameMode.h"
#include "TowerGameState.h"
#include "CorePlayerController.h"
#include "Camera/CameraActor.h"

ABuildTower::ABuildTower()
{
	PrimaryActorTick.bCanEverTick = true;

	nodeBuildBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Build Box"));
	nodeBuildBox->SetupAttachment(RootComponent);
	nodeBuildBox->bEditableWhenInherited = true;
}

void ABuildTower::Init(const class UTowerData& towerDatatoBuild, const bool continueBuilding)
{
	towerGameMode = Cast<ATowerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	towerToBuild = towerDatatoBuild.tower;
	nodeNeeded = towerDatatoBuild.nodes;
	goldCost = towerDatatoBuild.towerLevels[0].cost;

	continueToBuild = continueBuilding;
	
	FVector towerScale = FVector(1., 1., 1.) * nodeNeeded / 4.0f;

	baseArrow->SetWorldScale3D(towerScale);
	nodeBuildBox->SetWorldScale3D(towerScale);
	baseMesh->SetStaticMesh(towerDatatoBuild.towerLevels[0].towerBaseMesh);
	turretMesh->SetStaticMesh(towerDatatoBuild.towerLevels[0].towerTurretMesh);
	SetRange(towerDatatoBuild.towerLevels[0].range);
}


void ABuildTower::OnLeftMouseClick()
{
	BuildTower();
}

void ABuildTower::OnRightMouseClick()
{
	this->Destroy();
}

void ABuildTower::BuildTower()
{
	isBuilt = true;

	if (nodeCount != nodeNeeded) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cannot build here!"));
		return;
	} 

	bool hasGold = towerGameMode->UseGold(goldCost);	
	if (!hasGold) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Gold!"));
		return;
	}

	// Get midpoint of the nodes
	FVector buildLocation;
	for (ABuildNode* node : nodesCollided) {
		buildLocation += node->GetActorLocation();
		node->SetHovered(false, false);
		node->SetTaken(true);
	}
	buildLocation /= nodeNeeded;
	FTransform buildTransform = FTransform(buildLocation);

	// Spawn tower
	ATower* spawnedTower;
	spawnedTower = GetWorld()->SpawnActor<ATower>(towerToBuild, buildTransform);
	spawnedTower->nodesUsed = nodesCollided;

	OnTowerBuild.Broadcast(spawnedTower);

	if (!continueToBuild) {
		this->Destroy();
	}
	else {
		isBuilt = false;
	}
}

void ABuildTower::OnBuildBoxEnter(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (nodeCount >= nodeNeeded) return;
	
	ABuildNode* buildNode = Cast<ABuildNode>(OtherActor);	
	if (buildNode != nullptr && !buildNode->IsTaken() && !buildNode->IsTaken()) {

		buildNode->SetHovered(true);
		nodesCollided.Add(buildNode);

		nodeCount++;
		if (nodeCount == nodeNeeded) {
			baseMesh->SetMaterial(0, validMaterial);
			turretMesh->SetMaterial(0, validMaterial);

			if (allowSnap) {
				FVector snapLocation;
				for (ABuildNode* node : nodesCollided) {
					snapLocation += node->GetActorLocation();
				}
				snapLocation /= nodeNeeded;
				SetActorLocation(snapLocation, false);
				isSnapped = true;
			}

		}
	}
}

void ABuildTower::OnBuildBoxExit(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	ABuildNode* buildNode = Cast<ABuildNode>(OtherActor);
	if (buildNode != nullptr && nodesCollided.Contains(buildNode)) {
		buildNode->SetHovered(false);
		nodesCollided.Remove(buildNode);

		nodeCount--;
		if (nodeCount < nodeNeeded) {
			baseMesh->SetMaterial(0, invalidMaterial);
			turretMesh->SetMaterial(0, invalidMaterial);
		}
	}
}

void ABuildTower::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> outActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), 
		ACameraActor::StaticClass(), FName("LevelCamera"), outActors);

	levelCamera = Cast<ACameraActor>(outActors[0])->GetCameraComponent();
		
	towerGameState = Cast<ATowerGameState>(UGameplayStatics::GetGameState(GetWorld()));

	playerController = Cast<ACorePlayerController>(GetWorld()->GetFirstPlayerController());
	//playerController->OnPlayerLeftClick.AddDynamic(this, &ABuildTower::OnLeftMouseClick);
	//playerController->OnPlayerRightClick.AddDynamic(this, &ABuildTower::OnRightMouseClick);

	nodeBuildBox->OnComponentBeginOverlap.AddDynamic(this, &ABuildTower::OnBuildBoxEnter);
	nodeBuildBox->OnComponentEndOverlap.AddDynamic(this, &ABuildTower::OnBuildBoxExit);

	sphereMeshRange->SetVisibility(true);
	collisionParams.AddIgnoredActor(this);

	towerGameState->isBuildMode = true;
}

void ABuildTower::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (!isBuilt) {
		for (ABuildNode* node : nodesCollided) {
			node->SetHovered(false);
		}
	}

	towerGameState->isBuildMode = false;

	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ABuildTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool inScreen;
	inScreen = UGameplayStatics::GetPlayerController(GetWorld(), 0)
		->DeprojectMousePositionToWorld(worldLoc, worldDir);

	if (!inScreen) {
		SetActorLocation(voidSpace, true);
		return;
	}

	FVector pointLocation = (worldDir * 100000.0f) + worldLoc;
	FVector cameraLoc = levelCamera->GetComponentLocation();
	bool isHit = GetWorld()->LineTraceSingleByChannel(
		hit, cameraLoc, pointLocation, ECC_WorldStatic, collisionParams
	);
	
	if (isSnapped) {
		float distance = UKismetMathLibrary::Vector_Distance(
			hit.Location,
			GetActorLocation()
		);

		if (distance < distanceToUnsnap) return;
		isSnapped = false;
	}


	if (isHit) {
		SetActorLocation(hit.Location, true);
	}
	else {
		SetActorLocation(voidSpace, true);

	}
}
