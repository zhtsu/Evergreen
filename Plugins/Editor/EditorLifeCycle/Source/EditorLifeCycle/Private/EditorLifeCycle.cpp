// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorLifeCycle.h"

#include "StringTableHelper.h"

#define LOCTEXT_NAMESPACE "FEditorLifeCycleModule"

void FEditorLifeCycleModule::StartupModule()
{
	UStringTableHelper::ImportAllStringTableFromCSV();
}

void FEditorLifeCycleModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorLifeCycleModule, EditorLifeCycle)