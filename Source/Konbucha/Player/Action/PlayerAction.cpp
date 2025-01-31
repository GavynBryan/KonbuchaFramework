// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAction.h"

#include "GameFramework/Character.h"

UWorld* UPlayerAction::GetWorld() const
{
	if(ACharacter* Owner = ActionActorInfo.OwnerCharacter.Get()) {
		return Owner->GetWorld();
	}

	return nullptr;
}

void UPlayerAction::SetActorInfo(const FActionActorInfo ActorInfo)
{
	ActionActorInfo = ActorInfo;
}

void UPlayerAction::ExecuteAction_Implementation()
{
}


void UPlayerAction::FinishAction()
{
	OnActionSucceeded.Broadcast(ActionTag);
}

void UPlayerAction::CancelAction()
{
	OnActionCanceled.Broadcast(ActionTag);
}

