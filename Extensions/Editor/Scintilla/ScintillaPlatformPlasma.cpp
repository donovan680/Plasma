///////////////////////////////////////////////////////////////////////////////
///
/// \file TextEditor.cpp
/// Implementation of the Scintilla Platform on Plasma Engine
///
/// Authors: Chris Peters, Nathan Carlson
/// Copyright 2010-2011, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"
#include "ScintillaPrecompiled.hpp"

using namespace Math;

PRectangle ToPRectangle(Plasma::Widget* widget)
{
  Vec3 p = widget->GetTranslation();
  Vec2 s = widget->GetSize();
  return PRectangle(p.x, p.y, p.x + s.x, p.y + s.y);
}

Surface *Surface::Allocate(int technology)
{
  return new SurfaceImpl(nullptr);
}

SurfaceImpl::SurfaceImpl(Plasma::Widget* widget)
  : mWidget(widget)
{
}

void SurfaceImpl::Init(WindowID wid)
{
  // Do nothing
}

void SurfaceImpl::Init(SurfaceID sid, WindowID wid)
{
  // Do nothing
}

void SurfaceImpl::InitPixMap(int width, int height, Surface *surface_, WindowID wid)
{
  ErrorIf(true, "Not Valid");
}

void SurfaceImpl::Release()
{
  // Do nothing
}

bool SurfaceImpl::Initialised()
{
  return true;
}

void SurfaceImpl::PenColour(ColourDesired fore)
{
  mColor =  ToFloatColor(0xFF000000 | fore.AsLong());
}

int SurfaceImpl::LogPixelsY()
{
  return 10;
}

int SurfaceImpl::DeviceHeightFont(int points)
{
  return points;
}

void SurfaceImpl::MoveTo(int x_, int y_)
{
  mLastX = x_;
  mLastY = y_;
}

void SurfaceImpl::LineTo(int x_, int y_)
{
  if (mViewNode == nullptr || mDrawType != Lines)
  {
    mDrawType = Lines;
    Plasma::Texture* texture = Plasma::TextureManager::FindOrNull("White");
    mViewNode = &mWidget->AddRenderNodes(*mViewBlock, *mFrameBlock, mClipRect, texture);
    mViewNode->mStreamedVertexType = Plasma::PrimitiveType::Lines;
  }

  Vec3 newPoint = Vec3(x_, y_, 0) + Vec3(1.0f, 1.0f, 0.0f);
  Vec3 oldPoint = Vec3(mLastX, mLastY, 0) + Vec3(1.0f, 1.0f, 0.0f);
  mLastX = x_;
  mLastY = y_;

  Plasma::StreamedVertex v0(oldPoint, Vec2::cZero, mColor, Vec2::cZero);
  Plasma::StreamedVertex v1(newPoint, Vec2::cZero, mColor, Vec2::cZero);

  v0.mPosition = Math::TransformPoint(mViewNode->mLocalToView, v0.mPosition);
  v1.mPosition = Math::TransformPoint(mViewNode->mLocalToView, v1.mPosition);
  mFrameBlock->mRenderQueues->mStreamedVertices.PushBack(v0);
  mFrameBlock->mRenderQueues->mStreamedVertices.PushBack(v1);

  mViewNode->mStreamedVertexCount = mFrameBlock->mRenderQueues->mStreamedVertices.Size() - mViewNode->mStreamedVertexStart;
}

void SurfaceImpl::Polygon(Point *pts, int npts, ColourDesired fore, ColourDesired back)
{
  ErrorIf(true, "Not implemented.");
}

void SurfaceImpl::RectangleDraw(PRectangle rc, ColourDesired fore, ColourDesired back)
{
  if (mViewNode == nullptr || mDrawType != Lines)
  {
    mDrawType = Lines;
    Plasma::Texture* texture = Plasma::TextureManager::FindOrNull("White");
    mViewNode = &mWidget->AddRenderNodes(*mViewBlock, *mFrameBlock, mClipRect, texture);
    mViewNode->mStreamedVertexType = Plasma::PrimitiveType::Lines;
  }

  Vec3 pos0 = Vec3(rc.left, rc.top, 0);
  Vec3 pos1 = Vec3(rc.right, rc.bottom, 0);
  Vec4 color = ToFloatColor(0xFF000000 | fore.AsLong());

  mFrameBlock->mRenderQueues->AddStreamedLineRect(*mViewNode, pos0, pos1, Vec2(0, 0), Vec2(1, 1), color);
}

