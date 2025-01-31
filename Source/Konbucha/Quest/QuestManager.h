// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "QuestManager.generated.h"

USTRUCT(Blueprintable)
struct FQuest
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Stage = 0;
};

/**
 * 
 */
UCLASS(BlueprintType)
class KONBUCHA_API UQuestManager : public UObject
{
	GENERATED_BODY()
	UQuestManager();
	
public:
	UFUNCTION(BlueprintCallable)
	int GetQuestStage(FName QuestID);

	UFUNCTION(BlueprintCallable)
	void SetQuestStage(FName QuestID, int Stage);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<FName, FQuest> QuestLog;
};
