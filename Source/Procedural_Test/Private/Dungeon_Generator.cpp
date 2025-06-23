// Fill out your copyright notice in the Description page of Project Settings.


#include "Dungeon_Generator.h"

// Sets default values
ADungeon_Generator::ADungeon_Generator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADungeon_Generator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADungeon_Generator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<USceneComponent*> ADungeon_Generator::GenerateRooms(int numRooms, TArray<USceneComponent*> ExitList, TArray<UClass*> RoomTypes, FRandomStream StreamSeed, int depth) {
	for (int i = numRooms; i > 0; i--) {

		/*if (depth > RoomTypes.Num() * 2) {
			UE_LOG(LogTemp, Warning, TEXT("Too many failed attempts!"));
			return ExitList;
		}*/

		if (ExitList.Num() == 0) {
			return ExitList;
		}

		int32 idx = StreamSeed.RandRange(0, ExitList.Num() - 1); // choose one of the available exits
		USceneComponent* SelectedExit = ExitList[idx];

		if (SelectedExit) {
			idx = StreamSeed.RandRange(0, RoomTypes.Num() - 1); // choose a type of room to spawn
			UClass* classToSpawn = RoomTypes[idx];
			ABase_Room* newRoom = GetWorld()->SpawnActor<ABase_Room>(classToSpawn, SelectedExit->GetComponentTransform());
			
			if (CheckOverlap(newRoom)) { // check that the room does not intersect another room
				newRoom->Destroy();
				i++; // so that we can retry spawning the room
				continue;
				// return GenerateRooms(numRooms, ExitList, RoomTypes, StreamSeed, depth++); // depth++ to add 1 failure count
			}
			else {
				ExitList.Remove(SelectedExit);

				TArray<USceneComponent*> children;
				newRoom->Exits->GetChildrenComponents(false, children);
				ExitList.Append(children);

				addNewSpawns(newRoom, ExitList, SelectedExit); // modify lists to add available spawn points for items and enemies
				
				//if (numRooms <= 1) {
				//	// finished, can now return
				//	return ExitList;
				//}
				//else {
				//	// recursive call
				//	return GenerateRooms(numRooms--, ExitList, RoomTypes, StreamSeed, 0); // 0 resets depth
				//}
			}
		}
	}
	return ExitList; // return unused exits
}

bool ADungeon_Generator::CheckOverlap(ABase_Room* room) {
	TArray<USceneComponent*> children;

	room->Overlap_Detection->GetChildrenComponents(false, children);
	for (USceneComponent* sc : children) {
		TArray<UPrimitiveComponent*> overlaps;

		UBoxComponent* bc = Cast<UBoxComponent>(sc);
		bc->GetOverlappingComponents(overlaps);

		if (!overlaps.IsEmpty()) {
			return true;
		}
	}
	return false;
}

void ADungeon_Generator::addNewSpawns(ABase_Room* room, TArray<USceneComponent*> ExitList, USceneComponent* SelectedExit) {
	TArray<USceneComponent*> children;

	room->ItemSpawns->GetChildrenComponents(false, children);
	ItemLocations.Append(children);

	room->EnemySpawns->GetChildrenComponents(false, children);
	this->EnemySpawns.Append(children);

	DoorList.Add(SelectedExit);
}