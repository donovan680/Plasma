///////////////////////////////////////////////////////////////////////////////
///
/// Authors: Trevor Sundberg
/// Copyright 2016, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

namespace Events
{
  DefineEvent(WebBrowserPopup);
  DefineEvent(WebBrowserPointQuery);
  DefineEvent(WebBrowserConsoleMessage);
  DefineEvent(WebBrowserStatusChanged);
  DefineEvent(WebBrowserTitleChanged);
  DefineEvent(WebBrowserUrlChanged);
  DefineEvent(WebBrowserCursorChanged);
  DefineEvent(WebBrowserDownloadStarted);
  DefineEvent(WebBrowserDownloadUpdated);
}

//------------------------------------------------------------------ WebBrowserEvent
LightningDefineType(WebBrowserEvent, builder, type)
{
  LightningBindGetterProperty(WebBrowser);
}

WebBrowser* WebBrowserEvent::GetWebBrowser()
{
  return mWebBrowser;
}

//------------------------------------------------------------------ WebBrowserPopupCreateEvent
LightningDefineType(WebBrowserPopupCreateEvent, builder, type)
{
  LightningBindFieldProperty(mName);
  LightningBindFieldProperty(mUrl);
}

//------------------------------------------------------------------ WebBrowserCursorEvent
LightningDefineType(WebBrowserCursorEvent, builder, type)
{
  LightningBindFieldProperty(mCursor);
}

WebBrowserCursorEvent::WebBrowserCursorEvent()
{
  mCursor = Cursor::Arrow;
}

//------------------------------------------------------------------ WebBrowserPointQueryEvent
LightningDefineType(WebBrowserPointQueryEvent, builder, type)
{
  LightningBindFieldProperty(mBrowserPixelPosition);
  LightningBindFieldProperty(mMonitorPixelPosition);
}

WebBrowserPointQueryEvent::WebBrowserPointQueryEvent()
{
  mBrowserPixelPosition = IntVec2::cZero;
  mMonitorPixelPosition = IntVec2::cZero;
}

//------------------------------------------------------------------ WebBrowserConsoleEvent
LightningDefineType(WebBrowserConsoleEvent, builder, type)
{
  LightningBindFieldProperty(mMessage);
  LightningBindFieldProperty(mSource);
  LightningBindFieldProperty(mLine);
}

WebBrowserConsoleEvent::WebBrowserConsoleEvent()
{
  mLine = 0;
  mHandled = false;
}

//------------------------------------------------------------------ WebBrowserTextEvent
LightningDefineType(WebBrowserTextEvent, builder, type)
{
  LightningBindFieldProperty(mText);
}

//------------------------------------------------------------------ WebBrowserUrlEvent
LightningDefineType(WebBrowserUrlEvent, builder, type)
{
  LightningBindFieldProperty(mUrl);
  LightningBindFieldProperty(mHandled);
}

WebBrowserUrlEvent::WebBrowserUrlEvent()
{
  mHandled = false;
}

//------------------------------------------------------------------ WebBrowserDownloadEvent
LightningDefineType(WebBrowserDownloadEvent, builder, type)
{
  LightningBindFieldProperty(mFilePath);
  LightningBindFieldProperty(mCancel);
  LightningBindFieldProperty(mIsInProgress);
  LightningBindFieldProperty(mIsComplete);
  LightningBindFieldProperty(mCurrentSpeed);
  LightningBindFieldProperty(mReceivedBytes);
  LightningBindFieldProperty(mTotalBytes);
  LightningBindFieldProperty(mId);
  LightningBindFieldProperty(mUrl);
  LightningBindFieldProperty(mOriginalUrl);
  LightningBindFieldProperty(mSuggestedFileName);
  LightningBindFieldProperty(mContentDisposition);
  LightningBindFieldProperty(mMimeType);
}

