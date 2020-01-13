#pragma once

namespace Plasma
{

class DataNode;
struct DataTreeContext;

//------------------------------------------------------------ Data Tree Builder
class LegacyDataTreeParser
{
public:
  static DataNode* BuildTree(DataTreeContext& context, StringRange data);
};

}//namespace Plasma
