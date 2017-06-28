#include"Scalar.h"
#include"Matrix.h"
#include"ScriptExceptions.h"

using namespace std;

VarPtr Scalar::Copy() const {
	return VarPtr(new Scalar(*this));
};

VarPtr Scalar::NumElems() const {
	return VarPtr(new Scalar(1));
};

VarPtr Scalar::Size() const {
	return VarPtr(new Matrix(1,1,1));
};

VarPtr Scalar::Size(int dim) const {
	return VarPtr(new Scalar(1));
};


VarPtr Scalar::Conv(VarPtr rhs) const
{
	if ((*(rhs->NumElems()))[1] == 0)
		return VarPtr(new Scalar(0));
	VarPtr pRet = VarPtr(new Scalar(*this));
	VarPtr rhsSize = rhs->Size();
	int rhsRows = (*rhsSize)[1], rhsCols = (*rhsSize)[2];
	IdxVec rhsCenter = { (rhsRows / 2) + 1,(rhsCols / 2) + 1 };
	(*pRet)[1] *= (*rhs)[rhsCenter];
	return pRet;
}

int& Scalar::operator[](int idx) {
	if (idx != 1) {	throw INDEX_OUT_OF_RANGE;}
	return Val_;
};

int& Scalar::operator[](IdxVec V) {
	if ((V[0] != 1) || (V[1] != 1)) { throw INDEX_OUT_OF_RANGE; }
	return Val_;
};

//VarPtr Scalar::operator+(const Variable& rhs) const {
	//return VarPtr(new Scalar(rhs[1] + (*this).Val_));		// TODO: Fix this one..
//}

VarPtr Scalar::operator+(const Scalar& rhs) const {
	return VarPtr(new Scalar(rhs.Val_ + (*this).Val_));
}

VarPtr Scalar::operator+(const Matrix& rhs) const {
	VarPtr mat_size_vec = rhs.Size();
	VarPtr new_mat = rhs.Copy();
	int i, j;
	IdxVec pos_vec;
	for (i = 1; i <= (*mat_size_vec)[1]; i++) {
		for (j = 1; j <= (*mat_size_vec)[2]; j++) {
			pos_vec[0] = i;
			pos_vec[1] = j;
			(*new_mat)[pos_vec] += Val_;
		}
	}
	return new_mat;
};

VarPtr Scalar::operator*(const Scalar& rhs) const {
	return VarPtr(new Scalar(rhs.Val_ * (*this).Val_));
};

VarPtr Scalar::operator*(const Matrix& rhs) const {
	VarPtr mat_size_vec = rhs.Size();
	VarPtr new_mat = rhs.Copy();
	int i, j;
	IdxVec pos_vec;
	for (i = 1; i <= (*mat_size_vec)[1]; i++) {
		for (j = 1; j <= (*mat_size_vec)[2]; j++) {
			pos_vec[0] = i;
			pos_vec[1] = j;
			(*new_mat)[pos_vec] = (*new_mat)[pos_vec] * Val_;
		}
	}
	return new_mat;
};

VarPtr Scalar::operator>(const Scalar& rhs) const {
	return VarPtr(new Scalar(Val_ > rhs.Val_));
};

VarPtr Scalar::operator>(const Matrix& rhs) const {
	VarPtr mat_size_vec = rhs.Size();
	VarPtr new_mat = rhs.Copy();
	int i, j;
	IdxVec pos_vec;
	for (i = 1; i <= (*mat_size_vec)[1]; i++) {
		for (j = 1; j <= (*mat_size_vec)[2]; j++) {
			pos_vec[0] = i;
			pos_vec[1] = j;
			(*new_mat)[pos_vec] = ((*new_mat)[pos_vec] > Val_);
		}
	}
	return new_mat;
};

VarPtr Scalar::operator<(const Scalar& rhs) const {
	return VarPtr(new Scalar(Val_ < rhs.Val_));
};

VarPtr Scalar::operator<(const Matrix& rhs) const {
	VarPtr mat_size_vec = rhs.Size();
	VarPtr new_mat = rhs.Copy();
	int i, j;
	IdxVec pos_vec;
	for (i = 1; i <= (*mat_size_vec)[1]; i++) {
		for (j = 1; j <= (*mat_size_vec)[2]; j++) {
			pos_vec[0] = i;
			pos_vec[1] = j;
			(*new_mat)[pos_vec] = ((*new_mat)[pos_vec] < Val_);
		}
	}
	return new_mat;
};

VarPtr Scalar::operator==(const Scalar& rhs) const {
	return VarPtr(new Scalar(Val_ == rhs.Val_));
};

VarPtr Scalar::operator==(const Matrix& rhs) const {
	VarPtr mat_size_vec = rhs.Size();
	VarPtr new_mat = rhs.Copy();
	int i, j;
	IdxVec pos_vec;
	for (i = 1; i <= (*mat_size_vec)[1]; i++) {
		for (j = 1; j <= (*mat_size_vec)[2]; j++) {
			pos_vec[0] = i;
			pos_vec[1] = j;
			(*new_mat)[pos_vec] = ((*new_mat)[pos_vec] == Val_);
		}
	}
	return new_mat;
};

VarPtr Scalar::operator&&(const Scalar& rhs) const {
	return VarPtr(new Scalar(Val_ && rhs.Val_));
};
VarPtr Scalar::operator&&(const Matrix&) const { throw BAD_INPUT; };

VarPtr Scalar::operator||(const Scalar& rhs) const {
	return VarPtr(new Scalar(Val_ || rhs.Val_));
};
VarPtr Scalar::operator||(const Matrix&) const { throw BAD_INPUT; };
