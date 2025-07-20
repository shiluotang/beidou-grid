#include <ostream>

#include "printable.h"

namespace org {

printable::~printable() {
}

void
printable::print(std::ostream &out) const {
}

std::ostream& operator<<(std::ostream &os, printable const &obj) {
    obj.print(os);
    return os;
}

} // namespace org
