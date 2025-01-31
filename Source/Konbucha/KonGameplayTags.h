#pragma once

#include "NativeGameplayTags.h"

namespace KonGameplayTags
{
	KONBUCHA_API	extern const TMap<uint8, FGameplayTag> MovementModeTagMap;
	
	KONBUCHA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Walking);
	KONBUCHA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_NavWalking);
	KONBUCHA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Falling);
	KONBUCHA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Swimming);
	KONBUCHA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Flying);
	KONBUCHA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Custom);

	KONBUCHA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_Death);
}

