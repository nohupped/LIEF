/* Copyright 2017 R. Thomas
 * Copyright 2017 Quarkslab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "LIEF/ELF/DynamicEntryLibrary.hpp"

#include <iomanip>

namespace LIEF {
namespace ELF {

DynamicEntryLibrary::DynamicEntryLibrary(void) = default;
DynamicEntryLibrary& DynamicEntryLibrary::operator=(const DynamicEntryLibrary&) = default;
DynamicEntryLibrary::DynamicEntryLibrary(const DynamicEntryLibrary&) = default;

DynamicEntryLibrary::DynamicEntryLibrary(const Elf64_Dyn* header) :
  DynamicEntry{header}
{}


DynamicEntryLibrary::DynamicEntryLibrary(const Elf32_Dyn* header) :
  DynamicEntry{header}
{}

DynamicEntryLibrary::DynamicEntryLibrary(const std::string& name) :
  libname_{name}
{
  this->tag_   = DYNAMIC_TAGS::DT_NEEDED;
  this->value_ = 0;
}

const std::string& DynamicEntryLibrary::name(void) const {
  return this->libname_;
}


void DynamicEntryLibrary::name(const std::string& name) {
  this->libname_ = name;
}


void DynamicEntryLibrary::accept(Visitor& visitor) const {
  DynamicEntry::accept(visitor);
  visitor(*this); // Double dispatch to avoid down-casting
  visitor.visit(this->name());
}

std::ostream& DynamicEntryLibrary::print(std::ostream& os) const {

  DynamicEntry::print(os);
  os << std::hex
     << std::left
     << std::setw(10) << this->name();
  return os;

}
}
}



