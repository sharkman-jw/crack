#ifndef _WW_MATRIX_H_
#define _WW_MATRIX_H_

#include <vector>
#include <stdexcept>
#include <iostream>

namespace ww {

template <typename T>
class Matrix
{
public:
    typedef T value_type;
    
    Matrix(size_t rows, size_t cols)
        : rows_(rows), cols_(cols), capacity_(rows*cols), data_(NULL)
    {
        if (capacity_)
            data_ = new value_type[capacity_];
    }
    Matrix(const Matrix& other)
        : rows_(other.rows_), cols_(other.cols_), capacity_(other.capacity_)
        , data_(NULL)
    {
        if (capacity_)
        {
            data_ = new value_type[capacity_];
            for (size_t i = 0; i < capacity_; ++ i)
                data_[i] = other.data_[i];
        }
    }
    Matrix& operator =(const Matrix& rhs)
    {
        if (this != &rhs)
        {
            if (rhs.capacity_ == capacity_) // No need to resize
            {
                // Skip
            }
            else
            {
                // Clear current data
                clear();
                // Resize
                if (rhs.capacity_)
                    data_ = new value_type[rhs.capacity_];
            }

            // Copy data
            rows_ = rhs.rows_;
            cols_ = rhs.cols_;
            capacity_ = rhs.capacity_;
            for (size_t i = 0; i < capacity_; ++ i)
                data_[i] = rhs.data_[i];
        }
        return *this;
    }
    ~Matrix()
    {
        if (data_ != NULL)
            delete [] data_;
    }
    bool operator==(const Matrix& rhs) const
    {
        if (this == &rhs)
            return true;
        if (rows_ != rhs.rows_ || cols_ != rhs.cols_)
            return false;
        if (capacity_ == 0)
            return true;
        
        for (size_t i = 0; i < capacity_; ++ i)
        {
            if (data_[i] != rhs.data_[i])
                return false;
        }
        return true;
    }
    
    //
    // Capacities & data access
    //
    
    size_t rows() const { return rows_; }
    size_t cols() const { return cols_; }
    
    const value_type& get(size_t r, size_t c) const
    {
        size_t pos = cols_*r + c;
        // Tolerate out of range r or c, as long as it's within capacity
        if (pos < capacity_)
            return data_[pos];
        throw std::runtime_error("Index out of range.");
    }
    
    //
    // Operations
    //
    void print() const
    {
        if (0 == capacity_)
            return;
        for (size_t pos = 0, c = 1; pos < capacity_; ++ pos, ++ c)
        {
            std::cout << data_[pos] << ' ';
            if (c == cols_)
            {
                std::cout << std::endl;
                c = 0;
            }
        }
    }
    
    //
    // Modifiers
    //
    
    void set(size_t r, size_t c, const value_type& val)
    {
        size_t pos = cols_*r + c;
        // Tolerate out of range r or c, as long as it's within capacity 
        if (pos < capacity_)
        {
            data_[pos] = val;
            return;
        }
        throw std::runtime_error("Index out of range.");
    }

    void clear()
    {
        if (data_ != NULL)
        {
            delete [] data_;
        }
        rows_ = cols_ = capacity_ = 0;
    }
    
    // Assign data from the starting row, col.
    // @param start_r: starting row
    // @param start_c: starting col
    // @param data: source data
    // @param n: number of values to be assigned; if this is 0, will try to
    //        assign till end. (Index out range error may happen if data is not
    //        long enough.)
    void assign(size_t start_r, size_t start_c, const value_type* data, size_t n=0)
    {
        size_t pos = cols_*start_r + start_c;
        // Tolerate out of range r or c, as long as it's within capacity 
        if (pos < capacity_)
        {
            size_t available_slots = capacity_ - pos;
            if (n > available_slots || 0 == n)
                n = available_slots;
            size_t i = 0;
            while (i < n)
                data_[pos++] = data[i++];
            return;
        }
        throw std::runtime_error("Index out of range.");
    }

    void rotate_ez(bool clockwise) // Use extra memory
    {
        if (NULL == data_ || (rows_ == 1) && (cols_ == 1))
            return;
        
        size_t r0 = 0;
        size_t c0 = 0;
        size_t r1 = 0;
        size_t c1 = 0;
        Matrix rotated(cols_, rows_);
        if (clockwise)
        {
            for (r0 = 0; r0 < rows_; ++ r0)
            {
                for (c0 = 0; c0 < cols_; ++ c0)
                {
                    r1 = c0;
                    c1 = rows_ - 1 - r0;
                    rotated.set(r1, c1, get(r0, c0));
                }
            }
        }
        else
        {
            for (r0 = 0; r0 < rows_; ++ r0)
            {
                for (c0 = 0; c0 < cols_; ++ c0)
                {
                    r1 = cols_ - 1 - c0;
                    c1 = r0;
                    rotated.set(r1, c1, get(r0, c0));
                }
            } 
        }
        this->operator=(rotated);
    }
    
    void rotate(bool clockwise) // Smaller additional memory
    {
        if ((rows_ < 2) && (cols_ < 2))
            return;
        
        std::vector<bool> set_flags(capacity_, false);
        size_t r0 = 0;
        size_t c0 = 0;
        size_t r1 = 0;
        size_t c1 = 0;
        size_t pos = 0;
        size_t round_start_pos = 0;
        size_t rows_minus_1 = rows_ - 1;
        size_t cols_minus_1 = cols_ - 1;
        value_type val_write(data_[0]);
        value_type val_cache(val_write); 
            // Has to init with something, in case there's no default ctor
        while (true)
        {
            if (clockwise)
            {
                r1 = c0;
                c1 = rows_minus_1 - r0;
            }
            else
            {
                r1 = cols_minus_1 - c0;
                c1 = r0;
            }
            pos = r1*rows_ + c1; // rows_ is the new cols_
            val_cache = data_[pos];

            data_[pos] = val_write;
            set_flags[pos] = true;
            
            if (pos == round_start_pos)
            {
                // Find the next unset slot
                while (round_start_pos < capacity_)
                {
                    if (!set_flags[round_start_pos])
                        break;
                    ++ round_start_pos;
                }
                if (round_start_pos == capacity_)
                    break; // All set
                // Found next open slot, calc coordinates
                r0 = round_start_pos/cols_;
                c0 = round_start_pos - r0*cols_;
                val_write = data_[round_start_pos];
            }
            else
            {
                r0 = pos/cols_;   
                c0 = pos - r0*cols_;
                val_write = val_cache;
            }
        }
        size_t tmp = rows_;
        rows_ = cols_;
        cols_ = tmp;
    }

private:
    size_t rows_;
    size_t cols_;
    size_t capacity_;
    value_type* data_;
};

}

#endif
