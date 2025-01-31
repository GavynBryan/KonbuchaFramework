// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NPCManager.generated.h"


class ANPCCharacterBase;

/*
 * A timeslot in an NPC's schedule
 */
USTRUCT(Blueprintable)
struct FNPCTimeSlot 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ScheduleName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StartTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EndTime = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TargetScene;

	//This property is mostly used for handling scene transitions or interpolating position when NPCs are loaded in
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ScheduleEvent;

	bool IsValid() const {
		return !ScheduleName.IsNone();
	}
};

/*
 * A lightweight representation of an NPC in memory 
 */
USTRUCT(Blueprintable)
struct FNPCRepresentation
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<ANPCCharacterBase> Ref;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FNPCTimeSlot CurrentSchedule;
};

/*
 * Maybe it's redundant, but whatever. Making a datatable to store all NPC IDs and link them to their respective BPs
 * So we can dynamically spawn them.
 */
USTRUCT(BlueprintType)
struct FNPCData : public FTableRowBase {
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<AActor> NPCBlueprintClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FNPCTimeSlot> Schedules;
};

USTRUCT(BlueprintType)
struct FActiveScheduleEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FNPCTimeSlot ActiveSchedule; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeInSchedule = 0.0f;
};

UCLASS()
class KONBUCHA_API UNPCManager : public UObject
{
	GENERATED_BODY()

public:
	void UpdateAllNPCs();

	UFUNCTION(BlueprintCallable)
	void PopulateSpawnMap(UDataTable* DataTable);
	UFUNCTION(BlueprintCallable)
	void PopulateNPCMap_Default();
	UFUNCTION(BlueprintCallable)
	void PopulateHourlyScheduleCache_Default(UDataTable* DataTable);
	UFUNCTION(BlueprintCallable)
	FNPCTimeSlot FindScheduleByName(const FName& ScheduleName);
	UFUNCTION(BlueprintCallable)
	bool RemoveScheduleByName(const FName& ScheduleName);
	UFUNCTION(BlueprintCallable)
	bool AddSchedule(const FName& NPCName, const FNPCTimeSlot& NewSchedule);
private:
	//Index: NPC Name
	TMap<FName, FNPCRepresentation> AllNPCs;
	//Index: NPC Name
	TMap<FName, TSoftClassPtr<AActor>> NPCSpawnMap;

	//Index: Hour, NPC Name
	TMap<int, TMap<FName, FNPCTimeSlot>> HourlyScheduleCache;
	//Index: NPC Name
	TMap<FName, FActiveScheduleEntry> ActiveSchedules;
};
