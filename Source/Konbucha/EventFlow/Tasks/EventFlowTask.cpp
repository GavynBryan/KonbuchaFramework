// Fill out your copyright notice in the Description page of Project Settings.


#include "EventFlowTask.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Konbucha/Character/KonBaseCharacter.h"
#include "Konbucha/EventFlow/EventFlowchart.h"


bool UEventFlowTask::IsFlowchartValid() const
{
	return Flowchart && Flowchart->IsValidLowLevel();
}

AKonBaseCharacter* UEventFlowTask::FindCharacter(FName CharacterID)
{
	if (CachedCharacters.Contains(CharacterID))
	{
		TWeakObjectPtr<AKonBaseCharacter> WeakPtr = CachedCharacters[CharacterID];
		if (WeakPtr.IsValid()) {
			return WeakPtr.Get();
		}
		//Remove invalid characters from cache
		CachedCharacters.Remove(CharacterID);
	}
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AKonBaseCharacter::StaticClass(), FoundActors);
	
	for (TActorIterator<AKonBaseCharacter> It(GetWorld()); It; ++It)
	{
		AKonBaseCharacter* Character = *It;
		if (Character && Character->NameID == CharacterID)
		{
			CachedCharacters.Add(CharacterID, Character);
			return Character;
		}
	}

	return nullptr;
}

