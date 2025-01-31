#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KonGameInstance.generated.h"

class UNPCManager;
class UQuestManager;

UCLASS(BlueprintType)
class KONBUCHA_API UKonGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UKonGameInstance(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION(BlueprintCallable)
	UQuestManager* GetQuestManager() const { return QuestManager;}
	UFUNCTION(BlueprintCallable)
	UNPCManager* GetNPCManager() const {return NPCManager;}

protected:
	UPROPERTY()
	TObjectPtr<UQuestManager> QuestManager;
	UPROPERTY()
	TObjectPtr<UNPCManager> NPCManager;
};