#include"Matrix.h"
#include"ScriptExceptions.h"

Matrix::Matrix(int rows, int cols, int val) {
	rows_ = rows;
	cols_ = cols;
	elements_num = rows_*cols_;
	Mat_ = new int[elements_num];
	
	int i;
	for (i = 0; i < elements_num; i++) {
		Mat_[i] = val;
	}

};

Matrix::Matrix(int startVal, int endVal) {
	rows_ = 1;
	if (endVal > startVal) {
		cols_ = endVal - startVal + 1;
	}
	else {
		cols_ = 0;
	}
	
	elements_num = rows_*cols_;
	Mat_ = new int[elements_num];

	int i, j;
	for (i = 0; i < rows_; i++) {
		for (j = 0; j < cols_; j++) {
			Mat_[i*cols_+j] = startVal + j;
		}
	}
	
};

Matrix::Matrix(const Matrix& from) {
	rows_ = from.rows_;
	cols_ = from.cols_;
	elements_num = from.elements_num;
	Mat_ = new int[elements_num];
	int i;
	for (i = 0; i < elements_num; i++) {
		Mat_[i] = from.Mat_[i];
	}
	/*for (i = 0; i < rows_; i++) {
		for (j = 0; j < cols_; j++) {
			Mat_[i*cols_+j] = from.Mat_[i*cols_+j];
		}
	}*/
};

VarPtr Matrix::Copy() const {
	VarPtr pRet = VarPtr(new Matrix(rows_, cols_ , 0));
	int i;
	for (i = 0; i < elements_num; i++) {
		(*pRet)[i+1] = Mat_[i];
	}
	return pRet;
};

VarPtr Matrix::NumElems() const {
	return VarPtr(new Scalar(elements_num));
};

VarPtr Matrix::Size() const {
	VarPtr pRet = VarPtr(new Matrix(1, 2, 0));
	IdxVec pos_vec = {1,1};
	(*pRet)[pos_vec] = rows_;
	pos_vec = {1,2};
	(*pRet)[pos_vec] = cols_;
	return pRet;
};

VarPtr Matrix::Size(int dim) const {
	if ((dim < 1) || (dim > 2)) { throw BAD_INPUT; };
	int size = (dim == 1 ? rows_ : cols_);
	return VarPtr(new Scalar(size));
};

VarPtr Matrix::Transpose() const {
	VarPtr pRet = VarPtr(new Matrix(cols_, rows_, 0));
	int i, row_num;
	for (i = 0 ; i < elements_num ; i++){
		row_num = i/cols_;
		(*pRet)[i+1] = Mat_[(i%cols_)*rows_+row_num];
	}
	return pRet;
};

VarPtr Matrix::Conv(VarPtr rhs) const
{
	if ((*NumElems())[1] == 0)
		return VarPtr(new Matrix(*this));
	if ((*(rhs->NumElems()))[1] == 0)
		return VarPtr(new Matrix(rows_, cols_, 0));

	VarPtr pRet = VarPtr(new Matrix(rows_, cols_, 0));
	VarPtr rhsSize = rhs->Size();
	int rhsRows = (*rhsSize)[1], rhsCols = (*rhsSize)[2];
	IdxVec rhsCenter = { (rhsRows / 2) + 1,(rhsCols / 2) + 1 };
	int maxRowShift = rhsRows - rhsCenter[0];
	int minRowShift = 1 - rhsCenter[0];
	int maxColShift = rhsCols - rhsCenter[1];
	int minColShift = 1 - rhsCenter[1];
	for (int resRow = 1; resRow <= rows_; ++resRow)
		for (int resCol = 1; resCol <= cols_; ++resCol)
		{
			IdxVec resIdx = { resRow,resCol };
			for (int rowShift = minRowShift; rowShift <= maxRowShift; ++rowShift)
				for (int colShift = minColShift; colShift <= maxColShift; ++colShift)
				{
					try
					{
						(*pRet)[resIdx] += ((*this)[resIdx + IdxVec{ -rowShift,-colShift }] * (*rhs)[rhsCenter + IdxVec{rowShift,colShift}]);
					}
					catch (...)
					{
						// convolution is zero padded (no action required)
					}
				}
		}
	return pRet;
}


