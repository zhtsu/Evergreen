// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Framework/SlateDelegates.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class COMMONCOMMANDS_API SCommandButtonWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCommandButtonWidget)
	{}
	
	SLATE_ATTRIBUTE(FText, CommandText)
	
	SLATE_END_ARGS()

	FReply ExecCommand();
	
	void Construct(const FArguments& InArgs);

private:
	FText Command;
	TSharedPtr<SBorder> ColorStrip;
};
