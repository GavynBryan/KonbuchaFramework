#pragma once

#include "CoreMinimal.h"
#include "GameplayTask.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Konbucha/EventFlow/EventFlowchart.h"
#include "EventFlowTask.generated.h"

// Forward declaration of your flowchart class
class UEventFlowchart;

UCLASS(Abstract)
class KONBUCHA_API UEventFlowTask : public UGameplayTask
{
	GENERATED_BODY()

public:
	// Pointer to the owning flowchart
	UPROPERTY()
	TObjectPtr<UEventFlowchart> Flowchart;

public:
	// Factory method for task creation
	template <class T>
	static T* CreateEventFlowTask(UEventFlowchart* InFlowchart)
	{
		if (!InFlowchart)
		{
			UE_LOG(LogTemp, Warning, TEXT("CreateEventFlowTask: Invalid flowchart!"));
			return nullptr;
		}

		T* Task = NewObject<T>();
		Task->InitTask(*InFlowchart, InFlowchart->GetGameplayTaskDefaultPriority());
		return Task;
	}


protected:
	// Validation function for the flowchart
	bool IsFlowchartValid() const;

	UFUNCTION(BlueprintCallable)
	AKonBaseCharacter* FindCharacter(FName CharacterID);
};
