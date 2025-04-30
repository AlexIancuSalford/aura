// Copyright Alexandru Iancu

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraOverlayWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API USpellMenuWidgetController : public UAuraOverlayWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
};
