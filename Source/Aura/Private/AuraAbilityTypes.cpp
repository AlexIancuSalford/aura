﻿#include "AuraAbilityTypes.h"

UScriptStruct* FAuraGameplayEffectContext::GetScriptStruct() const
{
	return FGameplayEffectContext::StaticStruct();
}

bool FAuraGameplayEffectContext::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	return FGameplayEffectContext::NetSerialize(Ar, Map, bOutSuccess);
}
