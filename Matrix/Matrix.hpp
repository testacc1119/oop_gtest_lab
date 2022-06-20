#include <utility>

template<typename T>
class Matrix
{
public:
    // Consructors
    Matrix() : matrix{nullptr}, cols{0}, rows{0} {};
    Matrix(const Matrix & rhs); // copy
    Matrix(Matrix && lhs);      // move
    Matrix(unsigned r, unsigned c, const T& val); // construct with basic value
    Matrix(unsigned r, unsigned c, T** arr);    // construct from 2D array
    // Destructor
    ~Matrix();

    // Interface
    T& at(unsigned r, unsigned c);  // direct acces to node
    unsigned height() const;
    unsigned width() const;
    Matrix transpose() const; 
    Matrix submatrix(unsigned r, unsigned c) const;
    void clear();

    // For square matrixes only
    //Matrix inverse() const;
    //double determinant() const;

    // Operator overloadings
    Matrix& operator=(const Matrix & rhs);
    Matrix& operator=(Matrix && lhs);
    Matrix operator+(const Matrix & right) const;
    Matrix operator-(const Matrix & right) const;
    Matrix operator*(const Matrix & right) const;

    bool operator==(const Matrix & right);
    bool operator!=(const Matrix & right);

private:
    unsigned rows;
    unsigned cols;
    T** matrix;
};


//----------- Constructors --------------