WebBrowserDownloadEvent::WebBrowserDownloadEvent()
{
  mIsInProgress = false;
  mIsComplete = false;
  mCurrentSpeed = 0;
  mReceivedBytes = 0;
  mTotalBytes = 0;
  mId = 0;
  mCancel = false;
}

//------------------------------------------------------------------ WebBrowserManager
LightningDefineType(WebBrowserManager, builder, type)
{
}

WebBrowserManager::WebBrowserManager() :
  mInitializedPlatform(false)
{
  ConnectThisTo(PL::gEngine, Events::OsShellUpdate, OnOsShellUpdate);
}

WebBrowserManager::~WebBrowserManager()
{
  if (mInitializedPlatform)
    Browser::PlatformDestroy();
}

void WebBrowserManager::OnOsShellUpdate(Event* event)
{
  if (mInitializedPlatform)
    Browser::PlatformUpdate();
}

void WebBrowserManager::EnsurePlatformInitailized()
{
  if (mInitializedPlatform)
    return;

  mInitializedPlatform = true;
  Browser::PlatformCreate();
}

//------------------------------------------------------------------ WebBrowserSetup
LightningDefineType(WebBrowserSetup, builder, type)
{
  LightningBindFieldProperty(mUrl);
  LightningBindFieldProperty(mSize);
  LightningBindFieldProperty(mTransparent);
  LightningBindFieldProperty(mBackgroundColor);
  LightningBindFieldProperty(mScrollSpeed);

  LightningBindDestructor();
  LightningBindDefaultConstructor();

  type->CreatableInScript = true;
}

const String cWebBrowserDefaultUrl(Urls::cUserWebBrowserDefault);
const IntVec2 cWebBrowserDefaultSize(1024, 1024);
const bool cWebBrowserDefaultTransparent(false);
const Vec4 cWebBrowserDefaultBackgroundColor(1.0f);
const Vec2 cWebBrowserDefaultScrollSpeed(100, 100);

WebBrowserSetup::WebBrowserSetup(StringParam url, IntVec2Param size, IntVec2Param clientPosition, bool transparent, Vec4Param backgroundColor, Vec2Param scrollSpeed)
{
  mUrl = url;
  mSize = size;
  mClientPosition = clientPosition;
  mTransparent = transparent;
  mBackgroundColor = backgroundColor;
  mScrollSpeed = scrollSpeed;
}

//------------------------------------------------------------------ WebBrowser
LightningDefineType(WebBrowser, builder, type)
{
  PlasmaBindEvent(Events::WebBrowserPopup, WebBrowserPopupCreateEvent);
  PlasmaBindEvent(Events::WebBrowserPointQuery, WebBrowserPointQueryEvent);
  PlasmaBindEvent(Events::WebBrowserConsoleMessage, WebBrowserConsoleEvent);
  PlasmaBindEvent(Events::WebBrowserStatusChanged, WebBrowserTextEvent);
  PlasmaBindEvent(Events::WebBrowserTitleChanged, WebBrowserTextEvent);
  PlasmaBindEvent(Events::WebBrowserUrlChanged, WebBrowserUrlEvent);
  PlasmaBindEvent(Events::WebBrowserCursorChanged, WebBrowserCursorEvent);
  PlasmaBindEvent(Events::WebBrowserDownloadStarted, WebBrowserDownloadEvent);
  PlasmaBindEvent(Events::WebBrowserDownloadUpdated, WebBrowserDownloadEvent);

  LightningBindOverloadedMethod(Create, LightningStaticOverload(HandleOf<WebBrowser>));
  LightningBindOverloadedMethod(Create, LightningStaticOverload(HandleOf<WebBrowser>, const WebBrowserSetup&));

  LightningBindGetterSetterProperty(Size);
  LightningBindGetterSetterProperty(ClientPosition);
  LightningBindGetterSetterProperty(ZIndex);
  LightningBindGetterProperty(IsFloatingOnTop);
  LightningBindGetterProperty(IsSecurityRestricted);

  LightningBindGetterProperty(Texture);
  LightningBindGetterProperty(Status);
  LightningBindGetterProperty(Title);
  LightningBindGetterSetterProperty(ScrollSpeed);

  LightningBindGetterSetterProperty(Url);
  LightningBindGetterProperty(CanGoForward);
  LightningBindGetterProperty(CanGoBackward);

  LightningBindMethodProperty(GoForward);
  LightningBindMethodProperty(GoBackward);

  LightningBindGetterProperty(IsLoading);
  LightningBindOverloadedMethod(Reload, LightningInstanceOverload(void));
  LightningBindOverloadedMethod(Reload, LightningInstanceOverload(void, bool));

  LightningBindGetterSetterProperty(Focus);
  LightningBindGetterSetterProperty(Visible);
  LightningBindGetterSetterProperty(BackgroundColor);
  LightningBindGetterSetterProperty(Transparent);

  LightningBindMethod(ExecuteScript);
  LightningBindMethod(ExecuteScriptFromLocation);

  LightningBindMethod(SimulateKey);
  LightningBindMethod(SimulateTextTyped);
  LightningBindMethod(SimulateMouseMove);
  LightningBindMethod(SimulateMouseClick);
  LightningBindMethod(SimulateMouseDoubleClick);
  LightningBindMethod(SimulateMouseScroll);
}

