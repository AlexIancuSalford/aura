// Copywright AI


#include "UI/WidgetController/AuraOverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UAuraOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	FOnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	FOnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	FOnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	FOnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UAuraOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UAuraOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UAuraOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UAuraOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UAuraOverlayWidgetController::MaxManaChanged);

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Black, Msg);
			}
		}
	);
}

void UAuraOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	FOnHealthChanged.Broadcast(Data.NewValue);
}

void UAuraOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	FOnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UAuraOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	FOnManaChanged.Broadcast(Data.NewValue);
}

void UAuraOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	FOnMaxManaChanged.Broadcast(Data.NewValue);
}
