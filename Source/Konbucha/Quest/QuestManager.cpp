// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"

UQuestManager::UQuestManager()
{
}

int UQuestManager::GetQuestStage(FName QuestID)
{
	check(!QuestID.IsNone());
	
	if (QuestLog.Contains(QuestID))
	{
		return QuestLog[QuestID].Stage;
	}

	return -1;
}

void UQuestManager::SetQuestStage(FName QuestID, int Stage)
{
	if (QuestLog.Contains(QuestID))
	{
		QuestLog[QuestID].Stage = Stage;;
		return;
	}

	QuestLog.Add(QuestID, FQuest(Stage));
}
