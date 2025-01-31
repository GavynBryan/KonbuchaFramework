// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "PlayerAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerActionEvent, FGameplayTag, ActionTag);

USTRUCT(BlueprintType)
struct FActionActorInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<ACharacter> OwnerCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<APlayerController> PlayerController;
};

UCLASS(Blueprintable)
class KONBUCHA_API UPlayerAction : public UObject
{
	GENERATED_BODY()
	

protected:
	virtual UWorld* GetWorld() const override;

public:
	UFUNCTION(BlueprintCallable)
	void SetActorInfo(const FActionActorInfo ActorInfo);
	
	UFUNCTION(BlueprintCallable)
	FGameplayTag GetGameplayTag() const { return ActionTag; }
	UFUNCTION(BlueprintCallable)
	FActionActorInfo GetActorInfo() const { return ActionActorInfo; }
	UFUNCTION(BlueprintCallable)
	APlayerController* GetPlayerController() const { return ActionActorInfo.PlayerController.Get(); }
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ExecuteAction();
	UFUNCTION(BlueprintCallable)
	void FinishAction();
	UFUNCTION(BlueprintCallable)
	void CancelAction();

protected:
	UPROPERTY(BlueprintAssignable)
	FPlayerActionEvent OnActionSucceeded;

	UPROPERTY(BlueprintAssignable)
	FPlayerActionEvent OnActionCanceled;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FGameplayTag ActionTag;
	UPROPERTY()
	FActionActorInfo ActionActorInfo;
};
