//---------------------------------------------------------------------------

#include "Presets.h"

#include <tchar.h>
#include <XMLDoc.hpp>
#include <XMLIntf.hpp>
#include <ComObj.hpp>
#include <stdio.h>

//---------------------------------------------------------------------------

static const AnsiString CSubFolder = "presets\\";

//---------------------------------------------------------------------------

TPresets::TPresets(const AnsiString Directory) :
FDirectory(IncludeTrailingBackslash(Directory))
{
	CoInitializeEx(NULL, 0);

	// Make sure presets directory exists.

	ForceDirectories(FDirectory + CSubFolder);
}

//---------------------------------------------------------------------------

void TPresets::AvailablePresets(std::vector <AnsiString>& List)
{
	List.clear();

	List.push_back("testing");
	List.push_back("one");
	List.push_back("two");
}

//---------------------------------------------------------------------------

void TPresets::Load(const AnsiString Filename)
{

	// Get rid of old values.

	FKeyValues.clear();

}

//---------------------------------------------------------------------------

void TPresets::Save(const AnsiString Filename)
{
	_di_IXMLDocument document = interface_cast<Xmlintf::IXMLDocument> (new TXMLDocument(0));

	document->Active = true;

	document->SetEncoding("utf-8");
	document->NodeIndentStr = "  ";
	document->Options = document->Options + (TXMLDocOptions() << doNodeAutoIndent);

	// Define document content.

	document->DocumentElement = document->CreateNode("R128preset", ntElement, "");
	document->DocumentElement->Attributes["License"] = "CC Attribution-NonCommercial 4.0 International";
	document->DocumentElement->Attributes["Programming"] = "Hens Zimmerman Audio";

	for(std::map<AnsiString, AnsiString>::iterator idx = FKeyValues.begin();
		idx != FKeyValues.end(); ++idx)
	{
		AnsiString Key = idx->first;
		AnsiString Value = idx->second;

		_di_IXMLNode nodeElement = document->DocumentElement->AddChild(Key, -1);
		nodeElement->Text = Value;
	}

	document->SaveToFile(FDirectory + CSubFolder + Filename + ".xml");

}

//---------------------------------------------------------------------------

AnsiString TPresets::Get(const AnsiString Key, const AnsiString Def)
{
	return Def;
}

//---------------------------------------------------------------------------

int TPresets::Get(const AnsiString Key, const int Def)
{
	return Def;
}

//---------------------------------------------------------------------------

void TPresets::Put(const AnsiString Key, const AnsiString Value)
{
	FKeyValues[Key] = Value;
}

//---------------------------------------------------------------------------

void TPresets::Put(const AnsiString Key, const int Value)
{
	FKeyValues[Key] = IntToStr(Value);
}

//---------------------------------------------------------------------------


