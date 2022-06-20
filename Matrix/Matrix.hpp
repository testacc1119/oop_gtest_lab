template<typename T>
class Matrix
{
public:
    // Consructors
    Matrix() : matrix{nullptr}, cols{0}, rows{0} {};
    Matrix(const Matrix & rhs); // copy
    Matrix(Matrix && lhs);      // move
    Matrix(unsigned r, unsigned c, T& val); // construct with basic value
    Matrix(unsigned r, unsigned c, T** arr);    // construct from 2D array
    // Destructor
    ~Matrix();

    // Interface
    T& at(unsigned r, unsigned c);  // direct acces to node
    unsigned height() const;
    unsigned width() const;
    Matrix transpose(); 
    Matrix submatrix(unsigned r, unsigned c);

    // For square matrixes only
    Matrix inverse();
    double determinant();

    // Operator overloadings
    Matrix operator=(const Matrix & rhs);
    Matrix operator=(Matrix && lhs);
    Matrix operator+(const Matrix & right);
    Matrix operator-(const Matrix & right);
    Matrix operator*(const Matrix & right);

private:
    unsigned rows;
    unsigned cols;
    T** matrix;
};


//--------- Constructors --------------

template<typename T>
Matrix<T>::Matrix(const Matrix & rhs) : cols{rhs.cols}, rows{rhs.rows}
{
    this->matrix = new T*[rows];
    for(unsigned i = 0; i < rows; ++i)
    {
        this->matrix[i] = new T[cols];
        for(unsigned j = 0; i < cols; ++j)
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
Matrix<T>::Matrix(unsigned r, unsigned c, T& val) : cols{c}, rows{r}
{
    this->matrix = new T*[rows];
    for(unsigned i = 0; i < rows; ++i)
    {
        this->matrix[i] = new T[cols];
        for(unsigned j = 0; i < cols; ++j)
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
        for(unsigned j = 0; i < cols; ++j)
        {
            this->matrix[i][j] = arr[i][j];
        }
    }
}

//=====================================

//--------- Destructor --------------

template<typename T>
Matrix<T>::~Matrix()
{
    if(this->matrix)
        delete this->matrix
}

//===================================