void SurfaceImpl::FillRectangle(PRectangle rc, ColourDesired back)
{
  if (mViewNode == nullptr || mDrawType != Quads)
  {
    mDrawType = Quads;
    Plasma::Texture* texture = Plasma::TextureManager::FindOrNull("White");
    mViewNode = &mWidget->AddRenderNodes(*mViewBlock, *mFrameBlock, mClipRect, texture);
  }

  Vec3 pos0 = Vec3(rc.left, rc.top, 0);
  Vec3 pos1 = Vec3(rc.right, rc.bottom, 0);
  Vec4 color = ToFloatColor(back.AsLong());

  mFrameBlock->mRenderQueues->AddStreamedQuad(*mViewNode, pos0, pos1, Vec2(0, 0), Vec2(1, 1), color);
}

void SurfaceImpl::FillRectangle(PRectangle rc, Surface &surfacePattern)
{
  ErrorIf(true, "Not implemented.");
}

void SurfaceImpl::RoundedRectangle(PRectangle rc, ColourDesired fore, ColourDesired back)
{
  ErrorIf(true, "Not implemented.");
}

void SurfaceImpl::AlphaRectangle(PRectangle rc, int cornerSize, ColourDesired fill, int alphaFill, ColourDesired outline, int alphaOutline, int flags)
{
  RoundedLineRectHelper(rc, cornerSize, fill, alphaFill, outline, alphaOutline, flags);

  if(mViewNode == nullptr || mDrawType != Quads)
  {
    mDrawType = Quads;
    Plasma::Texture* texture = Plasma::TextureManager::FindOrNull("White");
    mViewNode = &mWidget->AddRenderNodes(*mViewBlock, *mFrameBlock, mClipRect, texture);
  }

  Vec3 pos0 = Vec3(rc.left, rc.top, 0);
  Vec3 pos1 = Vec3(rc.right, rc.bottom , 0);
  Vec4 color = ToFloatColor((alphaFill << 24) | fill.AsLong());

  mFrameBlock->mRenderQueues->AddStreamedQuad(*mViewNode, pos0, pos1, Vec2(0,0), Vec2(1,1), color);
}

void SurfaceImpl::DrawRGBAImage(PRectangle rc, int width, int height, const unsigned char *pixelsImage)
{
  ErrorIf(true, "Not implemented.");
}

void SurfaceImpl::Ellipse(PRectangle rc, ColourDesired fore, ColourDesired back)
{
  ErrorIf(true, "Not implemented.");
}

void SurfaceImpl::Copy(PRectangle rc, Point from, Surface &surfaceSource)
{
  ErrorIf(true, "Not available in hardware accelerated version.");
}

void SurfaceImpl::DrawTextNoClip(PRectangle rc, Font &font_, XYPOSITION ybase, const char *s, int len, ColourDesired fore, ColourDesired back)
{
  if (len == 0)
    return;

  Plasma::RenderFont* font = (Plasma::RenderFont*)font_.fid;

  if (mViewNode == nullptr || mDrawType != Text)
  {
    mDrawType = Text;
    mViewNode = &mWidget->AddRenderNodes(*mViewBlock, *mFrameBlock, mClipRect, font->mTexture);
  }

  Plasma::StringRange text(s, s + len);
  Vec2 textStart = Vec2(rc.left, rc.top);
  Vec2 size = Vec2(rc.right, rc.bottom) - textStart;
  Vec4 color = ToFloatColor(0xFF000000 | fore.AsLong());

  Plasma::FontProcessor fontProcessor(mFrameBlock->mRenderQueues, mViewNode, color);
  AddTextRange(fontProcessor, font, text, textStart, Plasma::TextAlign::Left, Vec2(1, 1), size);
}

void SurfaceImpl::DrawTextClipped(PRectangle rc, Font &font_, XYPOSITION ybase, const char *s, int len, ColourDesired fore, ColourDesired back)
{
  ErrorIf(true, "Not implemented.");
}

