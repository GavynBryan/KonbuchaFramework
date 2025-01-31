#include "KonGameInstance.h"
#include "Engine/LevelStreaming.h"
#include "Konbucha/Quest/QuestManager.h"

UKonGameInstance::UKonGameInstance(const FObjectInitializer& ObjectInitializer)
{
	QuestManager = ObjectInitializer.CreateDefaultSubobject<UQuestManager>(this, TEXT("QuestManager"));
	NPCManager = ObjectInitializer.CreateDefaultSubobject<UNPCManager>(this, TEXT("NPCManager"));
}
