// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Conditions/HIInCombatCondition.h"

bool UHIInCombatCondition::HICheckCondition()
{
	return UHIGameData::HIInCombat();
}