// Copyright Epic Games, Inc. All Rights Reserved.

#include "GeneralUtility.h"

#define LOCTEXT_NAMESPACE "FGeneralUtility"

void FGeneralUtility::StartupModule()
{
	
}

void FGeneralUtility::ShutdownModule()
{
	
}

void StringTableHelper::ImportStringTableFromCSV()
{
	// IDesktopPlatform* const DesktopPlatform = FDesktopPlatformModule::Get();
	//
	// if (DesktopPlatform)
	// {
	// 	const FString DefaultPath = FEditorDirectories::Get().GetLastDirectory(ELastDirectory::GENERIC_IMPORT);
	//
	// 	TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().FindWidgetWindow(StringTableEntriesListView.ToSharedRef());
	// 	const void* const ParentWindowHandle = (ParentWindow.IsValid() && ParentWindow->GetNativeWindow().IsValid())
	// 		? ParentWindow->GetNativeWindow()->GetOSWindowHandle()
	// 		: nullptr;
	//
	// 	TArray<FString> OutFiles;
	// 	if (DesktopPlatform->OpenFileDialog(
	// 		ParentWindowHandle,
	// 		LOCTEXT("ImportStringTableTitle", "Choose a string table CSV file...").ToString(),
	// 		DefaultPath,
	// 		TEXT(""),
	// 		TEXT("String Table CSV (*.csv)|*.csv"),
	// 		EFileDialogFlags::None,
	// 		OutFiles
	// 		))
	// 	{
	// 		UStringTable* StringTable = Cast<UStringTable>(GetEditingObject());
	// 		if (StringTable)
	// 		{
	// 			const FScopedTransaction Transaction(LOCTEXT("ImportStringTableEntries", "Import String Table Entries"));
	// 			StringTable->Modify();
	// 			StringTable->GetMutableStringTable()->ImportStrings(OutFiles[0]);
	// 			HandlePostChange();
	// 		}
	// 	}
	// }
	//
	// return FReply::Handled();
}

void StringTableHelper::ExportStringTableToCSV()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGeneralUtility, GeneralUtility)