WebBrowser::WebBrowser() :
  WebBrowser(WebBrowserSetup())
{
}

BrowserSetup ConvertSetupAndEnsurePlatformInitialized(const WebBrowserSetup& setup)
{
  WebBrowserManager::GetInstance()->EnsurePlatformInitailized();

  BrowserSetup browserSetup;
  browserSetup.mUrl = setup.mUrl;
  browserSetup.mSize = setup.mSize;
  browserSetup.mClientPosition = setup.mClientPosition;
  browserSetup.mTransparent = setup.mTransparent;
  browserSetup.mBackgroundColor = setup.mBackgroundColor;
  browserSetup.mScrollSpeed = setup.mScrollSpeed;
  return browserSetup;
}

WebBrowser::WebBrowser(const WebBrowserSetup& setup) :
  mBrowser(ConvertSetupAndEnsurePlatformInitialized(setup))
{
  mBrowser.mUserData = this;
  
  mBrowser.mOnPaint = &OnPaint;
  mBrowser.mOnPopup = &OnPopup;
  mBrowser.mOnPointQuery = &OnPointQuery;
  mBrowser.mOnConsoleMessage = &OnConsoleMessage;
  mBrowser.mOnStatusChanged = &OnStatusChanged;
  mBrowser.mOnTitleChanged = &OnTitleChanged;
  mBrowser.mOnUrlChanged = &OnUrlChanged;
  mBrowser.mOnCursorChanged = &OnCursorChanged;
  mBrowser.mOnDownloadStarted = &OnDownloadStarted;
  mBrowser.mOnDownloadUpdated = &OnDownloadUpdated;

  mBuffer.Resize(setup.mSize.x, setup.mSize.y, true, true, ToByteColor(mBrowser.GetBackgroundColor()));
}

HandleOf<WebBrowser> WebBrowser::Create()
{
  return new WebBrowser();
}

HandleOf<WebBrowser> WebBrowser::Create(const WebBrowserSetup& setup)
{
  return new WebBrowser(setup);
}

WebBrowser::~WebBrowser()
{
}

bool WebBrowser::GetIsFloatingOnTop()
{
  return Browser::IsFloatingOnTop();
}

bool WebBrowser::GetIsSecurityRestricted()
{
  return Browser::IsSecurityRestricted();
}

void WebBrowser::ExecuteScript(StringParam script)
{
  ExecuteScriptFromLocation(script, String(), 0);
}

