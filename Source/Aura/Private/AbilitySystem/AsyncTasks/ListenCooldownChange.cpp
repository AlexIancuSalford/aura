// Copyright Alexandru Iancu


#include "AbilitySystem/AsyncTasks/ListenCooldownChange.h"

#include "AbilitySystemComponent.h"

UListenCooldownChange* UListenCooldownChange::ListenCooldownChange(UAbilitySystemComponent* AbilitySystemComponent,
                                                                   const FGameplayTag& InCooldownTag)
{
	UListenCooldownChange* ListenCooldownChange = NewObject<UListenCooldownChange>();
	ListenCooldownChange->AbilitySystemComponent = AbilitySystemComponent;
	ListenCooldownChange->CooldownTag = InCooldownTag;

	if (!IsValid(AbilitySystemComponent) || !InCooldownTag.IsValid())
	{
		ListenCooldownChange->EndTask();
		return nullptr;
	}

	// To know when a cooldown has ended (Cooldown tag has been removed)
	AbilitySystemComponent->RegisterGameplayTagEvent(InCooldownTag, EGameplayTagEventType::NewOrRemoved)
		.AddUObject(ListenCooldownChange, &UListenCooldownChange::CooldownTagChanged);

	// To know when a cooldown effect has been applied
	AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(ListenCooldownChange, &UListenCooldownChange::OnActiveEffectAdded);

	return ListenCooldownChange;
}

void UListenCooldownChange::EndTask()
{
	if (!IsValid(AbilitySystemComponent)) return;
	AbilitySystemComponent->RegisterGameplayTagEvent(CooldownTag, EGameplayTagEventType::NewOrRemoved).RemoveAll(this);

	SetReadyToDestroy();
	MarkAsGarbage();
}

void UListenCooldownChange::CooldownTagChanged(const FGameplayTag NewCooldownTag, int32 NewCount)
{
	if (NewCount == 0)
	{
		CooldownEnd.Broadcast(0.f);
	}
}

void UListenCooldownChange::OnActiveEffectAdded(UAbilitySystemComponent* TargetSystemComponent,
	const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer AssetTags;
	SpecApplied.GetAllAssetTags(AssetTags);

	FGameplayTagContainer Grantedtags;
	SpecApplied.GetAllGrantedTags(Grantedtags);

	if (AssetTags.HasTagExact(CooldownTag) || Grantedtags.HasTagExact(CooldownTag))
	{
		FGameplayEffectQuery Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTag.GetSingleTagContainer());
		TArray<float> TimesRemaining = AbilitySystemComponent->GetActiveEffectsTimeRemaining(Query);

		if (TimesRemaining.Num() > 0)
		{
			float TimeRemaining = TimesRemaining[0];

			for (int32 i = 1; i < TimesRemaining.Num(); i++)
			{
				if (TimesRemaining[i] > TimeRemaining)
				{
					TimeRemaining = TimesRemaining[i];
				}
			}
			
			CooldownStart.Broadcast(TimeRemaining);
		}
	}
}
