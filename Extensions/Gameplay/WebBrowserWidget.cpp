///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Trevor Sundberg
/// Copyright 2016, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"
#include "Widget/RootWidget.hpp"
#include "Widget/Window.hpp"
#include "Engine/Tweakables.hpp"
#include "Engine/Time.hpp"

namespace Plasma
{

namespace WebBrowserUi
{
  const cstr cLocation = "EditorUi/Controls/WebBrowser";

  Tweakable(Vec4, ButtonEnabledColor, Vec4(1, 1, 1, 1), cLocation);
  Tweakable(Vec4, ButtonDisabledColor, Vec4(0.5f, 0.5f, 0.5f, 0.5f), cLocation);
  Tweakable(float, ButtonWidth, 40.0f, cLocation);
  Tweakable(float, ButtonSpacing, 2.0f, cLocation);
  Tweakable(float, ElementSpacing, 1.0f, cLocation);
}

//------------------------------------------------------------------ WebBrowserWidget
LightningDefineType(WebBrowserWidget, builder, type)
{
}

WebBrowserWidget::WebBrowserWidget(Composite* composite, const WebBrowserSetup& setup) :
  Composite(composite),
  mIsPopup(false)
{
  mBrowser = WebBrowser::Create(setup);
  SetLayout(new StackLayout(LayoutDirection::TopToBottom, Vec2(WebBrowserUi::ElementSpacing)));

  mAddressBar = new Composite(this);
  mAddressBar->SetDockMode(DockMode::DockTop);
  mAddressBar->SetLayout(new StackLayout(LayoutDirection::LeftToRight, Vec2(WebBrowserUi::ButtonSpacing)));

  mBack = new IconButton(mAddressBar);
  mBack->SetSizing(SizeAxis::X, SizePolicy::Fixed, WebBrowserUi::ButtonWidth);
  mBack->SetIcon("PreviousObject");
  mBack->SetToolTip("Go back to the previous page");
  ConnectThisTo(mBack, Events::ButtonPressed, OnBackPressed);

  mForward = new IconButton(mAddressBar);
  mForward->SetSizing(SizeAxis::X, SizePolicy::Fixed, WebBrowserUi::ButtonWidth);
  mForward->SetIcon("NextObject");
  mForward->SetToolTip("Go forward to the next page");
  ConnectThisTo(mForward, Events::ButtonPressed, OnForwardPressed);

  mReload = new IconButton(mAddressBar);
  mReload->SetSizing(SizeAxis::X, SizePolicy::Fixed, WebBrowserUi::ButtonWidth);
  mReload->SetIcon("ReloadContent");
  mReload->SetToolTip("Reload the page");
  ConnectThisTo(mReload, Events::ButtonPressed, OnReloadPressed);

  mAddressText = new TextBox(mAddressBar);
  mAddressText->SetEditable(true);
  mAddressText->SetSizing(SizeAxis::X, SizePolicy::Flex, 1.0f);

  WebBrowser* browser = mBrowser;

  mBrowserView = new TextureView(this);
  mBrowserView->SetSizing(SizeAxis::Y, SizePolicy::Flex, 1.0f);
  mBrowserView->SetDockMode(DockMode::DockFill);
  mBrowserView->SetTexture(browser->GetTexture());

  // If we ever gain focus on any other widget, tell the browser it lost focus.
  ConnectThisTo(GetRootWidget(), Events::FocusGainedHierarchy, OnRootFocusGainedHierarchy);

  mStatusBar = new TextBox(this);
  mStatusBar->SetEditable(false);
  mStatusBar->SetDockMode(DockMode::DockBottom);
  mStatusBar->SetText("Ready");

  mBrowserView->SetTakeFocusMode(FocusMode::Hard);
  SetSize(Math::ToVec2(browser->GetSize()));

  ConnectThisTo(PL::gEngine, Events::EngineUpdate, OnEngineUpdate);

  ConnectThisTo(mAddressText, Events::TextSubmit, OnAddressTextSubmit);

  ConnectThisTo(browser, Events::WebBrowserPopup, OnWebBrowserPopup);
  ConnectThisTo(browser, Events::WebBrowserPointQuery, OnWebBrowserPointQuery);
  ConnectThisTo(browser, Events::WebBrowserUrlChanged, OnWebBrowserUrlChanged);
  ConnectThisTo(browser, Events::WebBrowserCursorChanged, OnWebBrowserCursorChanged);
  ConnectThisTo(browser, Events::WebBrowserTitleChanged, OnWebBrowserTitleChanged);
  ConnectThisTo(browser, Events::WebBrowserStatusChanged, OnWebBrowserStatusChanged);
  ConnectThisTo(browser, Events::WebBrowserConsoleMessage, OnWebBrowserConsoleMessage);
  ConnectThisTo(browser, Events::WebBrowserDownloadStarted, OnWebBrowserDownloadStarted);
  
  ConnectThisTo(mBrowserView, Events::FocusGained, OnBrowserViewFocusGained);
  ConnectThisTo(mBrowserView, Events::FocusLost, OnBrowserViewFocusLost);

  ConnectThisTo(mBrowserView, Events::KeyDown, OnKeyDown);
  ConnectThisTo(mBrowserView, Events::KeyUp, OnKeyUp);
  ConnectThisTo(mBrowserView, Events::TextTyped, OnTextTyped);

  ConnectThisTo(mBrowserView, Events::MouseMove, OnMouseMove);
  ConnectThisTo(mBrowserView, Events::MouseDown, OnMouseDown);
  ConnectThisTo(mBrowserView, Events::MouseUp, OnMouseUp);
  ConnectThisTo(mBrowserView, Events::DoubleClick, OnMouseDoubleClick);

  ConnectThisTo(mBrowserView, Events::MouseScroll, OnMouseScroll);
}

void WebBrowserWidget::UpdateTransform()
{
  Composite::UpdateTransform();

  bool isVisible = GetActive() && GetVisible();

  if (isVisible)
  {
    IntVec2 newSize = Math::ToIntVec2(mBrowserView->GetSize());
    IntVec2 clientPosition = Math::ToIntVec2(mBrowserView->GetScreenPosition());
    mBrowser->SetSize(newSize);
    mBrowser->SetClientPosition(clientPosition);
    mBrowser->SetZIndex(GetZIndex());
  }
  
  if (isVisible != mBrowser->GetVisible())
    mBrowser->SetVisible(isVisible);
}

void WebBrowserWidget::OnEngineUpdate(UpdateEvent* event)
{
  if (!GetActive())
    return;
  WebBrowser* browser = mBrowser;

  if (browser->GetCanGoBackward())
    mBack->SetColor(WebBrowserUi::ButtonEnabledColor);
  else
    mBack->SetColor(WebBrowserUi::ButtonDisabledColor);

  if (browser->GetCanGoForward())
    mForward->SetColor(WebBrowserUi::ButtonEnabledColor);
  else
    mForward->SetColor(WebBrowserUi::ButtonDisabledColor);
}

BrowserModifiers::Enum GetModifiers(KeyboardEvent* event)
{
  BrowserModifiers::Enum value = (BrowserModifiers::Enum)0;
  if (event->CtrlPressed)
    value = (BrowserModifiers::Enum)(value | BrowserModifiers::Control);
  if (event->AltPressed)
    value = (BrowserModifiers::Enum)(value | BrowserModifiers::Alt);
  if (event->ShiftPressed)
    value = (BrowserModifiers::Enum)(value | BrowserModifiers::Shift);
  return value;
}

BrowserModifiers::Enum GetModifiers(MouseEvent* event)
{
  BrowserModifiers::Enum value = (BrowserModifiers::Enum)0;
  if (event->CtrlPressed)
    value = (BrowserModifiers::Enum)(value | BrowserModifiers::Control);
  if (event->AltPressed)
    value = (BrowserModifiers::Enum)(value | BrowserModifiers::Alt);
  if (event->ShiftPressed)
    value = (BrowserModifiers::Enum)(value | BrowserModifiers::Shift);
  if (event->IsButtonDown(MouseButtons::Left))
    value = (BrowserModifiers::Enum)(value | BrowserModifiers::LeftMouse);
  if (event->IsButtonDown(MouseButtons::Middle))
    value = (BrowserModifiers::Enum)(value | BrowserModifiers::MiddleMouse);
  if (event->IsButtonDown(MouseButtons::Right))
    value = (BrowserModifiers::Enum)(value | BrowserModifiers::RightMouse);
  return value;
}

void WebBrowserWidget::OnWebBrowserPopup(WebBrowserPopupCreateEvent* event)
{
  if (!mManager)
    return;

  WebBrowserSetup setup;
  setup.mUrl = event->mUrl;
  setup.mSize = mBrowser->GetSize();

  WebBrowserWidget* browser = new WebBrowserWidget(this, setup);
  browser->mIsPopup = true;
  browser->SetName(event->mName);

  browser->SetHideOnClose(false);
  mManager->AddManagedWidget(browser, DockArea::Center, true);
}

void WebBrowserWidget::OnWebBrowserPointQuery(WebBrowserPointQueryEvent* event)
{
  Vec2 browserClient = Math::ToVec2(event->mBrowserPixelPosition);
  Vec2 plasmaClient = mBrowserView->ToScreen(browserClient);
  IntVec2 desktopScreen = GetRootWidget()->GetOsWindow()->ClientToMonitor(Math::ToIntVec2(plasmaClient));
  event->mMonitorPixelPosition = desktopScreen;
}

void WebBrowserWidget::OnBackPressed(ObjectEvent* event)
{
  mBrowser->GoBackward();
}

void WebBrowserWidget::OnForwardPressed(ObjectEvent* event)
{
  mBrowser->GoForward();
}

void WebBrowserWidget::OnReloadPressed(ObjectEvent* event)
{
  bool useCache = !(Keyboard::Instance->KeyIsDown(Keys::Shift) || Keyboard::Instance->KeyIsDown(Keys::Control));
  mBrowser->Reload(useCache);
}

void WebBrowserWidget::OnAddressTextSubmit(ObjectEvent* event)
{
  mBrowser->SetUrl(mAddressText->GetText());
}

void WebBrowserWidget::OnRootFocusGainedHierarchy(FocusEvent* event)
{
  mBrowser->SetFocus(false);
}

void WebBrowserWidget::OnWebBrowserUrlChanged(WebBrowserUrlEvent* event)
{
  if (!mAddressText->HasFocus())
    mAddressText->SetText(event->mUrl);
}

void WebBrowserWidget::OnWebBrowserCursorChanged(WebBrowserCursorEvent* event)
{
  PL::gMouse->SetCursor(event->mCursor);
}

void WebBrowserWidget::OnWebBrowserTitleChanged(WebBrowserTextEvent* event)
{
  SetName(event->mText);

  Widget* parent = this;
  while (parent != nullptr)
  {
    Window* window = Type::DynamicCast<Window*>(parent);
    if (window)
    {
      window->SetName(event->mText);
      window->MarkAsNeedsUpdate();
    }
    parent = parent->GetParent();
  }
}

void WebBrowserWidget::OnWebBrowserStatusChanged(WebBrowserTextEvent* event)
{
  mStatusBar->SetText(event->mText);
}

void WebBrowserWidget::OnWebBrowserConsoleMessage(WebBrowserConsoleEvent* event)
{
  StringBuilder builder;
  builder << "  File \"";
  builder << event->mSource;
  builder << "\", line ";
  builder << event->mLine;
  builder << "\n    ";
  builder << event->mMessage;
  builder << "\n";

  String fullMessage = builder.ToString();

  ZPrint("%s", fullMessage.c_str());
}

void OnPackageDownloadCallback(BackgroundTask* task, Job* job)
{
  DownloadTaskJob* downloadJob = (DownloadTaskJob*)job;
  String location = FilePath::Combine(GetTemporaryDirectory(), downloadJob->mName);
  WriteStringRangeToFile(location, downloadJob->GetData());

  ContentImporter::OpenImportWindow(location);
}

void OnGenericDownloadCallback(BackgroundTask* task, Job* job)
{
  DownloadTaskJob* downloadJob = (DownloadTaskJob*)job;
  String location = FilePath::Combine(GetTemporaryDirectory(), downloadJob->mName);
  WriteStringRangeToFile(location, downloadJob->GetData());
  Os::SystemOpenFile(location.c_str());
}

void WebBrowserWidget::OnWebBrowserDownloadStarted(WebBrowserDownloadEvent* event)
{
  BackgroundTask* task = DownloadTaskJob::DownloadToBuffer(event->mUrl, event->mSuggestedFileName);

  String extension = FilePath::GetExtension(event->mSuggestedFileName);

  static const String PlasmaPack("plasmapack");

  if (extension == PlasmaPack)
    task->mCallback = &OnPackageDownloadCallback;
  else
    task->mCallback = &OnGenericDownloadCallback;

  // Since we started our own download, cancel the browser download
  event->mCancel = true;

  // If this is a popup whose sole purpose was to start a download, then close the tab (like other browsers)
  if (mIsPopup)
  {
    String currentUrl = mBrowser->GetUrl();
    if (event->mUrl == currentUrl || event->mOriginalUrl == currentUrl)
      CloseTabContaining(this);
  }
}

void WebBrowserWidget::OnBrowserViewFocusGained(FocusEvent* event)
{
  mBrowser->SetFocus(true);
}

void WebBrowserWidget::OnBrowserViewFocusLost(FocusEvent* event)
{
  mBrowser->SetFocus(false);
}

void WebBrowserWidget::OnKeyDown(KeyboardEvent* event)
{
  mBrowser->SimulateKey(event->OsKey, true, GetModifiers(event));
  event->Handled = true;
}

void WebBrowserWidget::OnKeyUp(KeyboardEvent* event)
{
  if (event->Key == Keys::F5)
  {
    bool useCache = !(event->ShiftPressed || event->CtrlPressed);
    mBrowser->Reload(useCache);
  }
  else
  {
    mBrowser->SimulateKey(event->OsKey, false, GetModifiers(event));
  }
  event->Handled = true;
}

void WebBrowserWidget::OnTextTyped(KeyboardTextEvent* event)
{
  mBrowser->SimulateTextTyped(event->mRune.value, (BrowserModifiers::Enum)0);
  event->mHandled = true;
}

void WebBrowserWidget::OnMouseMove(MouseEvent* event)
{
  IntVec2 localPosition = Math::ToIntVec2(mBrowserView->ToLocal(event->Position));
  mBrowser->SimulateMouseMove(localPosition, GetModifiers(event));
  event->Handled = true;
}

void WebBrowserWidget::OnMouseDown(MouseEvent* event)
{
  IntVec2 localPosition = Math::ToIntVec2(mBrowserView->ToLocal(event->Position));
  mBrowser->SimulateMouseClick(localPosition, event->Button, true, GetModifiers(event));
  event->Handled = true;
}

void WebBrowserWidget::OnMouseUp(MouseEvent* event)
{
  IntVec2 localPosition = Math::ToIntVec2(mBrowserView->ToLocal(event->Position));
  mBrowser->SimulateMouseClick(localPosition, event->Button, false, GetModifiers(event));
  event->Handled = true;
}

void WebBrowserWidget::OnMouseDoubleClick(MouseEvent* event)
{
  IntVec2 localPosition = Math::ToIntVec2(mBrowserView->ToLocal(event->Position));
  mBrowser->SimulateMouseDoubleClick(localPosition, event->Button, GetModifiers(event));
  event->Handled = true;
}

void WebBrowserWidget::OnMouseScroll(MouseEvent* event)
{
  IntVec2 localPosition = Math::ToIntVec2(mBrowserView->ToLocal(event->Position));
  mBrowser->SimulateMouseScroll(localPosition, event->Scroll, GetModifiers(event));
  event->Handled = true;
}

} // namespace Plasma
