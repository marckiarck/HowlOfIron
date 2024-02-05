// @AUTHOR: Germán López

#pragma once

UENUM(BlueprintType)
enum ECustomActorStyle
{
	None   = 0  UMETA(DisplayName = "Invalid"),
	Row    = 1  UMETA(DisplayName = "Row"),
	Matrix = 2  UMETA(DisplayName = "Matrix"),
	Circle = 3  UMETA(DisplayName = "Circle")
};
