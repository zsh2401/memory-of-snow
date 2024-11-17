#include <ml.h>
Scalar ML_F_ReLU(Scalar x){
    return x > 0 ? x : 0;
}
// Scalar ML_F_Mut()