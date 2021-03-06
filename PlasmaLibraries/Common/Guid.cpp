#include "Precompiled.hpp"
#include "Containers/Hashing.hpp"
#include "Utility/Guid.hpp"

namespace Plasma
{

size_t Guid::Hash() const
{
  return HashPolicy<u64>()(mValue);
}

}
