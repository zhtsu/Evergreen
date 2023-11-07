// Fill out your copyright notice in the Description page of Project Settings.


#include "SCommandButton.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SCommandButton::Construct(const FArguments& InArgs)
{
	SButton::Construct(SButton::FArguments()
		.Text(InArgs._CommandText)
	);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