void WebBrowser::SetSize(IntVec2Param size)
{
  if (size.x < 0 || size.y < 0)
  {
    DoNotifyException("WebBrowser", "Cannot set the size to a negative number");
    return;
  }

  if (size == GetSize())
    return;

  mBuffer.Resize(size.x, size.y, true, true, ToByteColor(mBrowser.GetBackgroundColor()));

  mBrowser.SetSize(size);
}

IntVec2 WebBrowser::GetSize()
{
  return IntVec2(mBuffer.Width, mBuffer.Height);
}

Math::IntVec2 WebBrowser::GetClientPosition()
{
  return mBrowser.GetClientPosition();
}

void WebBrowser::SetClientPosition(Math::IntVec2Param clientPosition)
{
  mBrowser.SetClientPosition(clientPosition);
}

int WebBrowser::GetZIndex()
{
  return mBrowser.GetZIndex();
}

void WebBrowser::SetZIndex(int zindex)
{
  mBrowser.SetZIndex(zindex);
}

Texture* WebBrowser::GetTexture()
{
  return mBuffer.Image;
}

Vec4 WebBrowser::GetBackgroundColor()
{
  return mBrowser.GetBackgroundColor();
}

void WebBrowser::SetBackgroundColor(Vec4Param color)
{
  return mBrowser.SetBackgroundColor(color);
}

bool WebBrowser::GetTransparent()
{
  return mBrowser.GetTransparent();
}

void WebBrowser::SetTransparent(bool transparent)
{
  return mBrowser.SetTransparent(transparent);
}

void WebBrowser::SetUrl(StringParam url)
{
  return mBrowser.SetUrl(url);
}

String WebBrowser::GetUrl()
{
  return mBrowser.GetUrl();
}

String WebBrowser::GetStatus()
{
  return mBrowser.GetStatus();
}
String WebBrowser::GetTitle()
{
  return mBrowser.GetTitle();
}

Vec2 WebBrowser::GetScrollSpeed()
{
  return mBrowser.GetScrollSpeed();
}

void WebBrowser::SetScrollSpeed(Vec2Param pixelsPerScroll)
{
  return mBrowser.SetScrollSpeed(pixelsPerScroll);
}

bool WebBrowser::GetCanGoForward()
{
  return mBrowser.GetCanGoForward();
}

bool WebBrowser::GetCanGoBackward()
{
  return mBrowser.GetCanGoBackward();
}

void WebBrowser::GoForward()
{
  return mBrowser.GoForward();
}

void WebBrowser::GoBackward()
{
  return mBrowser.GoBackward();
}

bool WebBrowser::GetIsLoading()
{
  return mBrowser.GetIsLoading();
}

void WebBrowser::Reload()
{
  Reload(true);
}

void WebBrowser::Reload(bool useCache)
{
  return mBrowser.Reload(useCache);
}

void WebBrowser::SetFocus(bool focus)
{
  return mBrowser.SetFocus(focus);
}

bool WebBrowser::GetFocus()
{
  return mBrowser.GetFocus();
}

void WebBrowser::SetVisible(bool visible)
{
  return mBrowser.SetVisible(visible);
}

bool WebBrowser::GetVisible()
{
  return mBrowser.GetVisible();
}

void WebBrowser::ExecuteScriptFromLocation(StringParam script, StringParam url, int line)
{
  return mBrowser.ExecuteScriptFromLocation(script, url, line);
}

void WebBrowser::SimulateKey(int key, bool down, BrowserModifiers::Enum modifiers)
{
  return mBrowser.SimulateKey(key, down, modifiers);
}

void WebBrowser::SimulateTextTyped(int character, BrowserModifiers::Enum modifiers)
{
  return mBrowser.SimulateTextTyped(character, modifiers);
}

void WebBrowser::SimulateMouseMove(IntVec2Param localPosition, BrowserModifiers::Enum modifiers)
{
  return mBrowser.SimulateMouseMove(localPosition, modifiers);
}

