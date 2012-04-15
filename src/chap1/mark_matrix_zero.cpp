#include "mark_matrix_zero.h"

void mark_matrix_zero(ww::Matrix<int>& m)
{
    size_t r = 0;
    size_t c = 0;
    std::vector<bool> mark_row(m.rows(), false);
    std::vector<bool> mark_col(m.cols(), false);
    for (r = 0; r < m.rows(); ++ r)
    {
        for (c = 0; c < m.cols(); ++ c)
        {
            if (0 == m.get(r, c))
            {
                mark_row[r] = true;
                mark_col[c] = true;
            }
        }
    }
    
    for (r = 0; r < m.rows(); ++ r)
    {
        for (c = 0; c < m.cols(); ++ c)
        {
            if (mark_col[c] || mark_row[r])
                m.set(r, c, 0);
        }
    }
}
