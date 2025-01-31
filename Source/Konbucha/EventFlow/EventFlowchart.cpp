// Fill out your copyright notice in the Description page of Project Settings.


#include "EventFlowchart.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Konbucha/Character/NPC/NPCCharacterBase.h"
#include "Tasks/EventFlowTask.h"

void UEventFlowchart::OnGameplayTaskInitialized(UGameplayTask& Task)
{
	UEventFlowTask* FlowTask = Cast<UEventFlowTask>(&Task);

	if(FlowTask) {
		FlowTask->Flowchart = this;
	}
}

UWorld* UEventFlowchart::GetWorld() const
{
	if(AActor* Owner = Cast<AActor>(GetOuter())) {
		return Owner->GetWorld();
	}

	return nullptr;
}
