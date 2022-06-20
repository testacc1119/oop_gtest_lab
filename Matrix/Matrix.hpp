
template<typename T>
class Matrix
{
public:
    // Consructors
    Matrix() : matrix{nullptr}, cols{0}, rows{0} {};
    Matrix(const Matrix & rhs); // copy
    Matrix(Matrix && lhs);      // move
    Matrix(size_t r, size_t c, T& val); // construct with basic value
    Matrix(size_t r, size_t c, T** arr);    // construct from 2D array
    // Destructor
    ~Matrix();

    // Interface
    T& at(size_t r, size_t c);  // direct acces to node
    size_t height() const;
    size_t width() const;
    Matrix transpose(); 
    Matrix submatrix(size_t r, size_t c);

    // For square matrixes only
    Matrix inverse();
    Matrix determinant();

    // Operator overloadings
    Matrix operator=(const Matrix & rhs);
    Matrix operator=(Matrix && lhs);
    Matrix operator+(const Matrix & right);
    Matrix operator-(const Matrix & right);

private:
    size_t rows;
    size_t cols;
    T** matrix;
};