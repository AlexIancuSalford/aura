// Copyright Alexandru Iancu


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP) const
{
	int32 Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		// LevelUpInfo is a 1 index array so the index matches the level
		// LevelUpInfo[1] = Level 1 Information
		// LevelUpInfo[2] = Level 2 Information
		// LevelUpInfo[0] is meaningless, just a placeholder
		if (LevelUpInfo.Num() - 1 <= Level) { return Level; }

		if (XP >= LevelUpInfo[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
	}
	
	return Level;
}
