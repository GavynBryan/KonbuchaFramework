// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCManager.h"

void UNPCManager::UpdateAllNPCs()
{
	for (auto Element : AllNPCs) {
		
	}
}

void UNPCManager::PopulateSpawnMap(UDataTable* DataTable)
{
	if (!DataTable) {
		UE_LOG(LogTemp, Warning, TEXT("DataTable is null in PopulateSpawnMap!"));
		return;
	}

	NPCSpawnMap.Empty();

	// Iterate over each row in the DataTable
	DataTable->ForeachRow<FNPCData>(TEXT("PopulateSpawnMap"), [this](const FName& Key, const FNPCData& Row) {
		if (!Row.NPCBlueprintClass.IsNull()) {
			// Add the NPC to the spawn map
			NPCSpawnMap.Add(Key, Row.NPCBlueprintClass);
			UE_LOG(LogTemp, Log, TEXT("Added NPC %s to the spawn map."), *Key.ToString());
		} else {
			UE_LOG(LogTemp, Warning, TEXT("NPCBlueprintClass is null for NPC %s."), *Key.ToString());
		}
	});

	UE_LOG(LogTemp, Log, TEXT("Spawn map populated with %d entries."), NPCSpawnMap.Num());
}

void UNPCManager::PopulateNPCMap_Default()
{
	if (NPCSpawnMap.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("NPCSpawnMap is empty. Populate it before calling PopulateAllNPCs."));
		return;
	}
	
	AllNPCs.Empty();
	
	for (const auto& Entry : NPCSpawnMap) {
		const FName& NPCID = Entry.Key;

		// Check if the NPC is already in AllNPCs
		if (!AllNPCs.Contains(NPCID)) {
			// Create a new FNPCRepresentation with default values
			FNPCRepresentation NewNPC;
			NewNPC.Ref = nullptr; 
			NewNPC.CurrentSchedule = FNPCTimeSlot(); 
			NewNPC.TimeSinceScheduleChange = 0.0f;

			// Add the new NPC to the AllNPCs map
			AllNPCs.Add(NPCID, NewNPC);
			UE_LOG(LogTemp, Log, TEXT("Added NPC %s to AllNPCs with default values."), *NPCID.ToString());
		} else {
			UE_LOG(LogTemp, Warning, TEXT("NPC %s is already in AllNPCs. Skipping."), *NPCID.ToString());
		}
	}

	UE_LOG(LogTemp, Log, TEXT("AllNPCs populated with %d entries."), AllNPCs.Num());
}

void UNPCManager::PopulateHourlyScheduleCache_Default(UDataTable* DataTable)
{
	if (!DataTable) {
		UE_LOG(LogTemp, Warning, TEXT("DataTable is null in PopulateHourlyScheduleCache!"));
		return;
	}

	// Clear the existing cache
	HourlyScheduleCache.Empty();

	// Iterate through the DataTable
	DataTable->ForeachRow<FNPCData>(TEXT("PopulateHourlyScheduleCache"), [this](const FName& Key, const FNPCData& Row) {
		const FName& NPCID = Key; // Each row's key is the NPC ID

		// Iterate through the schedules for this NPC
		for (const FNPCTimeSlot& TimeSlot : Row.Schedules) {
			int Hour = TimeSlot.StartTime; // Use StartTime directly as it’s already in hours

			// Add the schedule to the HourlyScheduleCache
			TMap<FName, TArray<FNPCTimeSlot>>& NPCMap = HourlyScheduleCache.FindOrAdd(Hour);
			NPCMap.FindOrAdd(NPCID).Add(TimeSlot);

			UE_LOG(LogTemp, Log, TEXT("Added schedule '%s' for NPC %s to Hour %d"),
				   *TimeSlot.ScheduleName.ToString(), *NPCID.ToString(), Hour);
		}
	});

	UE_LOG(LogTemp, Log, TEXT("HourlyScheduleCache populated with %d hourly entries."), HourlyScheduleCache.Num());
}

FNPCTimeSlot UNPCManager::FindScheduleByName(const FName& ScheduleName)
{
	// Check if the hour exists in the cache
	if (TMap<FName, FNPCTimeSlot> NPCMap = HourlyScheduleCache.Find(Hour)) {
		// Check if the NPC has a schedule for this hour
		if (FNPCTimeSlot* Schedule = NPCMap->Find(NPCName)) {
			return Schedule;
		} else {
			UE_LOG(LogTemp, Warning, TEXT("NPC '%s' does not have a schedule for hour '%d'."), *NPCName.ToString(), Hour);
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("No schedules exist for hour '%d'."), Hour);
	}

	return nullptr;
}

bool UNPCManager::RemoveScheduleByName(const FName& ScheduleName)
{
	if (ScheduleName.IsNone()) {
		UE_LOG(LogTemp, Warning, TEXT("Invalid ScheduleName provided to RemoveScheduleByName."));
		return false;
	}

	bool bRemoved = false;

	// Iterate through all hours in the HourlyScheduleCache
	for (auto& HourEntry : HourlyScheduleCache) {
		int Hour = HourEntry.Key;
		TMap<FName, FNPCTimeSlot>& NPCMap = HourEntry.Value;

		// Iterate through each NPC in the hour
		for (auto It = NPCMap.CreateIterator(); It; ++It) {
			FName NPCName = It->Key;
			const FNPCTimeSlot& TimeSlot = It->Value;

			// Check if the schedule name matches
			if (TimeSlot.ScheduleName == ScheduleName) {
				UE_LOG(LogTemp, Log, TEXT("Removed schedule '%s' for NPC '%s' at hour '%d'."),
					   *ScheduleName.ToString(), *NPCName.ToString(), Hour);

				// Remove the NPC entry
				It.RemoveCurrent();
				bRemoved = true;
			}
		}

		// Clean up the hour entry if it becomes empty
		if (NPCMap.Num() == 0) {
			HourlyScheduleCache.Remove(Hour);
			UE_LOG(LogTemp, Log, TEXT("Removed hour '%d' from HourlyScheduleCache as it has no NPCs."), Hour);
		}
	}

	if (!bRemoved) {
		UE_LOG(LogTemp, Warning, TEXT("Schedule '%s' not found in HourlyScheduleCache."), *ScheduleName.ToString());
	}

	return bRemoved;
}

bool UNPCManager::AddSchedule(const FName& NPCName, const FNPCTimeSlot& NewSchedule)
{
	if (NPCName.IsNone() || !NewSchedule.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("Invalid input to AddToHourlyScheduleCache."));
		return false;
	}

	int Hour = NewSchedule.StartTime; // Assuming StartTime is in hours

	// Get or create the NPC map for the hour
	TMap<FName, FNPCTimeSlot>& NPCMap = HourlyScheduleCache.FindOrAdd(Hour);

	// Check if the NPC already has a schedule for this hour
	if (NPCMap.Contains(NPCName)) {
		UE_LOG(LogTemp, Warning, TEXT("NPC '%s' already has a schedule for hour '%d'. Overwriting it."),
			   *NPCName.ToString(), Hour);
	}

	// Add or overwrite the NPC's schedule for this hour
	NPCMap.Add(NPCName, NewSchedule);
	UE_LOG(LogTemp, Log, TEXT("Added schedule '%s' for NPC '%s' at hour '%d'."),
		   *NewSchedule.ScheduleName.ToString(), *NPCName.ToString(), Hour);

	return true;
}