// Copyright Alexandru Iancu

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NiagaraComponent.h"
#include "PassiveNiagaraComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UPassiveNiagaraComponent : public UNiagaraComponent
{
	GENERATED_BODY()
public:
	UPassiveNiagaraComponent();
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag PassiveSpellTag;
	
	virtual void BeginPlay() override;
	void OnPassiveActivate(const FGameplayTag& AbilityTag, bool bActivate);
};
