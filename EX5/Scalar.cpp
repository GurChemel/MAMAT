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
	return VarPtr(new Matrix(1,2,1));
};

VarPtr Scalar::Size(int dim) const {
	return VarPtr(new Scalar(1));
};

VarPtr Scalar::Transpose() const {
	return VarPtr(new Scalar(*this));
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

// ###############################################
// #
// #	Opertors: []
// #
// ###############################################

int& Scalar::operator[](int idx) {
	if (idx != 1) {	throw INDEX_OUT_OF_RANGE;}
	return Val_;
};

int& Scalar::operator[](IdxVec V) {
	if ((V[0] != 1) || (V[1] != 1)) { throw INDEX_OUT_OF_RANGE; }
	return Val_;
};

int Scalar::operator[](int idx) const{
	if (idx != 1) { throw INDEX_OUT_OF_RANGE; }
	return Val_;
};

int Scalar::operator[](IdxVec V) const{
	if ((V[0] != 1) || (V[1] != 1)) { throw INDEX_OUT_OF_RANGE; }
	return Val_;
};

// ###############################################
// #
// #	Opertors: + * 
// #
// ###############################################

VarPtr Scalar::operator+(const Variable& rhs) const {
	return rhs + (*this);
}

VarPtr Scalar::operator+(const Scalar& rhs) const {
	return VarPtr(new Scalar(rhs.Val_ + (*this).Val_));
}

VarPtr Scalar::operator+(const Matrix& rhs) const {
	VarPtr mat_size_vec = rhs.Size();
	VarPtr new_mat = rhs.Copy();
	int i;
	for (i=1 ; i<= ((*mat_size_vec)[1]*(*mat_size_vec)[2]) ; i++){
		(*new_mat)[i] += Val_;
	}
	return new_mat;
};

VarPtr Scalar::operator*(const Variable& rhs) const {
	return rhs * (*this);
}

VarPtr Scalar::operator*(const Scalar& rhs) const {
	return VarPtr(new Scalar(rhs.Val_ * (*this).Val_));
};

VarPtr Scalar::operator*(const Matrix& rhs) const {
	VarPtr mat_size_vec = rhs.Size();
	VarPtr new_mat = rhs.Copy();
	int i, j;
	for (i = 1; i <= (*mat_size_vec)[1]; i++) {
		for (j = 1; j <= (*mat_size_vec)[2]; j++) {
			IdxVec resIdx = { i,j };
			(*new_mat)[resIdx] = (*new_mat)[resIdx] * Val_;
		}
	}
	return new_mat;
};

// ###############################################
// #
// #	Opertors: > < ==
// #
// ###############################################

VarPtr Scalar::operator>(const Variable& rhs) const {
	return rhs < (*this);
}
VarPtr Scalar::operator<(const Variable& rhs) const {
	return rhs > (*this);
}
VarPtr Scalar::operator==(const Variable& rhs) const {
	return rhs == (*this);
}

VarPtr Scalar::operator>(const Scalar& rhs) const {
	return VarPtr(new Scalar(Val_ > rhs.Val_));
};

VarPtr Scalar::operator>(const Matrix& rhs) const {
	VarPtr mat_size_vec = rhs.Size();
	VarPtr new_mat = rhs.Copy();
	int i, j;
	cout << "s>m" << endl;
	for (i = 1; i <= (*mat_size_vec)[1]; i++) {
		for (j = 1; j <= (*mat_size_vec)[2]; j++) {
			IdxVec resIdx = { i,j };
			(*new_mat)[resIdx] = ((*new_mat)[resIdx] < Val_);
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
	cout << "s<m" << endl;
	for (i = 1; i <= (*mat_size_vec)[1]; i++) {
		for (j = 1; j <= (*mat_size_vec)[2]; j++) {
			IdxVec resIdx = { i,j };
			(*new_mat)[resIdx] = ((*new_mat)[resIdx] > Val_);
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
	for (i = 1; i <= (*mat_size_vec)[1]; i++) {
		for (j = 1; j <= (*mat_size_vec)[2]; j++) {
			IdxVec resIdx = { i,j };
			(*new_mat)[resIdx] = ((*new_mat)[resIdx] == Val_);
		}
	}
	return new_mat;
};

// ###############################################
// #
// #	Opertors: && ||
// #
// ###############################################

VarPtr Scalar::operator&&(const Variable& rhs) const {
	return rhs && (*this);
}
VarPtr Scalar::operator||(const Variable& rhs) const {
	return rhs || (*this);
}

VarPtr Scalar::operator&&(const Scalar& rhs) const {
	return VarPtr(new Scalar(Val_ && rhs.Val_));
};
VarPtr Scalar::operator&&(const Matrix&) const { throw BAD_INPUT; };

VarPtr Scalar::operator||(const Scalar& rhs) const {
	return VarPtr(new Scalar(Val_ || rhs.Val_));
};
VarPtr Scalar::operator||(const Matrix&) const { throw BAD_INPUT; };
