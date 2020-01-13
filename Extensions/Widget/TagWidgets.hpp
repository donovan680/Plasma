///////////////////////////////////////////////////////////////////////////////
///
/// \file Tags.hpp
/// Declaration of the Tags composite.
/// 
/// Authors: Joshua Claeys
/// Copyright 2013, DigiPen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{
namespace Events
{
  DeclareEvent(TagDeleted);
  DeclareEvent(TagsModified);
  DeclareEvent(SearchDataModified);
}

//-------------------------------------------------------------------- Tag Event
class TagEvent : public Event
{
public:
  LightningDeclareType(TagEvent, TypeCopyMode::ReferenceType);
  TagLabel* mTag;
  String mTagName;
};

//-------------------------------------------------------------------------- Tag
class TagLabel : public Composite
{
public:
  typedef TagLabel self_type;
  typedef TagLabel LightningSelf;

  /// Constructor.
  TagLabel(Composite* parent, StringParam name, bool removeable);

  /// Widget interface.
  void UpdateTransform() override;

  Vec2 GetDesiredSize();

  String GetName();

  bool mRemoveable;

private:
  /// Event Response.
  void OnMouseEnterBackground(MouseEvent* e);
  void OnMouseExitBackground(MouseEvent* e);
  void OnDelete(MouseEvent* e);

  Text* mName;
  Element* mDeleteButton;
  Element* mBackground;
};

//----------------------------------------------------------------- TagChainBase
class TagChainBase : public Composite
{
public:
  typedef TagChainBase LightningSelf;

  /// Constructor.
  TagChainBase(Composite* parent);

  virtual bool AddTag(StringParam tagName, bool removeable, bool sendsEvents = true);
  void GetTags(Array<String>& tags, bool includeNonRemoveable = true);
  void GetTags(HashSet<String>& tags, bool includeNonRemoveable = true);
  void ClearTags();

  /// Returns whether or not the given tag is contained in this tag chain.
  bool ContainsTag(StringParam tag);
  
  bool mSorted;
protected:
  void OnTagDeleted(TagEvent* e);
  void Modified();

  Array<TagLabel*> mTags;
};

//--------------------------------------------------------------------- TagChain
class TagChain : public TagChainBase
{
public:
  typedef TagChain LightningSelf;

  /// Constructor.
  TagChain(Composite* parent);

  /// Widget interface.
  void UpdateTransform() override;

  float GetDesiredHeight(Vec2Param& sizeConstraint);

private:
  Element* mBackground;
  Vec2 mLastSize;
};

//------------------------------------------------------------------- TagTextBox
DeclareEnum2(SearchIconSide, Left, Right);

class TagChainTextBox : public TagChainBase
{
public:
  typedef TagChainTextBox LightningSelf;

  /// Constructor.
  TagChainTextBox(Composite* parent);

  /// Widget interface.
  void UpdateTransform() override;
  Vec2 GetMinSize() override;

  bool AddTag(StringParam tagName, bool removeable, bool sendsEvents = true) override;
  void ClearSearch();
  void ClearTags();

  void Refresh();
  bool TakeFocusOverride() override;

  String GetText(){return mSearchBar->GetText();}

  void SetSearchIconSide(SearchIconSide::Type side);

  /// Active Search Data.
  SearchData mSearch;
  uint mSearchIndex;
  
  bool mAddTagsOnEnter;

  TextBox* mSearchBar;
private:
  void OnTagDeleted(TagEvent* e);

  void OnSearchBoxChanged(Event* e);
  void OnSearchBoxKeyPreview(KeyboardEvent* e);

  SearchIconSide::Type mSearchIconSide;
  Element* mMagnifyingGlassBg;
  Element* mMagnifyingGlass;
  String mLastSearchText;

  /// Results area.
  ScrollArea* mArea;
};

//-------------------------------------------------------------------- TagEditor
class TagEditor : public Composite
{
public:
  typedef TagEditor LightningSelf;

  /// Constructor.
  TagEditor(Composite* parent);

  /// Widget interface.
  void UpdateTransform() override;
  Vec2 Measure(LayoutArea& data) override;

  float GetDesiredHeight(Vec2Param& sizeConstraint);

  TagChain* GetTagChain();

  float GetAxisSize(SizeAxis::Enum axis);
  void SetAxisSize(SizeAxis::Enum axis, float size);

  void SetIsAnimating(bool state);

protected:
  /// Validates the given text as a tag and adds it.
  void SubmitText(StringParam text);

  virtual void Modified(){}

  /// Event response.
  void OnSearchBoxChanged(Event* e);
  void OnSearchBoxSubmitted(Event* e);

  bool mIsAnimating;
  TagChain* mTagChain;
  TextBox* mTextBox;
  IconButton* mAddButton;
};

//---------------------------------------------------------- Resource Tag Editor
class ResourceTagEditor : public TagEditor
{
public:
  typedef ResourceTagEditor LightningSelf;

  /// Constructor.
  ResourceTagEditor(Composite* parent);

  /// Edits the given content item.
  void EditResource(Resource* resource);
  void EditResources(Array<Resource*>& resources);

  void CleanTagEditor();

private:
  /// Saves the content item.
  void Modified();
  void OnTagDeleted(TagEvent* e);

  Array< HandleOf<Resource> > mResources;
};

}// namespace Plasma