int& Matrix::operator[](int idx) {
	return Mat_[idx-1];
};

int& Matrix::operator[](IdxVec V) {
	if ((V.size() != 2) || (V[0] < 1) || (V[0] > rows_) || (V[1] < 1) || (V[1] > cols_)) { throw INDEX_OUT_OF_RANGE; }
	return Mat_[(V[0]-1)+(V[1] - 1)*rows_];
};

int Matrix::operator[](int idx) const{
	return Mat_[idx-1];
};

int Matrix::operator[](IdxVec V) const {
	if ((V.size() != 2) || (V[0] < 1) || (V[0] > rows_) || (V[1] < 1) || (V[1] > cols_)) { throw INDEX_OUT_OF_RANGE; }
	return Mat_[(V[0]-1)+(V[1] - 1)*rows_];
};

VarPtr Matrix::operator+(const Variable& rhs) const {
	return rhs + (*this);
}

VarPtr Matrix::operator+(const Scalar& rhs) const {
	VarPtr pRet = VarPtr(new Matrix(*this));
	int i;
	for (i=1 ; i<= elements_num ; i++){
		(*pRet)[i] += rhs[1];
	}
	return pRet;
}

VarPtr Matrix::operator+(const Matrix& rhs) const {
	VarPtr pLhs_rows = rhs.Size(1);
	VarPtr pLhs_cols = rhs.Size(2);
	if ((rows_ != (*pLhs_rows)[1]) || (cols_ != (*pLhs_cols)[1])) { throw BAD_MAT_DIMS("+"); }
	
	VarPtr pRet = VarPtr(new Matrix(*this));
	int i;
	for (i=1 ; i<= elements_num ; i++){
		(*pRet)[i] += rhs[i];
	}
	return pRet;
};

VarPtr Matrix::operator*(const Variable& rhs) const {
	return rhs * (*this);
}

VarPtr Matrix::operator*(const Scalar& rhs) const {
	
	VarPtr pRet = VarPtr(new Matrix(*this));
	int i, j;

	for (i = 1; i <= rows_; i++) {
		for (j = 1; j <= cols_; j++) {
			IdxVec resIdx = { i,j };
			(*pRet)[resIdx] *= rhs[1];
		}
	}
	return pRet;
};

VarPtr Matrix::operator*(const Matrix& lhs) const {
	VarPtr pLhs_rows = lhs.Size(1);
	VarPtr pLhs_cols = lhs.Size(2);
	if (rows_ != (*pLhs_cols)[1]) { throw BAD_MAT_PROD; }

	VarPtr pRet = VarPtr(new Matrix( (*pLhs_rows)[1],cols_,0));
	int i, j, k;

	for (i = 1; i <= (*pLhs_rows)[1]; i++) {
		for (j = 1; j <= cols_; j++) {
			for (k = 1; k <= (*pLhs_cols)[1]; k++) {
				IdxVec resIdx = { i,j };
				IdxVec aIdx = { i,k };
				IdxVec bIdx = { k,j };
				(*pRet)[resIdx] += lhs[aIdx] * (*this)[bIdx];
			}
		}
	}
	return pRet;
};

VarPtr Matrix::operator>(const Variable& rhs) const {
	return rhs < (*this);
}
VarPtr Matrix::operator<(const Variable& rhs) const {
	return rhs > (*this);
}
VarPtr Matrix::operator==(const Variable& rhs) const {
	return rhs == (*this);
}
VarPtr Matrix::operator&&(const Variable& rhs) const {
	return rhs == (*this);
}
VarPtr Matrix::operator||(const Variable& rhs) const {
	return rhs == (*this);
}