void SurfaceImpl::DrawTextTransparent(PRectangle rc, Font &font_, XYPOSITION ybase, const char *s, int len, ColourDesired fore)
{
  if (len == 0)
    return;

  Plasma::RenderFont* font = (Plasma::RenderFont*)font_.fid;

  if (mViewNode == nullptr || mDrawType != Text)
  {
    mDrawType = Text;
    mViewNode = &mWidget->AddRenderNodes(*mViewBlock, *mFrameBlock, mClipRect, font->mTexture);
  }

  Plasma::StringRange text(s, s + len);
  Vec2 textStart = Vec2(rc.left, rc.top);
  Vec2 size = Vec2(rc.right, rc.bottom) - textStart;
  Vec4 color = ToFloatColor(fore.AsLong());

  Plasma::FontProcessor fontProcessor(mFrameBlock->mRenderQueues, mViewNode, color);
  AddTextRange(fontProcessor, font, text, textStart, Plasma::TextAlign::Left, Vec2(1, 1), size);
}

void SurfaceImpl::MeasureWidths(Font &font_, const char *s, int len, XYPOSITION *positions)
{
  Plasma::RenderFont* font = (Plasma::RenderFont*)font_.fid;
  if (font)
  {
    int start = 0;
    for (int i = 0; i < len; ++i)
    {
      Vec2 size = font->MeasureText(Plasma::StringRange(s + i, s + i + 1), 1.0f);
      start += (int)size.x;
      positions[i] = start;
    }
  }
  else
  {
    //Fill with defaults.
    int start = 0;
    for (int i = 0; i < len; ++i)
    {
      positions[i] = start;
      start += 5;
    }
  }
}

XYPOSITION SurfaceImpl::WidthText(Font &font_, const char *s, int len)
{
  Plasma::RenderFont* font = (Plasma::RenderFont*)font_.fid;
  if (font)
  {
    Vec2 size = font->MeasureText(Plasma::StringRange(s), len, 1.0f);
    return size.x;
  }
  return 1.0f;
}

XYPOSITION SurfaceImpl::WidthChar(Font &font_, char ch)
{
  Plasma::RenderFont* font = (Plasma::RenderFont*)font_.fid;
  if (font)
  {
    const char a[2] = {ch, '\0'};
    Vec2 size = font->MeasureText(Plasma::StringRange(a), 1, 1.0f);
    return size.x;
  }
  return 5;
}

XYPOSITION SurfaceImpl::Ascent(Font &font_)
{
  Plasma::RenderFont* font = (Plasma::RenderFont*)font_.fid;
  return font->mFontHeight;
}

XYPOSITION SurfaceImpl::Descent(Font &font_)
{
  Plasma::RenderFont* font = (Plasma::RenderFont*)font_.fid;
  return font->mDescent;
}

XYPOSITION SurfaceImpl::InternalLeading(Font &font_)
{
  return 0;
}

XYPOSITION SurfaceImpl::ExternalLeading(Font &font_)
{
  return 0;
}

XYPOSITION SurfaceImpl::Height(Font &font_)
{
  Plasma::RenderFont* font = (Plasma::RenderFont*)font_.fid;
  return font->mFontHeight;
}

XYPOSITION SurfaceImpl::AverageCharWidth(Font &font_)
{
  Plasma::RenderFont* font = (Plasma::RenderFont*)font_.fid;
  return font->mFontHeight;
}

void SurfaceImpl::SetClip(PRectangle rc)
{
  //mClipRect.X = mBaseRect.X + rc.left;
  //mClipRect.Y = mBaseRect.Y + rc.top;
  //mClipRect.SizeX = rc.right - rc.left;
  //mClipRect.SizeY = rc.bottom - rc.top;
}

void SurfaceImpl::FlushCachedState()
{
  // Do nothing
}

void SurfaceImpl::SetUnicodeMode(bool unicodeMode_)
{
  // Do nothing
}

void SurfaceImpl::SetDBCSMode(int codePage)
{
  // Do nothing
}

