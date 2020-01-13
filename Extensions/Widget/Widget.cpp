///////////////////////////////////////////////////////////////////////////////
///
/// \file Widget.cpp
/// Implementation of the base widget class.
///
/// Authors: Chris Peters
/// Copyright 2010-2011, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#include "Precompiled.hpp"

namespace Plasma
{

//---------------------------------------------------------------- Size Policies
//******************************************************************************
LightningDefineType(SizePolicies, builder, type)
{
}

//----------------------------------------------------------------------- Widget
//******************************************************************************
LightningDefineType(Widget, builder, type)
{
  type->HandleManager = LightningManagerId(WidgetHandleManager);
}

void WidgetHandleManager::ObjectToHandle(const byte* object, BoundType* type, Handle& handleToInitialize)
{
  if (object == nullptr)
    return;

  Widget* instance = (Widget*)object;
  handleToInitialize.HandleU64 = instance->mId;
}

byte* WidgetHandleManager::HandleToObject(const Handle& handle)
{
  return (byte*)PL::gWidgetManager->Widgets.FindValue(handle.HandleU64, nullptr);
}

void WidgetHandleManager::Delete(const Handle& handle)
{
  Widget* widget = handle.Get<Widget*>();
  if (widget)
    widget->Destroy();
}

bool WidgetHandleManager::CanDelete(const Handle& handle)
{
  return true;
}

u64 WidgetHandleManager::HandleToId(const Handle& handle)
{
  if (handle.StoredType == nullptr)
    return 0;

  ReturnIf(!Type::BoundIsA(handle.StoredType, LightningTypeId(Widget)), 0,
    "A handle to a non widget was passed in.");

  return handle.HandleU64;
}


Widget::Widget(Composite* parent, AttachType::Enum attachType)
{
  mId = ++PL::gWidgetManager->IdCounter;
  PL::gWidgetManager->Widgets.Insert(mId, this);

  ClearValues();

  if(parent)
  {
    mRootWidget = parent->mRootWidget;
    mDefSet = parent->GetDefinitionSet();
    parent->AttachChildWidget(this, attachType);
  }
  else
  {
    mDefSet = DefinitionSetManager::GetInstance()->Main;
    mRootWidget = (RootWidget*)this;
  }
}

void Widget::ClearValues()
{
  mWorldTx = Mat4::cIdentity;
  mCurDockMode = DockMode::DockNone;
  mTransformUpdateState = TransformUpdateState::LocalUpdate;
  mDocker = nullptr;
  mParent = nullptr;
  mDefSet = nullptr;
  mSize = Vec2(10, 10);
  mTranslation = Vec3::cZero;
  mColor = Vec4(1, 1, 1, 1);
  mNotInLayout = false;
  mHideOnClose = false;
  mDestroyed = false;
  mActions = nullptr;
  mAngle = 0.0f;
  mActive = true;
  mVisible = true;
  mClipping = false;
  mInteractive = true;
  mOrigin = DisplayOrigin::TopLeft;
  mTakeFocusMode = FocusMode::Soft;
  mNeedsRedraw = true;
  mSizePolicy = SizePolicies(SizePolicy::Flex, SizePolicy::Flex);
  mDragDistance = 6.0f;
  mHorizontalAlignment = HorizontalAlignment::Left;
  mVerticalAlignment = VerticalAlignment::Top;
  mManager = nullptr;
}

Widget::~Widget()
{
  SafeDelete(mDocker);
  SafeRelease(mActions);

  if(mManager)
    mManager->Destroyed(this);

  if(mParent)
  {
    mParent->MarkAsNeedsUpdate(true);
    mParent->mChildren.Erase(this);
    mParent = nullptr;
  }
}

String Widget::GetDebugName()
{
  if(!mName.Empty())
    return mName;

  return LightningVirtualTypeId(this)->Name;
}

void Widget::InternalDestroy()
{
  if(!mDestroyed)
  {
    mDestroyed = true;
    mNotInLayout = true;

    PL::gWidgetManager->Widgets.Erase(mId);
    PL::gWidgetManager->DestroyList.PushBack(this);

    if(HasFocus())
      this->LoseFocus();
  }
}

void Widget::OnDestroy()
{

}

void Widget::Destroy()
{
  if(!mDestroyed)
  {
    // Call on Destroy for this chain
    this->OnDestroy();
    InternalDestroy();
  }
}

void Widget::SetName(StringParam name)
{
  mName = name;
}

String Widget::GetName()
{
  return mName;
}

bool Widget::InputBlocked()
{
  return !mInteractive || !mActive || !mVisible || mDestroyed;
}

bool Widget::CheckClipping(Vec2Param screenPoint)
{
  if(mClipping)
  {
    WidgetRect rect = GetLocalRect();
    Vec2 localMousePos = this->ToLocal(screenPoint);
    bool withIn = rect.Contains(localMousePos);
    if(!withIn)
      return false;
  }
  return true;
}

Widget* Widget::HitTest(Vec2 screenPoint, Widget* ignore)
{
  // Skip inactive object
  if(InputBlocked())
    return nullptr;

  if(ignore == this)
    return nullptr;

  // Check for containment
  if(!CheckClipping(screenPoint))
    return nullptr;

  if(!Contains(screenPoint))
    return nullptr;

  return this;
}

RootWidget* Widget::GetRootWidget()
{
  return mRootWidget;
}

void Widget::SetDocker(Docker* docker)
{
  SafeDelete(mDocker);
  mDocker = docker;
}

void Widget::DispatchBubble(StringParam eventId, Event* event)
{
  GetDispatcher()->Dispatch(eventId, event);
  if(mParent) mParent->DispatchBubble(eventId, event);
}

Actions* Widget::GetActions()
{
  if(mActions == nullptr)
  {
    mActions = new Actions(PL::gWidgetManager->mWidgetActionSpace);
    mActions->AddReference();
  }
  return mActions;
}

bool Widget::HasFocus()
{
  return mFlags.IsSet(DisplayFlags::FocusHierarchy);
}

bool Widget::IsMouseOver()
{
  return mFlags.IsSet(DisplayFlags::MouseOverHierarchy);
}

void Widget::SetColor(Vec4Param color)
{
  if (color == mColor)
    return;
  mColor = color;
  MarkAsNeedsUpdate();
}

void Widget::SetSize(Vec2 newSize)
{
  mSize = SnapToPixels(newSize);
  MarkAsNeedsUpdate();
}

void Widget::SetSizing(SizeAxis::Enum axis, SizePolicy::Enum policy, float size)
{
  mSizePolicy.Policy[axis] = policy;
  mSizePolicy.Size[axis] = size;
  if (policy == SizePolicy::Fixed)
    mSize[axis] = size;
}

void Widget::SetSizing(SizePolicy::Enum policy, Vec2Param size)
{
  SetSizing(SizeAxis::X, policy, size.x);
  SetSizing(SizeAxis::Y, policy, size.y);
}

void Widget::SetSizing(SizePolicy::Enum policy, float size)
{
  SetSizing(policy, Vec2(size));
}

void Widget::SetTranslation(Vec3 newTranslation)
{
  mTranslation = SnapToPixels(newTranslation);
  MarkAsNeedsUpdate();
}

void Widget::SetTranslationAndSize(Vec3 newTranslation, Vec2 newSize)
{
  mSize = SnapToPixels(newSize);
  mTranslation = SnapToPixels(newTranslation);
  MarkAsNeedsUpdate();
}

void Widget::NeedsRedraw()
{
  mNeedsRedraw = true;
  if(mParent)
    mParent->NeedsRedraw();
}

void Widget::MarkAsNeedsUpdate(bool local)
{
  mNeedsRedraw = true;

  if(mTransformUpdateState == TransformUpdateState::Updated)
  {
    if(local)
      mTransformUpdateState = TransformUpdateState::LocalUpdate;
    else
      mTransformUpdateState = TransformUpdateState::ChildUpdate;

    if(mParent)
      mParent->MarkAsNeedsUpdate(false);
  }
  else if(local && mTransformUpdateState == TransformUpdateState::ChildUpdate)
  {
    mTransformUpdateState = TransformUpdateState::LocalUpdate;
  }
}

bool Widget::IsAncestorOf(Widget* child)
{
  Widget* current = child;
  while(current)
  {
    current = current->GetParent();
    if(current == this)
      return true;
  }
  return false;
}

void Widget::MoveToFront()
{
  Composite* parent = mParent;
  parent->mChildren.Erase(this);
  parent->mChildren.PushBack(this);
}

void Widget::MoveToBack()
{
  Composite* parent = mParent;
  parent->mChildren.Erase(this);
  parent->mChildren.PushFront(this);
}

Vec2 Widget::ToLocal(Vec2Param screenPoint)
{
  Mat4 toLocal = Invert2D(mWorldTx);
  Vec3 localPoint = TransformPointCol(toLocal, Vec3(screenPoint.x, screenPoint.y, 0.0f));
  return Vec2(localPoint.x, localPoint.y);
}

Vec3 Widget::ToLocal(Vec3Param screenPoint)
{
  Mat4 toLocal = Invert2D(mWorldTx);
  return TransformPointCol(toLocal, screenPoint);
}

Vec2 Widget::ToScreen(Vec2Param localPoint)
{
  Vec3 screenPoint = Math::ToVector3(localPoint, 0.0f);
  screenPoint = TransformPointCol(mWorldTx, screenPoint);
  return Vec2(screenPoint.x, screenPoint.y);
}

Vec3 Widget::GetScreenPosition() const
{
  if(mParent)
    return mTranslation + mParent->GetScreenPosition();
  return mTranslation;
}

WidgetRect Widget::GetRectInParent()
{
  WidgetRect local = GetLocalRect();
  local.X = mTranslation.x;
  local.Y = mTranslation.y;
  return local;
}

WidgetRect Widget::GetLocalRect() const
{
  if(mOrigin == DisplayOrigin::Center)
    return WidgetRect::PointAndSize(mSize * 0.5f, mSize);
  else
    return WidgetRect::PointAndSize(Vec2::cZero, mSize);
}

WidgetRect Widget::GetScreenRect() const
{
  Vec3 screenPos = GetScreenPosition();
  WidgetRect rect = GetLocalRect();
  rect.X += screenPos.x;
  rect.Y += screenPos.y;
  return rect;
}

Vec2 Widget::GetClientCenterPosition() const
{
  WidgetRect clientRect = GetScreenRect();
  return Vec2(clientRect.X + clientRect.SizeX / 2.0f, clientRect.Y + clientRect.SizeY / 2.0f);
}

bool Widget::Contains(Vec2 screenPoint)
{
  WidgetRect localRect = GetLocalRect();
  Vec2 localMousePos = this->ToLocal(screenPoint);
  return localRect.Contains(localMousePos);
}

bool Widget::TryTakeFocus()
{
  return this->TakeFocusOverride();
}

void Widget::TakeFocus()
{
  bool focusTaken = this->TakeFocusOverride();
  ErrorIf(!focusTaken, "The widget can not take focus.");
}

void Widget::SoftTakeFocus()
{
  GetRootWidget()->RootSoftTakeFocus(this);
}

void Widget::HardTakeFocus()
{
  GetRootWidget()->RootChangeFocus(this, FocusMode::Hard);
}

bool Widget::TakeFocusOverride()
{
  // By default do not take focus
  return false;
}

void Widget::LoseFocus()
{
  GetRootWidget()->RootRemoveFocus(this);
  MarkAsNeedsUpdate(true);
}

void Widget::ChangeDefinition(BaseDefinition* def)
{

}

void Widget::CaptureMouse()
{
  GetRootWidget()->RootCaptureMouse(this);
}

void Widget::ReleaseMouseCapture()
{
  GetRootWidget()->RootReleaseMouseCapture(this);
}

void Widget::SetRotation(float angle)
{
  mAngle = angle;
}

float Widget::GetRotation()
{
  return mAngle;
}

void Widget::ScreenCaptureBackBuffer(Image& image)
{
  WidgetRect rect = GetLocalRect();
  ScreenCaptureBackBuffer(image, rect);
}

void Widget::ScreenCaptureBackBuffer(Image& image, WidgetRect& subRect)
{
  //GraphicsViewport viewport = GenerateSubViewport(mWorldTx, subRect.TopLeft(), subRect.Size());

  //RootWidget* root = GetRootWidget();
  //CaptureViewport(root->GetOsWindow()->GetGraphicsContext(), &image, viewport);
}

void Widget::SetTakeFocusMode(FocusMode::Type focusMode)
{
  mTakeFocusMode = focusMode;
}

void Widget::SetClipping(bool clipping)
{
  mClipping = clipping;
}

void Widget::DispatchAt(DispatchAtParams& params)
{
  Widget* hit = this->HitTest(params.Position, params.Ignore);
  if(!hit) return;

  if(params.BubbleEvent)
    hit->DispatchBubble(params.EventId, params.EventObject);
  else
    hit->DispatchEvent(params.EventId, params.EventObject);
  params.ObjectHit = true;
}

bool Widget::GetClipping()
{
  return mClipping;
}

bool GetZIndexDepthFirst(Widget* widget, Widget* target, int* zindex)
{
  if (!widget)
    return false;

  Composite* composite = widget->GetSelfAsComposite();
  if (composite)
  {
    forRange(Widget& child, composite->GetChildren())
    {
      if (&child == target)
        return true;
      else
        ++*zindex;

      // If we found the child, stop execution and return all the way up.
      if (GetZIndexDepthFirst(&child, target, zindex))
        return true;
    }
  }
  return false;
}

int Widget::GetZIndex()
{
  // This is a potentially expensive function to call because it walks
  // all widgets until we find our own widget (from the root).
  int zindex = 0;
  GetZIndexDepthFirst(GetRootWidget(), this, &zindex);
  return zindex;
}

void Widget::BuildLocalMatrix(Mat4& output)
{
  Build2dTransform(output, this->mTranslation, this->mAngle);
}

void Widget::RenderUpdate(ViewBlock& viewBlock, FrameBlock& frameBlock, Mat4Param parentTx, ColorTransform colorTx, WidgetRect clipRect)
{
  Mat4 localTx;
  BuildLocalMatrix(localTx);
  mWorldTx = localTx * parentTx;
}

ViewNode& Widget::AddRenderNodes(ViewBlock& viewBlock, FrameBlock& frameBlock, WidgetRect clipRect, Texture* texture)
{
  FrameNode& frameNode = frameBlock.mFrameNodes.PushBack();
  ViewNode& viewNode = viewBlock.mViewNodes.PushBack();

  frameNode.mGraphicalEntry = nullptr;
  viewNode.mGraphicalEntry = nullptr;

  frameNode.mBorderThickness = 1.0f;
  frameNode.mBlendSettingsOverride = false;
  frameNode.mRenderingType = RenderingType::Streamed;
  frameNode.mCoreVertexType = CoreVertexType::Streamed;
  frameNode.mLocalToWorld = mWorldTx.Transposed();
  viewNode.mFrameNodeIndex = frameBlock.mFrameNodes.Size() - 1;
  viewNode.mLocalToView = viewBlock.mWorldToView * frameNode.mLocalToWorld;

  frameNode.mClip = Vec4(clipRect.X, clipRect.Y, clipRect.SizeX, clipRect.SizeY);

  // maybe cache this lookup on root
  Material* spriteMaterial = nullptr;
  
  if(texture->mType == TextureType::TextureCube)
    spriteMaterial = MaterialManager::FindOrNull("TextureCubePreview");
  else
    spriteMaterial = MaterialManager::FindOrNull("AlphaSprite");

  frameNode.mMeshRenderData = nullptr;
  frameNode.mMaterialRenderData = spriteMaterial->mRenderData;
  frameNode.mTextureRenderData = texture->mRenderData;

  // default setup for adding streamed data
  viewNode.mStreamedVertexType = PrimitiveType::Triangles;
  viewNode.mStreamedVertexStart = frameBlock.mRenderQueues->mStreamedVertices.Size();
  viewNode.mStreamedVertexCount = 0;

  return viewNode;
}

void Widget::CreateRenderData(ViewBlock& viewBlock, FrameBlock& frameBlock, WidgetRect clipRect, Array<StreamedVertex>& vertices, PrimitiveType::Enum primitiveType)
{
  if (vertices.Empty())
    return;

  StreamedVertexArray& streamedVertices = frameBlock.mRenderQueues->mStreamedVertices;

  static Texture* white = TextureManager::Find("White");
  ViewNode& viewNode = AddRenderNodes(viewBlock, frameBlock, clipRect, white);
  viewNode.mStreamedVertexType = primitiveType;

  for (uint i = 0; i < vertices.Size(); ++i)
  {
    StreamedVertex vertex = vertices[i];
    vertex.mPosition = Math::TransformPoint(viewNode.mLocalToView, vertex.mPosition);
    streamedVertices.PushBack(vertex);
  }

  viewNode.mStreamedVertexCount = streamedVertices.Size() - viewNode.mStreamedVertexStart;
}

void Widget::SizeToContents()
{
  SetSize(GetMinSize());
}

void Widget::UpdateTransformExternal()
{
  UpdateTransform();

  static String message = "Improper Widget Update. Did you forget to call your base UpdateTransform at the end of "
                         "your UpdateTransform?";
  ErrorIf(!mDestroyed && mTransformUpdateState != TransformUpdateState::Updated, message.c_str());
}

void Widget::UpdateTransform()
{
  //Clear the update flag
  mTransformUpdateState = TransformUpdateState::Updated;
}

void Widget::SetDockMode(DockMode::Enum dockMode)
{
  mCurDockMode = dockMode;
  mParent->MarkAsNeedsUpdate();
}

void Widget::SetDockArea(DockArea::Enum dockArea)
{
  if(mDocker)
    mDocker->Dock(this, dockArea);
  if(dockArea == DockArea::Floating)
    SetDockMode(DockMode::DockNone);
  else
    SetDockMode(DockMode::DockFill);
}

bool Widget::GetActive()
{
  return mActive;
}

bool Widget::GetGlobalActive()
{
  Widget* current = this;
  while(current)
  {
    if (current->mActive == false)
      return false;
    current = current->mParent;
  }

  return true;
}

void Widget::SetActive(bool active)
{
  if(mActive != active)
  {
    mActive = active;
    MarkAsNeedsUpdate();
    mParent->MarkAsNeedsUpdate();

    // Activated does not bubble.
    ObjectEvent event(this);
    if(active)
      DispatchEvent(Events::Activated, &event);
    else
    {
      DispatchEvent(Events::Deactivated, &event);
      LoseFocus();
    }
  }
}

void Widget::SetInteractive(bool interactive)
{
  mInteractive = interactive;
}

Vec2 Widget::GetMinSize()
{
  return Pixels(100, 100);
}

Vec2 Widget::Measure(LayoutArea& data)
{
  Vec2 measureSize = GetMinSize();
  if(mSizePolicy.XPolicy == SizePolicy::Fixed)
    measureSize.x = mSize.x;
  if(mSizePolicy.YPolicy == SizePolicy::Fixed)
    measureSize.y = mSize.y;
  return measureSize;
}

Element* Widget::CreateAttachedGeneric(StringParam name)
{
  Composite* thisComposite = this->GetSelfAsComposite();
  ImageWidget* w = new ImageWidget(thisComposite, name, AttachType::Direct);
  w->SetNotInLayout(true);
  return w;
}

Thickness Widget::GetBorderThickness()
{
  return Thickness::cZero;
}

}//namespace Plasma