VarPtr Matrix::operator>(const Scalar& rhs) const {
	VarPtr pRet = VarPtr(new Matrix(rows_,cols_,0));
	int i, j;

	for (i = 1; i <= rows_; i++) {
		for (j = 1; j <= cols_; j++) {
			IdxVec resIdx = { i,j };
			(*pRet)[resIdx] = ((*this)[resIdx] > rhs[1]);
		}
	}
	return pRet;
};

VarPtr Matrix::operator>(const Matrix& rhs) const {
	VarPtr pLhs_rows = rhs.Size(1);
	VarPtr pLhs_cols = rhs.Size(2);
	if ((rows_ != (*pLhs_rows)[1]) || (cols_ != (*pLhs_cols)[1])) { throw BAD_MAT_DIMS(">/<"); }
	VarPtr pRet = VarPtr(new Matrix(rows_, cols_, 0));
	int i, j;
	
	for (i = 1; i <= rows_; i++) {
		for (j = 1; j <= cols_; j++) {
			IdxVec resIdx = { i,j };
			(*pRet)[resIdx] = ((*this)[resIdx] > rhs[resIdx]);
		}
	}
	return pRet;
};

VarPtr Matrix::operator<(const Scalar& rhs) const {
	VarPtr pRet = VarPtr(new Matrix(rows_, cols_, 0));
	int i, j;

	for (i = 1; i <= rows_; i++) {
		for (j = 1; j <= cols_; j++) {
			IdxVec resIdx = { i,j };
			(*pRet)[resIdx] = ((*this)[resIdx] < rhs[1]);
		}
	}
	return pRet;
};

VarPtr Matrix::operator<(const Matrix& rhs) const {
	VarPtr pLhs_rows = rhs.Size(1);
	VarPtr pLhs_cols = rhs.Size(2);
	if ((rows_ != (*pLhs_rows)[1]) || (cols_ != (*pLhs_cols)[1])) { throw BAD_MAT_DIMS(">/<"); }
	VarPtr pRet = VarPtr(new Matrix(rows_, cols_, 0));
	int i, j;

	for (i = 1; i <= rows_; i++) {
		for (j = 1; j <= cols_; j++) {
			IdxVec resIdx = { i,j };
			(*pRet)[resIdx] = ((*this)[resIdx] < rhs[resIdx]);
		}
	}
	return pRet;
};

VarPtr Matrix::operator==(const Scalar& rhs) const {
	VarPtr pRet = VarPtr(new Matrix(rows_, cols_, 0));
	int i, j;

	for (i = 1; i <= rows_; i++) {
		for (j = 1; j <= cols_; j++) {
			IdxVec resIdx = { i,j };
			(*pRet)[resIdx] = ((*this)[resIdx] == rhs[1]);
		}
	}
	return pRet;
};

VarPtr Matrix::operator==(const Matrix& rhs) const {
	VarPtr pLhs_rows = rhs.Size(1);
	VarPtr pLhs_cols = rhs.Size(2);
	if ((rows_ != (*pLhs_rows)[1]) || (cols_ != (*pLhs_cols)[1])) { throw BAD_MAT_DIMS("=="); }
	VarPtr pRet = VarPtr(new Matrix(rows_, cols_, 0));
	int i, j;

	for (i = 1; i <= rows_; i++) {
		for (j = 1; j <= cols_; j++) {
			IdxVec resIdx = { i,j };
			(*pRet)[resIdx] = ((*this)[resIdx]==rhs[resIdx]);
		}
	}
	return pRet;
};

VarPtr Matrix::operator&&(const Scalar& rhs) const { throw BAD_INPUT; };
VarPtr Matrix::operator&&(const Matrix&) const { throw BAD_INPUT; };
VarPtr Matrix::operator||(const Scalar& rhs) const { throw BAD_INPUT; };
VarPtr Matrix::operator||(const Matrix&) const { throw BAD_INPUT; };