// 'cornerEmulation' is either 0 or 1 based on 'cornerSize' passed from Scintilla
// to the 'AlphaRectangle' method defined in this file.  Internally, Scintilla
// keeps track of an indicator style for each indicator ID. So, if:
//
// style == INDIC_ROUNDBOX [ie, Plasma's IndicatorStyle::Roundbox]
//
// then: 'cornerSize' is 1, and thus 'cornerEmulation' is 1.
void SurfaceImpl::RoundedLineRectHelper(PRectangle rc, int cornerEmulation, ColourDesired fill, int alphaFill, ColourDesired outline, int alphaOutline, int flags)
{
  if(mViewNode == nullptr || mDrawType != Lines)
  {
    mDrawType = Lines;
    Plasma::Texture* texture = Plasma::TextureManager::FindOrNull("White");
    mViewNode = &mWidget->AddRenderNodes(*mViewBlock, *mFrameBlock, mClipRect, texture);
    mViewNode->mStreamedVertexType = Plasma::PrimitiveType::Lines;
  }

  // Prevent the bottom line of the outline rect from getting clipped by Scintilla.
  const int cScintillaCorrection = 1;

  Vec3 pos0 = Vec3(rc.left, rc.top, 0);
  Vec3 pos1 = Vec3(rc.right, rc.bottom - cScintillaCorrection, 0);
  Vec4 color = ToFloatColor((alphaOutline << 24) | outline.AsLong());

  Vec2 uv0(0,0);
  Vec2 uv1(1,1);

  if(cornerEmulation == 0)
  {
    mFrameBlock->mRenderQueues->AddStreamedLineRect(*mViewNode, pos0, pos1, uv0, uv1, color);
    return;
  }

  int ce = cornerEmulation;

  float leftX = pos0.x;
  float rightX = pos1.x + ce;
  Plasma::StreamedVertex v0(Math::TransformPoint(mViewNode->mLocalToView, Vec3(leftX, pos0.y, 0)), uv0, color, uv0);
  Plasma::StreamedVertex v1(Math::TransformPoint(mViewNode->mLocalToView, Vec3(leftX, pos1.y, 0)), Vec2(uv0.x, uv1.y), color, Vec2(uv0.x, uv1.y));
  Plasma::StreamedVertex v2(Math::TransformPoint(mViewNode->mLocalToView, Vec3(pos1.x, pos1.y, 0)), uv1, color, uv1);
  Plasma::StreamedVertex v3(Math::TransformPoint(mViewNode->mLocalToView, Vec3(rightX, pos0.y, 0)), Vec2(uv1.x, uv0.y), color, Vec2(uv1.x, uv0.y));

  Plasma::RenderQueues* queue = mFrameBlock->mRenderQueues;

  // TopLeft to BottomLeft
  queue->mStreamedVertices.PushBack(v0);
  queue->mStreamedVertices.PushBack(v1);
  // BottomLeft to BottomRight
  queue->mStreamedVertices.PushBack(v1);
  queue->mStreamedVertices.PushBack(v2);
  // BottomRight to TopRight
  v2.mPosition = Math::TransformPoint(mViewNode->mLocalToView, Vec3(rightX, pos1.y, 0));
  queue->mStreamedVertices.PushBack(v2);
  queue->mStreamedVertices.PushBack(v3);
  // TopRight to TopLeft
  float topY = pos0.y - ce;
  v3.mPosition = Math::TransformPoint(mViewNode->mLocalToView, Vec3(pos1.x, topY, 0));
  v0.mPosition = Math::TransformPoint(mViewNode->mLocalToView, Vec3(leftX, topY, 0));
  queue->mStreamedVertices.PushBack(v3);
  queue->mStreamedVertices.PushBack(v0);

  mViewNode->mStreamedVertexCount = queue->mStreamedVertices.Size() - mViewNode->mStreamedVertexStart;
  mViewNode->mStreamedVertexType = Plasma::PrimitiveType::Lines;
}


class DynamicLibraryImpl : public DynamicLibrary
{
public:
  DynamicLibraryImpl(const char *modulePath){}
  virtual ~DynamicLibraryImpl(){}
  virtual Scintilla::Function FindFunction(const char *name){return NULL;}
  virtual bool IsValid(){return false;}
};

// Scintilla LexerLibrary requires this to be implemented
DynamicLibrary *DynamicLibrary::Load(const char *modulePath)
{
  return static_cast<DynamicLibrary *>(new DynamicLibraryImpl(modulePath));
}

Font::Font()
{
  fid = 0;
}

Font::~Font()
{
}

void Font::Create(const FontParameters &fp)
{
  this->fid = Plasma::FontManager::GetInstance()->GetRenderFont(fp.faceName, fp.size, 0);
}

void Font::Release()
{
}

Window::~Window()
{
}

