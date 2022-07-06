#include <vector>
#include <cmath>

class VectorSorter
{
    private:
    std::vector<int> vec;

public:
    // Consructors
    VectorSorter() {};
    VectorSorter(const std::vector<int> &v) {vec = v;};
    VectorSorter(const VectorSorter &vecsort) {vec = vecsort.vec;};

    // Functions
    int& at(size_t);
    size_t size() const;
    std::vector<int> get_vec() const { return vec; };
    void set_vec(std::vector<int> v) { vec = v;};
    void bubblesort();
    void ins_sort();

    // Operators
    VectorSorter& operator=(const VectorSorter&);
};

//----------- Functions --------------

int& VectorSorter::at(size_t index)
{
    return this->vec[index];
}


size_t VectorSorter::size() const
{
    return this->vec.size();
}
//----------------------------------------------------------------

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}
//----------------------------------------------------------------

void VectorSorter::bubblesort()
{
    unsigned counter = 0;
    for(int i = 0; i < this->vec.size() - 1; ++i){
        for(int j = 0; j < this->vec.size() - 1; ++j)
            if(this->vec[j] > this->vec[j+1]){
                swap(this->vec[j], this->vec[j+1]);
                counter++;
            }
    }
    if(counter == 0) 
        return;
    else counter = 0;
}

void VectorSorter::ins_sort()
{
    int key, j;
    for (int i = 1; i < vec.size(); ++i) {
        key = vec[i];
        j = i - 1;

        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            --j;
        }
        vec[j+1] = key;
    }
}