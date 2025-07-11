#pragma once

#include "types.h"

template <typename Scalar>
class StageConstraintBase {
public:
    virtual ~StageConstraintBase() = default;

    virtual Vector<Scalar> c(const Vector<Scalar>& x, const Vector<Scalar>& u) const = 0;
    virtual Matrix<Scalar> cx(const Vector<Scalar>& x, const Vector<Scalar>& u) const = 0;
    virtual Matrix<Scalar> cu(const Vector<Scalar>& x, const Vector<Scalar>& u) const = 0;

    virtual void setConstraintType(ConstraintType constraint_type) {
        this->constraint_type = constraint_type;
    };
    virtual void setDimC(int dim_c) {
        this->dim_c = dim_c;
    };

    virtual ConstraintType getConstraintType() const {
        return this->constraint_type;
    };
    virtual int getDimC() const {
        return this->dim_c;
    };


protected:
    ConstraintType constraint_type;
    int dim_c;
};