template<typename T>
Matrix<T>::Matrix(const Matrix & rhs) : cols{rhs.cols}, rows{rhs.rows}
{
    this->matrix = new T*[rows];
    for(unsigned i = 0; i < rows; ++i)
    {
        this->matrix[i] = new T[cols];
        for(unsigned j = 0; j < cols; ++j)
        {
            this->matrix[i][j] = rhs.matrix[i][j];
        }
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix && lhs) : cols{lhs.cols}, rows{lhs.rows}
{
    this->matrix = lhs.matrix;
    lhs.matrix = nullptr;
}

template<typename T>
Matrix<T>::Matrix(unsigned r, unsigned c, const T& val) : cols{c}, rows{r}
{
    this->matrix = new T*[rows];
    for(unsigned i = 0; i < rows; ++i)
    {
        this->matrix[i] = new T[cols];
        for(unsigned j = 0; j < cols; ++j)
        {
            this->matrix[i][j] = val;
        }
    }
}

template<typename T>
Matrix<T>::Matrix(unsigned r, unsigned c, T** arr) : cols{c}, rows{r}
{
    this->matrix = new T*[rows];
    for(unsigned i = 0; i < rows; ++i)
    {
        this->matrix[i] = new T[cols];
        for(unsigned j = 0; j < cols; ++j)
        {
            this->matrix[i][j] = arr[i][j];
        }
    }
}

//=======================================

//----------- Destructor --------------

template<typename T>
Matrix<T>::~Matrix()
{
    this->clear();
}

//===================================

//----------- Interface --------------

template<typename T>
T& Matrix<T>::at(unsigned r, unsigned c)
{
    return this->matrix[r][c];
}

template<typename T>
unsigned Matrix<T>::height() const
{
    return this->rows;
}

template<typename T>
unsigned Matrix<T>::width() const
{
    return this->cols;
}

template<typename T>
Matrix<T> Matrix<T>::transpose() const
{
    Matrix temp;
    temp.cols = this->rows;
    temp.rows = this->cols;

    temp.matrix = new T*[temp.rows];
    for(unsigned i = 0; i < temp.rows; ++i)
    {
        temp.matrix[i] = new T[temp.cols];
        for(unsigned j = 0; j < temp.cols; ++j)
        {
            temp.matrix[i][j] = this->matrix[j][i];
        }
    }

    return std::move(temp);
}

template<typename T>
Matrix<T> Matrix<T>::submatrix(unsigned r, unsigned c) const
{   
    // r anc c are row anc column to delete
    if(r > rows - 1 || c > cols - 1)
        throw "r and c must be less than rows and cols";

    Matrix temp;
    temp.cols = this->cols - 1;
    temp.rows = this->rows - 1;

    temp.matrix = new T*[temp.rows];
    for(unsigned i = 0; i < rows; ++i)
    {
        temp.matrix[i] = new T[temp.cols];
        for(unsigned j = 0; j < cols; ++j)
        {
            if(i == r || j == c)
                continue;

            if(i > r)
            {
                if(j > c)
                    temp.matrix[i - 1][j - 1] = this->matrix[i][j];
                else
                    temp.matrix[i - 1][j] = this->matrix[i][j];
            }
            else if(j > c)
                temp.matrix[i][j - 1] = this->matrix[i][j];
            else
                temp.matrix[i][j] = this->matrix[i][j];
        }
    }

    return std::move(temp);
}

template<typename T>
void Matrix<T>::clear()
{
    if(this->matrix)
        for(unsigned i = 0; i < this->rows; ++i)
            if(this->matrix[i])
                delete[] this->matrix[i];
    
    this->rows = 0;
    this->cols = 0;
    this->matrix = nullptr;
}

//===================================

//----------- For square --------------



//=====================================


//----------- Operator overloading --------------

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix & rhs)
{
    this->clear();

    this->rows = rhs.rows;
    this->cols = rhs.cols;

    this->matrix = new T*[rows];
    for(unsigned i = 0; i < rows; ++i)
    {
        this->matrix[i] = new T[cols];
        for(unsigned j = 0; j < cols; ++j)
        {
            this->matrix[i][j] = rhs.matrix[i][j];
        }
    }

    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix && lhs)
{
    this->clear();

    this->rows = lhs.rows;
    this->cols = lhs.cols;

    this->matrix = lhs.matrix;
    lhs.matrix = nullptr;

    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix & right) const
{
    if(this->cols != right.cols || this->rows != right.rows)
        throw "Sum works only for matrixes of same size";
    
    Matrix temp;
    temp.cols = this->cols;
    temp.rows = this->rows;

    temp.matrix = new T*[temp.rows];
    for(unsigned i = 0; i < temp.rows; ++i)
    {
        temp.matrix[i] = new T[temp.cols];
        for(unsigned j = 0; j < temp.cols; ++j)
        {
            temp.matrix[i][j] = this->matrix[i][j] + right.matrix[i][j];
        }
    }

    return std::move(temp);
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix & right) const
{
    if(this->cols != right.cols || this->rows != right.rows)
        throw "Diff works only for matrixes of same size";
    
    Matrix temp;
    temp.cols = this->cols;
    temp.rows = this->rows;

    temp.matrix = new T*[temp.rows];
    for(unsigned i = 0; i < temp.rows; ++i)
    {
        temp.matrix[i] = new T[temp.cols];
        for(unsigned j = 0; j < temp.cols; ++j)
        {
            temp.matrix[i][j] = this->matrix[i][j] - right.matrix[i][j];
        }
    }

    return std::move(temp);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix & right) const
{
    if(this->cols != right.rows)
        throw "Multiply cannot be done";

    Matrix temp;
    temp.rows = this->rows;
    temp.cols = right.cols;

    temp.matrix = new T*[temp.rows];
    for(unsigned i = 0; i < temp.rows; ++i)
    {
        temp.matrix[i] = new T[temp.cols];
        for(unsigned j = 0; j < temp.cols; ++j)
        {
            temp.matrix[i][j] = T();
            for(unsigned k = 0; k < this->cols; ++k)
                temp.matrix[i][j] += this->matrix[i][k] + right.matrix[k][j];
        }
    }

    return std::move(temp);
}

template<typename T>
bool Matrix<T>::operator==(const Matrix & right)
{
    if(this->rows != right.rows || this->cols != right.cols)
        return false;

    for(unsigned i = 0; i < rows; ++i)
        for(unsigned j = 0; j < cols; ++j)
            if(this->matrix[i][j] != right.matrix[i][j])
                return false;

    return true;
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix & right)
{
    return !(*this == right);
}

//===============================================