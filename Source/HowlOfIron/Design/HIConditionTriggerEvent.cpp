// Fill out your copyright notice in the Description page of Project Settings.


#include "Design/HIConditionTriggerEvent.h"
#include "Game/Conditions/HITriggerCondition.h"

void UHIConditionTriggerEvent::HISetListenerCondition(UHITriggerCondition* newListenerCondition)
{
	listenerCondition = newListenerCondition;
}

void UHIConditionTriggerEvent::CodeExecuteTriggerEvent()
{
	listenerCondition->triggerActivated = true;
}
