#include "TColor_.h"
#include "TLine_.h"

class TRectangle_ {

public:
    TPoint_ x1_, x2_, x3_, x4_;
    TColor_ color_;

    TRectangle_():
        x1_({0, 0}), x2_({0, 0}), x3_({0, 0}), x4_({0, 0}), color_({1.0f, 1.0f, 1.0f}) {};

    TRectangle_()
    
};