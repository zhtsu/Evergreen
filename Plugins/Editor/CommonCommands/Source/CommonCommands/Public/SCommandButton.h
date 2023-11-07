// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Framework/SlateDelegates.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Input/SButton.h"

/**
 * 
 */
class COMMONCOMMANDS_API SCommandButton : public SButton
{
public:
	SLATE_BEGIN_ARGS(SCommandButton)
	{}
	
	SLATE_ATTRIBUTE(FText, CommandText)

	/** The clicked handler. */
	SLATE_EVENT(FOnClicked, OnClicked)
	
	SLATE_END_ARGS()

	SCommandButton() {}

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
