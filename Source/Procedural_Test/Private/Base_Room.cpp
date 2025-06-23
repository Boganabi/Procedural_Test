// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Room.h"

// Sets default values
ABase_Room::ABase_Room()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	// root->SetupAttachment(RootComponent);
	RootComponent = root;

	EnemySpawns = CreateDefaultSubobject<USceneComponent>(TEXT("Enemy Spawn Points"));
	EnemySpawns->SetupAttachment(RootComponent);

	ItemSpawns = CreateDefaultSubobject<USceneComponent>(TEXT("Item Spawn Points"));
	ItemSpawns->SetupAttachment(RootComponent);

	Exits = CreateDefaultSubobject<USceneComponent>(TEXT("Exits"));
	Exits->SetupAttachment(RootComponent);

	Overlap_Detection = CreateDefaultSubobject<USceneComponent>(TEXT("Room Overlap"));
	Overlap_Detection->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABase_Room::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABase_Room::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

