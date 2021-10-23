#include <iostream>
using namespace std;

template<typename T>
class Grid {
private:
    T* memory;
    size_t x_size, y_size;

public:
    Grid(size_t x_size, size_t y_size) : x_size(x_size), y_size(y_size), memory(new T[x_size * y_size]) {}

    ~Grid() {
        delete[] memory;
    }

    Grid(Grid<T> const& old) : Grid(old.x_size, old.y_size) {  // конструктор копирования
        for (int i = 0; i < old.x_size * old.y_size;++i) {
            memory[i] = old.memory[i];
        }
    }

    
    Grid<T>& operator=(Grid<T> const &old) { //оператор копирующего присваивания
        T* new_memory = new T[old.x_size * y_size];
        for (int i = 0;i < old.y_size * old.x_size;++i) {
            new_memory[i] = old.memory[i];  
        }
        delete[] memory;
        memory = new_memory;
        return *this;
    }
    
    Grid(Grid<T> && old): memory(old.memory), x_size(x_size), y_size(y_size) { // конструктор перемещения
        delete[]old.memory;
    }

    Grid<T>& operator = (Grid<T>&& old) {  
        Grid<T> tmp(move(old));
        swap(this->memory, old.memory);
        swap(this->x_size, old.x_size);
        swap(this->y_size, old.y_size);
    }

    T operator()(size_t x_idx, size_t y_idx) const {
        return memory[x_size * (y_idx - 1) + x_idx - 1];
    }
    T& operator()(size_t x_idx, size_t y_idx) {
        return &memory[x_size * (y_idx - 1) + x_idx - 1];
    }

    Grid& operator=(T value) {
        for (int i = 0; i < x_size * y_size;++i) {
            memory[i] = value;
        }
        return *this;
    }

    size_t get_xsize() const {
        return x_size;
    }
    size_t get_ysize() const {
        return y_size;
    }

    friend ostream& operator<<(ostream& output, Grid const& g) {
        for (int i = 0; i < g.x_size * g.y_size;++i) {
            output << g.memory[i] << " ";
            if (i % g.x_size == g.x_size - 1) {
                output << endl;
            }
        }
        return output;
    }
    friend istream& operator>>(istream& input, Grid& g) {
        for (int i = 0; i < g.x_size * g.y_size;++i) {
            input >> g.memory[i];
        }
        return input;
    }
};


int main()
{
    Grid<int> g(3, 2);
    g = 7;
    cout << g << endl;
    Grid<int>g_1(g);
    cout << g_1 << endl;
    g_1 = 9;
    cout << g_1 << endl;
    g = g_1;
    cout << g_1;
    cout << g << endl;
    cin >> g;
    cout << g << endl;
}