void Window::Destroy()
{
  if(wid)
  {
    Plasma::Widget* widget = (Plasma::Widget*)wid;
    widget->Destroy();
  }
  wid = 0;
}

bool Window::HasFocus()
{
  Plasma::Widget* widget = (Plasma::Widget*)wid;
  return widget->HasFocus();
}

PRectangle Window::GetPosition()
{
  Plasma::Widget* widget = (Plasma::Widget*)wid;
  Vec3 p = widget->GetTranslation();
  Vec2 s = widget->GetSize();
  return PRectangle(p.x, p.y, p.x + s.x, p.y + s.y);
}

void Window::SetPosition(PRectangle rc)
{
  SetPositionRelative(rc, Window());
}

void Window::SetPositionRelative(PRectangle rc, Window w)
{
  Plasma::Widget* widget = (Plasma::Widget*)wid;
  Plasma::Widget* relativeWidget = (Plasma::Widget*)w.wid;
  Vec3 p = Vec3(rc.left, rc.top, 0);
  Vec2 s = Vec2(rc.right - rc.left, rc.bottom - rc.top);
  p += relativeWidget->GetScreenPosition();

  widget->SetTranslationAndSize(p, s);
}

PRectangle Window::GetClientPosition()
{
  Plasma::Widget* widget = (Plasma::Widget*)wid;
  return ToPRectangle(widget);
}

void Window::Show(bool show)
{
  Plasma::Widget* widget = (Plasma::Widget*)wid;
  widget->SetActive(show);
}

void Window::InvalidateAll()
{
}

void Window::InvalidateRectangle(PRectangle rc)
{
}

void Window::SetFont(Font &font)
{
}

void Window::SetCursor(Cursor curs)
{
  switch (curs) {
  case cursorText:
    Plasma::PL::gMouse->SetCursor(Plasma::Cursor::TextBeam);
    break;
  case cursorUp:
    Plasma::PL::gMouse->SetCursor(Plasma::Cursor::Arrow);
    break;
  case cursorWait:
    Plasma::PL::gMouse->SetCursor(Plasma::Cursor::Wait);
    break;
  case cursorHoriz:
    Plasma::PL::gMouse->SetCursor(Plasma::Cursor::SizeWE);
    break;
  case cursorVert:
    Plasma::PL::gMouse->SetCursor(Plasma::Cursor::SizeNS);
    break;
  case cursorHand:
    Plasma::PL::gMouse->SetCursor(Plasma::Cursor::Hand);
    break;
  case cursorReverseArrow:
    Plasma::PL::gMouse->SetCursor(Plasma::Cursor::Arrow);
    break;
  case cursorArrow:
  case cursorInvalid:// Should not occur, but just in case.
    Plasma::PL::gMouse->SetCursor(Plasma::Cursor::Arrow);
    break;
  }
}

void Window::SetTitle(const char *s)
{
}

// Returns rectangle of monitor pt is on, both rect and pt are in Window's coordinates
PRectangle Window::GetMonitorRect(Point pt)
{
  Plasma::Widget* widget = (Plasma::Widget*)wid;
  widget = widget->GetRootWidget();
  return ToPRectangle(widget);
}

ListBox::ListBox()
{
}

ListBox::~ListBox()
{
}

class ListBoxPlasma : public ListBox
{
public:
  typedef ListBoxPlasma LightningSelf;
  Plasma::EventReceiver mReceiver;
  Plasma::EventReceiver* GetReceiver(){return &mReceiver;}
  Plasma::ListBox* mListBox;
  uint mVisibleRows;
  Plasma::StringSource mOptions;

  ListBoxPlasma()
  {
    mListBox = NULL;
    mCallback = NULL;
  }

  virtual void SetFont(Font &font){}

  virtual void Create(Window& parent, int ctrlID, Point location, int lineHeight_, bool unicodeMode_, int technology_)
  {
    Plasma::Widget* widget = (Plasma::Widget*)parent.GetID();
    mListBox = new Plasma::ListBox(widget->GetRootWidget()->GetPopUp());
    mListBox->SetDataSource(&mOptions);
    wid = mListBox;

    ConnectThisTo(widget, Plasma::Events::ItemSelected, OnItemSelected);
  }

  void OnItemSelected(Plasma::Event* event)
  {
    if(mCallback)
      (*mCallback)(mCallbackData);
  }

