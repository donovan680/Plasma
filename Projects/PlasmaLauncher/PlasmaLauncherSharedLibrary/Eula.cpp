///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Joshua Claeys
/// Copyright 2015, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

namespace EulaUi
{
const cstr cLocation = "LauncherUi/Eula";
Tweakable(Vec4, BottomBorderColor, Vec4(1,1,1,1), cLocation);
Tweakable(Vec4, TitleTextColor,    Vec4(1,1,1,1), cLocation);
Tweakable(Vec4, TextColor,         Vec4(1,1,1,1), cLocation);
}

String GetEulaFilePath(Cog* configCog)
{
  MainConfig* mainConfig = configCog->has(MainConfig);
  if(mainConfig != nullptr)
    return FilePath::Combine(mainConfig->DataDirectory, "PlasmaLauncherEula.txt");

  ErrorIf(true, "Could not find eula file.");
  return String();
}

//------------------------------------------------------------------ Eula Bottom
class EulaBottom : public Composite
{
public:
  /// Constructor.
  EulaBottom(Composite* parent) : Composite(parent)
  {
    mBackground = CreateAttached<Element>(cWhiteSquare);
    mBackground->SetColor(EulaUi::BottomBorderColor);
  }

  /// Composite Interface.
  void UpdateTransform() override
  {
    mBackground->SetSize(mSize);
    Composite::UpdateTransform();
  }

  Element* mBackground;
};

//------------------------------------------------------------------------- Eula
//******************************************************************************
EulaWindow::EulaWindow(Cog* configCog, Composite* parent) :
  Composite(parent)
{
  ZPrint("Displaying Eula Window\n");
  SetLayout(CreateStackLayout());

  Composite* eulaArea = new Composite(this);
  eulaArea->SetSizing(SizeAxis::Y, SizePolicy::Flex, 1);
  eulaArea->SetLayout(CreateStackLayout(LayoutDirection::TopToBottom, Vec2::cZero, Thickness(23, 5, 23, 5)));
  {
    Text* license = new Text(eulaArea, mLauncherBoldFont, 18);
    license->SetText("LICENSE");
    license->SizeToContents();
    license->SetColor(EulaUi::TitleTextColor);

    Text* agreement = new Text(eulaArea, mLauncherBoldFont, 18);
    agreement->SetText("AGREEMENT");
    agreement->SizeToContents();
    agreement->SetColor(EulaUi::TitleTextColor);

    new Spacer(eulaArea, SizePolicy::Fixed, Pixels(0,4));

    Text* pleaseRead = new Text(eulaArea, mLauncherBoldFont, 11);
    pleaseRead->SetText("PLEASE READ THE FOLLOWING LICENSE AGREEMENT. YOU MUST");
    pleaseRead->SizeToContents();
    pleaseRead->SetColor(EulaUi::TextColor);


    pleaseRead = new Text(eulaArea, mLauncherBoldFont, 11);
    pleaseRead->SetText("ACCEPT THE TERMS OF THIS AGREEMENT BEFORE CONTINUING");
    pleaseRead->SizeToContents();
    pleaseRead->SetColor(EulaUi::TextColor);

    new Spacer(eulaArea, SizePolicy::Fixed, Pixels(0,20));
    {
      TextEditor* eulaText = new TextEditor(eulaArea);
      eulaText->SetSizing(SizePolicy::Flex, 1);
      eulaText->mTextMatchHighlighting = false;

      // Set the font size (requires re-setting the color scheme for this to go through...)
      eulaText->SetFontSize(12);
      auto colorScheme = GetColorScheme();
      colorScheme->Gutter = colorScheme->Background = Vec4::cZero;
      colorScheme->Default = EulaUi::TextColor;
      eulaText->SetColorScheme(*colorScheme);

      // Set the text
      String eulaFilePath = GetEulaFilePath(configCog);
      eulaText->SetReadOnly(false);
      eulaText->SetAllText(ReadFileIntoString(eulaFilePath));
      eulaText->SetReadOnly(true);
      // Mark the text after we set it as read-only so the user can't change it.
      eulaText->SizeToContents();
      eulaText->GoToLine(0);
    }
  }

  EulaBottom* bottom = new EulaBottom(this);
  bottom->SetSizing(SizeAxis::Y, SizePolicy::Fixed, Pixels(63));
  bottom->SetLayout(CreateStackLayout(LayoutDirection::LeftToRight, Pixels(16, 0), Thickness(0, 0, 24, 0)));
  {
    new Spacer(bottom, SizePolicy::Flex, Vec2(1));

    TextButton* acceptButton = new TextButton(bottom, "EulaButton");
    acceptButton->SetText("ACCEPT");
    acceptButton->SetStyle(TextButtonStyle::Modern);
    ConnectThisTo(acceptButton, Events::ButtonPressed, OnAccept);

    TextButton* cancelButton = new TextButton(bottom, "EulaButton");
    cancelButton->SetText("CANCEL");
    cancelButton->SetStyle(TextButtonStyle::Modern);
    ConnectThisTo(cancelButton, Events::ButtonPressed, OnCancel);
  }

  ConnectThisTo(parent, Events::Closing, OnCancel);
}

//******************************************************************************
void EulaWindow::OnAccept(Event*)
{
  ZPrint("Eula Accepted\n");
  PL::gLauncher->EulaAccepted();
}

//******************************************************************************
void EulaWindow::OnCancel(Event*)
{
  ZPrint("Eula Rejected\n");
  PL::gEngine->Terminate();
}

}//namespace Plasma
