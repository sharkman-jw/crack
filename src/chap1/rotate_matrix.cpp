#include <iostream>
#include "rotate_matrix.h"

static inline void set_matrix_val(int* data, size_t n, size_t r, size_t c, int val)
{
    data[r*n + c] = val;
}

static inline int get_matrix_val(int* data, size_t n, size_t r, size_t c)
{
    return data[r*n + c];
}

void rotate_matrix_ez(int* data, size_t n, bool clockwise)
{
    if (NULL == data || n < 2)
        return;
    
    size_t r0 = 0;
    size_t c0 = 0;
    size_t r1 = 0;
    size_t c1 = 0;
    int* new_data = new int[n*n];
    if (clockwise)
    {
        for (r0 = 0; r0 < n; ++ r0)
        {
            for (c0 = 0; c0 < n; ++ c0)
            {
                r1 = c0;
                c1 = n - 1 - r0;
                set_matrix_val(new_data, n, r1, c1,
                    get_matrix_val(data, n, r0, c0));
            }
        }
    }
    else
    {
        for (r0 = 0; r0 < n; ++ r0)
        {
            for (c0 = 0; c0 < n; ++ c0)
            {
                r1 = n- 1 - c0;
                c1 = r0;
                set_matrix_val(new_data, n, r1, c1,
                    get_matrix_val(data, n, r0, c0));
            }
        }
    }
    // Copy data back
    for (r0 = 0; r0 < n; ++ r0)
    {
        for (c0 = 0; c0 < n; ++ c0)
        {
            set_matrix_val(data, n, r0, c0,
                get_matrix_val(new_data, n, r0, c0));
        }
    }
    
    delete [] new_data;
    new_data = NULL;
}

// 7:28
void rotate_matrix(int* data, size_t n, bool clockwise)
{
    if (NULL == data || n < 2)
        return;
        
    size_t rounds = n/2; // 1 round for 2x2, 3x3 (skip the last 1x1 squre)
    size_t turns = n - 1;
    size_t i_turn = 0;
    size_t i_switch = 0;
    size_t round_start_r = 0;
    size_t round_start_c = 0;
    size_t r0 = 0;
    size_t c0 = 0;
    size_t r1 = 0;
    size_t c1 = 0;
    int val_cache = 0;
    int val_write = 0;
    for (size_t i_round = 0; i_round < rounds; ++ i_round)
    {
        r0 = round_start_r;
        c0 = round_start_c;
        for (i_turn = 0; i_turn < turns; ++ i_turn)
        {
            // Rotate values on 4 positions
            val_write = get_matrix_val(data, n, r0, c0);
            for (i_switch = 0; i_switch < 4; ++ i_switch)
            {
                if (clockwise)
                {
                    r1 = c0;
                    c1 = n - 1 - r0;
                }
                else
                {
                    r1 = n - 1 - c0;
                    c1 = r0;
                }
                val_cache = get_matrix_val(data, n, r1, c1);
                set_matrix_val(data, n, r1, c1, val_write);
                val_write = val_cache;
                r0 = r1;
                c0 = c1;
            }
            ++ c0;
        }
        turns -= 2;
        ++ round_start_r;
        ++ round_start_c;
    }
}
// 7:38
