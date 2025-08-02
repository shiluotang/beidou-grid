#ifndef BEIDOU_GRID_PRINTABLE_H_INCLUDED
#define BEIDOU_GRID_PRINTABLE_H_INCLUDED

#include <iosfwd>

namespace beidou {
namespace grid {

class printable {
public:
    virtual
    ~printable();
    virtual
    void print(std::ostream&) const = 0;
protected:
private:
};

std::ostream& operator<<(std::ostream&, printable const&);

} // namespace grid
} // namespace beidou

#endif // BEIDOU_GRID_PRINTABLE_H_INCLUDED