void WebBrowser::SimulateMouseClick(IntVec2Param localPosition, MouseButtons::Enum button, bool down, BrowserModifiers::Enum modifiers)
{
  return mBrowser.SimulateMouseClick(localPosition, button, down, modifiers);
}

void WebBrowser::SimulateMouseDoubleClick(IntVec2Param localPosition, MouseButtons::Enum button, BrowserModifiers::Enum modifiers)
{
  return mBrowser.SimulateMouseDoubleClick(localPosition, button, modifiers);
}

void WebBrowser::SimulateMouseScroll(IntVec2Param localPosition, Vec2Param delta, BrowserModifiers::Enum modifiers)
{
  return mBrowser.SimulateMouseScroll(localPosition, delta, modifiers);
}

void WebBrowser::OnPaint(BrowserColorFormat::Enum format, const byte* data, Math::IntVec2Param bufferSize, const Array<IntRect>& dirtyRectangles, Browser* browser)
{
  WebBrowser* webBrowser = (WebBrowser*)browser->mUserData;

  int srcX = bufferSize.x;
  int srcY = bufferSize.y;

  int dstX = (int)webBrowser->mBuffer.Width;
  int dstY = (int)webBrowser->mBuffer.Height;

  int minX = Math::Min(srcX, dstX);
  int minY = Math::Min(srcY, dstY);

  ErrorIf(format != BrowserColorFormat::BGRA8, "This was only coded for BGRA8 at the moment");

  ByteColor* dst = webBrowser->mBuffer.Data;
  ByteColor* src = (ByteColor*)data;

  for (size_t i = 0; i < dirtyRectangles.Size(); ++i)
  {
    const IntRect& rect = dirtyRectangles[i];

    int maxX = Math::Min(minX, rect.X + rect.SizeX);
    int maxY = Math::Min(minY, rect.Y + rect.SizeY);

    for (int y = rect.Y; y < maxY; ++y)
    {
      for (int x = rect.X; x < maxX; ++x)
      {
        ByteColor& dstColor = dst[x + y * dstX];
        ByteColor& srcColor = src[x + y * srcX];

        dstColor = srcColor;

        // Change from BGRA to RGBA
        byte* dstBytes = (byte*)&dstColor;
        Math::Swap(dstBytes[0], dstBytes[2]);
      }
    }
  }

  webBrowser->mBuffer.Upload();
}

void WebBrowser::OnPopup(StringParam name, StringParam url, Browser* browser)
{
  WebBrowser* webBrowser = (WebBrowser*)browser->mUserData;

  WebBrowserPopupCreateEvent toSend;
  toSend.mWebBrowser = webBrowser;
  toSend.mName = name;
  toSend.mUrl = url;
  webBrowser->DispatchEvent(Events::WebBrowserPopup, &toSend);
}

void WebBrowser::OnPointQuery(Math::IntVec2Param browserPixelPosition, Math::IntVec2* monitorPixelPositionOut, Browser* browser)
{
  WebBrowser* webBrowser = (WebBrowser*)browser->mUserData;

  WebBrowserPointQueryEvent toSend;
  toSend.mWebBrowser = webBrowser;
  toSend.mBrowserPixelPosition = browserPixelPosition;
  webBrowser->DispatchEvent(Events::WebBrowserPointQuery, &toSend);

  *monitorPixelPositionOut = toSend.mMonitorPixelPosition;
}

void WebBrowser::OnConsoleMessage(StringParam message, StringParam source, int line, bool* handledOut, Browser* browser)
{
  WebBrowser* webBrowser = (WebBrowser*)browser->mUserData;

  WebBrowserConsoleEvent toSend;
  toSend.mWebBrowser = webBrowser;
  toSend.mMessage = message;
  toSend.mSource = source;
  toSend.mLine = line;
  webBrowser->DispatchEvent(Events::WebBrowserConsoleMessage, &toSend);
  *handledOut = toSend.mHandled;
}

