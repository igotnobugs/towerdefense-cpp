// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildNode.h"
#include "Components/SphereComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values
ABuildNode::ABuildNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Scene")));

	nodeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Node Mesh"));
	nodeMesh->SetupAttachment(RootComponent);
	nodeMesh->bEditableWhenInherited = true;


	nodeCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Node Collision"));
	nodeCollision->SetupAttachment(RootComponent);
	nodeCollision->bEditableWhenInherited = true;
}

bool ABuildNode::IsTaken()
{
	return isTaken;
}

bool ABuildNode::IsHovered()
{
	return isHovered;
}

void ABuildNode::SetTaken(const bool state, const bool updateMaterial)
{
	isTaken = state;

	if (updateMaterial)
		UpdateMaterial();
}

void ABuildNode::SetHovered(const bool state, const bool updateMaterial)
{
	isHovered = state;

	if (updateMaterial)
		UpdateMaterial();
}

void ABuildNode::UpdateMaterial()
{
	if (isTaken) {
		nodeMesh->SetMaterial(0, takenMaterial);
	}
	else {
		if (isHovered) {
			nodeMesh->SetMaterial(0, hoveredMaterial);
		}
		else {
			nodeMesh->SetMaterial(0, freeMaterial);
		}
	}


}

// Called when the game starts or when spawned
void ABuildNode::BeginPlay()
{
	Super::BeginPlay();

	nodeCollision->SetRelativeLocation(FVector(0, 0, 0));

	UpdateMaterial();

//#if WITH_EDITOR
//	this->SetFolderPath("BuildGrids/BuildNodes");
//#endif

}

// Called every frame
void ABuildNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

