// Copyright AI


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* TargetDataUnderMouse = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return TargetDataUnderMouse;
}

void UTargetDataUnderMouse::Activate()
{
	const APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	ValidData.Broadcast(CursorHit.Location);
}
