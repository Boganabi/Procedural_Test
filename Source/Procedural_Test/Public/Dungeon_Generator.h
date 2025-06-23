// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Base_Room.h"
#include "Components/BoxComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dungeon_Generator.generated.h"

UCLASS()
class PROCEDURAL_TEST_API ADungeon_Generator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeon_Generator();

	// Arrays to keep track of items, enemies, and doors
	TArray<USceneComponent*> ItemLocations;
	TArray<USceneComponent*> EnemySpawns;
	TArray<USceneComponent*> DoorList;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// helper function to calculate overlaps. returns false if nothing overlaps
	bool CheckOverlap(ABase_Room* room);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// recursively generates rooms, and outputs item, enemy, and door locations.
	UFUNCTION(BlueprintCallable)
		TArray<USceneComponent*> GenerateRooms(int numRooms, TArray<USceneComponent*> ExitList, TArray<UClass*> RoomTypes, FRandomStream StreamSeed, int depth = 0);

private:
	// private helper function to add the new spawning locations
	void addNewSpawns(ABase_Room* room, TArray<USceneComponent*> ExitList, USceneComponent* SelectedExit);
};