void WebBrowser::OnStatusChanged(StringParam text, Browser* browser)
{
  WebBrowser* webBrowser = (WebBrowser*)browser->mUserData;

  WebBrowserTextEvent toSend;
  toSend.mWebBrowser = webBrowser;
  toSend.mText = text;
  webBrowser->DispatchEvent(Events::WebBrowserStatusChanged, &toSend);
}

void WebBrowser::OnTitleChanged(StringParam text, Browser* browser)
{
  WebBrowser* webBrowser = (WebBrowser*)browser->mUserData;

  WebBrowserTextEvent toSend;
  toSend.mWebBrowser = webBrowser;
  toSend.mText = text;
  webBrowser->DispatchEvent(Events::WebBrowserTitleChanged, &toSend);
}

void WebBrowser::OnUrlChanged(StringParam url, bool* handledOut, Browser* browser)
{
  WebBrowser* webBrowser = (WebBrowser*)browser->mUserData;

  WebBrowserUrlEvent toSend;
  toSend.mWebBrowser = webBrowser;
  toSend.mUrl = url;
  webBrowser->DispatchEvent(Events::WebBrowserUrlChanged, &toSend);
  *handledOut = toSend.mHandled;
}

void WebBrowser::OnCursorChanged(Cursor::Enum cursor, Browser* browser)
{
  WebBrowser* webBrowser = (WebBrowser*)browser->mUserData;

  WebBrowserCursorEvent toSend;
  toSend.mWebBrowser = webBrowser;
  toSend.mCursor = cursor;
  webBrowser->DispatchEvent(Events::WebBrowserCursorChanged, &toSend);
}

void WebBrowser::OnDownloadStarted(BrowserDownload& download, bool* cancelOut, Browser* browser)
{
  WebBrowser* webBrowser = (WebBrowser*)browser->mUserData;

  WebBrowserDownloadEvent toSend;
  toSend.mWebBrowser = webBrowser;

  toSend.mFilePath = download.mFilePath;
  toSend.mIsInProgress = download.mIsInProgress;
  toSend.mIsComplete = download.mIsComplete;
  toSend.mCurrentSpeed = download.mCurrentSpeed;
  toSend.mReceivedBytes = download.mReceivedBytes;
  toSend.mTotalBytes = download.mTotalBytes;
  toSend.mId = download.mId;
  toSend.mUrl = download.mUrl;
  toSend.mOriginalUrl = download.mOriginalUrl;
  toSend.mSuggestedFileName = download.mSuggestedFileName;
  toSend.mContentDisposition = download.mContentDisposition;
  toSend.mMimeType = download.mMimeType;

  webBrowser->DispatchEvent(Events::WebBrowserDownloadStarted, &toSend);

  download.mFilePath = toSend.mFilePath;
  *cancelOut = toSend.mCancel;
}

void WebBrowser::OnDownloadUpdated(const BrowserDownload& download, bool* cancelOut, Browser* browser)
{
  WebBrowser* webBrowser = (WebBrowser*)browser->mUserData;

  WebBrowserDownloadEvent toSend;
  toSend.mWebBrowser = webBrowser;

  toSend.mFilePath = download.mFilePath;
  toSend.mIsInProgress = download.mIsInProgress;
  toSend.mIsComplete = download.mIsComplete;
  toSend.mCurrentSpeed = download.mCurrentSpeed;
  toSend.mReceivedBytes = download.mReceivedBytes;
  toSend.mTotalBytes = download.mTotalBytes;
  toSend.mId = download.mId;
  toSend.mUrl = download.mUrl;
  toSend.mOriginalUrl = download.mOriginalUrl;
  toSend.mSuggestedFileName = download.mSuggestedFileName;
  toSend.mContentDisposition = download.mContentDisposition;
  toSend.mMimeType = download.mMimeType;

  webBrowser->DispatchEvent(Events::WebBrowserDownloadUpdated, &toSend);

  *cancelOut = toSend.mCancel;
}

} // namespace Plasma