  virtual void SetAverageCharWidth(int width)
  {
  }

  virtual void SetVisibleRows(int rows)
  {
    mVisibleRows = rows;
  }
  virtual int GetVisibleRows() const
  {
    return mVisibleRows;
  }

  virtual PRectangle GetDesiredRect()
  {
    uint size = Math::Min(int(200), int(mOptions.Strings.Size() * 20));
    return PRectangle(0,0,180, size);
  }

  virtual int CaretFromEdge()
  {
    return 0;
  }

  virtual void Clear()
  {
    mOptions.Strings.Clear();
  }

  virtual void Append(char *s, int type = -1)
  {

  }

  virtual int Length()
  {
    return mOptions.Strings.Size();
  }

  virtual void Select(int n)
  {
    mListBox->SetSelectedItem(n, false);
    mListBox->ScrollToView();
  }

  virtual int GetSelection()
  {
    return mListBox->GetSelectedItem();
  }

  virtual int Find(const char *prefix)
  {
    return 1;
  }

  virtual void GetValue(int n, char *value, int len)
  {
    strcpy(value, mOptions.Strings[n].Data());
  }

  CallBackAction mCallback;
  void* mCallbackData;

  virtual void RegisterImage(int type, const char *xpm_data){}
  virtual void ClearRegisteredImages(){}
  virtual void SetDoubleClickAction(CallBackAction callback, void* data)
  {
    mCallback = callback;
    mCallbackData = data;
  }

  virtual void RegisterRGBAImage(int type, int width, int height, const unsigned char *pixelsImage)
  {

  }

  virtual void SetList(const char* list, char separator, char typesep)
  {
    Plasma::StringTokenRange tokens(list, separator);
    while(!tokens.Empty())
    {
      mOptions.Strings.PushBack(tokens.Front());
      tokens.PopFront();
    }
  }
};

ListBox* ListBox::Allocate(void)
{
  return new ListBoxPlasma();
}

Menu::Menu() : mid(0)
{
}

void Menu::CreatePopUp()
{
}

void Menu::Destroy()
{
  mid = 0;
}

void Menu::Show(Point pt, Window &w)
{
}

ColourDesired Platform::Chrome()
{
  return ByteColorRGBA(0x2E, 0x2E, 0x2E, 0xFF);
}

ColourDesired Platform::ChromeHighlight()
{
  return ByteColorRGBA(0x2E, 0x2E, 0x2E, 0xFF);
}

const char *Platform::DefaultFont()
{
  return "Inconsolata";
}

int Platform::DefaultFontSize()
{
  return 15;
}

unsigned int Platform::DoubleClickTime()
{
  return 100;
}

bool Platform::MouseButtonBounce()
{
  return false;
}

void Platform::DebugDisplay(const char *s)
{
  DebugPrint(s);
}

bool Platform::IsKeyDown(int key)
{
  return 0;
}

long Platform::SendScintilla(WindowID w, unsigned int msg, unsigned long wParam, long lParam)
{
  return 0;
}

long Platform::SendScintillaPointer(WindowID w, unsigned int msg, unsigned long wParam, void *lParam)
{
  return 0;
}

bool Platform::IsDBCSLeadByte(int codePage, char ch)
{
  return false;
}

int Platform::DBCSCharLength(int codePage, const char *s)
{
  return 1;
}

int Platform::DBCSCharMaxLength()
{
  return 2;
}

// These are utility functions not really tied to a platform

int Platform::Minimum(int a, int b)
{
  if (a < b)
    return a;
  else
    return b;
}

int Platform::Maximum(int a, int b)
{
  if (a > b)
    return a;
  else
    return b;
}

int Platform::Clamp(int val, int minVal, int maxVal)
{
  if (val > maxVal)
    val = maxVal;
  if (val < minVal)
    val = minVal;
  return val;
}

void Platform::DebugPrintf(const char *, ...)
{
}

bool Platform::ShowAssertionPopUps(bool assertionPopUps_)
{
  return false;
}

void Platform::Assertion(const char *c, const char *file, int line)
{
  bool ignore = false;
  bool safe = Plasma::ErrorSignaler::SignalError(Plasma::ErrorSignaler::Error, c, file, line, ignore, "Scintilla Error");
  ErrorIf(!safe, "Break Scintilla");
}
