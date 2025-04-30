// Copyright AI


#include "UI/WidgetController/AuraOverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/AuraPlayerState.h"

void UAuraOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
	
	FOnHealthChanged.Broadcast(GetAuraAttributeSet()->GetHealth());
	FOnMaxHealthChanged.Broadcast(GetAuraAttributeSet()->GetMaxHealth());
	FOnManaChanged.Broadcast(GetAuraAttributeSet()->GetMana());
	FOnMaxManaChanged.Broadcast(GetAuraAttributeSet()->GetMaxMana());
}

void UAuraOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
	
	GetAuraPlayerState()->OnXPChangedDelegate.AddUObject(this, &UAuraOverlayWidgetController::OnXPChanged);
	GetAuraPlayerState()->OnLevelChangedDelegate.AddLambda(
		[this](int32 NewLevel)
		{
			OnPlayerLevelChangedDelegate.Broadcast(NewLevel);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAttributeSet()->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			FOnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAttributeSet()->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			FOnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAttributeSet()->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			FOnManaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAttributeSet()->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			FOnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	if (GetAuraAbilitySystemComponent())
	{
		if (GetAuraAbilitySystemComponent()->bStartupAbilitiesGiven)
		{
			BroadcastAbilityInfo();
		}
		else
		{
			GetAuraAbilitySystemComponent()->AbilitiesGivenDelegate.AddUObject(this, &UAuraOverlayWidgetController::BroadcastAbilityInfo);	
		}

		GetAuraAbilitySystemComponent()->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDatatableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);	
				}
			}
		});
	}
}

void UAuraOverlayWidgetController::OnXPChanged(int32 NewXP)
{
	const ULevelUpInfo* LevelUpInfo = GetAuraPlayerState()->LevelUpInfo;
	checkf(LevelUpInfo, L"Unable to get level up info. Please fill out AuraPlayerState Blueprint");

	const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);

	if (const int32 MaxLevel = LevelUpInfo->LevelUpInfo.Num(); Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInfo[Level].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInfo[Level - 1].LevelUpRequirement;

		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);
		OnXPPercentageChangedDelegate.Broadcast(XPBarPercent);
	}
}
