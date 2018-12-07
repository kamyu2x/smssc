#if !defined(SPRITE_HEIGHT) || SPRITE_HEIGHT != 8 && SPRITE_HEIGHT != 16
#error "SPRITE_HEIGHT != 8 and SPRITE_HEIGHT != 16"
#endif

#if SPRITE_HEIGHT == 8
int
smssc8x8(int c_n1,
         const int r_x,
         const int r_y,
         const int *const r_mat,
         int  *c0_n,
         int **c0_x,
         int **c0_y)
#else
int
smssc8x16(int c_n1,
          const int r_x,
          const int r_y,
          const int *const r_mat,
          int  *c0_n,
          int **c0_x,
          int **c0_y)
#endif
{
    int x0 = INT_MAX;
    int y0 = INT_MAX;
    int x1 = -1;
    int y1 = -1;
    {
        {
            int x;
            int y;
            for (y = 0; y < r_y; y += 1)
            {
                for (x = 0; x < r_x; x += 1)
                {
                    if (r_mat[y*r_x + x])
                    {
                        if (x < x0) x0 = x;
                        if (x > x1) x1 = x;
                        if (y < y0) y0 = y;
                        if (y > y1) y1 = y;
                    }
                }
            }
            if (x1 == -1)
            {
                *c0_n = 0;
                *c0_x = NULL;
                *c0_y = NULL;
                return 0;
            }
        }
        {
            int t;
            for (t = 0; t < 256*34; t += 1) r_pat[t] = 0;
        }
        {
            unsigned u;
            const int c2 = (x1 - x0 + 8)/8;
            const int y2 = y1 - y0 + 1;
            int c;
            int i;
            int y;
            for (c = 0; c < c2; c += 1)
            {
                for (y = 0; y < y2; y += 1)
                {
                    u = 0;
                    for (i = 0; i < 8; i += 1)
                    {
                        if (x0 + 8*c + i >= r_x) break;
                        u |= (unsigned) (r_mat[(y0 + y)*r_x + x0 + 8*c + i] != 0) << (7 - i);
                    }
                    r_pat[256*(c + 1) + y] = u;
                }
            }
        }
    }
    const int ty = 256 + (y1 - y0 + 1);
    const int tx = (x1 - x0 + 8)/8*256 + (y1 - y0 + 1);
    const int dt = (x1 - x0 + 8)/8*256 - 1;
    unsigned u;
    unsigned v;
    int b;
    int c_n = 0;
    int i;
    int t0 = 256;
    int t1;
    c0_t[0] = -1;
    for (;;)
    {
        do
        {
            while (t0 < tx)
            {
                if (r_pat[t0] != 0) goto L1;
                t0 += 256;
            }
            t0 -= dt;
        }
        while (t0 < ty);
        {
            int c;
            for (c = 0; c < c_n; c += 1)
            {
                c0_t[c] = c_t[c];
                c0_i[c] = c_i[c];
            }
        }
        if (--c_n >= 0)
        {
            t0 = c_t[c_n];
            r_pat[t0     ] |= c_pat[c_n][0][ 0];
            r_pat[t0 +  1] |= c_pat[c_n][0][ 1];
            r_pat[t0 +  2] |= c_pat[c_n][0][ 2];
            r_pat[t0 +  3] |= c_pat[c_n][0][ 3];
            r_pat[t0 +  4] |= c_pat[c_n][0][ 4];
            r_pat[t0 +  5] |= c_pat[c_n][0][ 5];
            r_pat[t0 +  6] |= c_pat[c_n][0][ 6];
            r_pat[t0 +  7] |= c_pat[c_n][0][ 7];
#if SPRITE_HEIGHT == 16
            r_pat[t0 +  8] |= c_pat[c_n][0][ 8];
            r_pat[t0 +  9] |= c_pat[c_n][0][ 9];
            r_pat[t0 + 10] |= c_pat[c_n][0][10];
            r_pat[t0 + 11] |= c_pat[c_n][0][11];
            r_pat[t0 + 12] |= c_pat[c_n][0][12];
            r_pat[t0 + 13] |= c_pat[c_n][0][13];
            r_pat[t0 + 14] |= c_pat[c_n][0][14];
            r_pat[t0 + 15] |= c_pat[c_n][0][15];
#endif
            t0 += 256;
            r_pat[t0     ] |= c_pat[c_n][1][ 0];
            r_pat[t0 +  1] |= c_pat[c_n][1][ 1];
            r_pat[t0 +  2] |= c_pat[c_n][1][ 2];
            r_pat[t0 +  3] |= c_pat[c_n][1][ 3];
            r_pat[t0 +  4] |= c_pat[c_n][1][ 4];
            r_pat[t0 +  5] |= c_pat[c_n][1][ 5];
            r_pat[t0 +  6] |= c_pat[c_n][1][ 6];
            r_pat[t0 +  7] |= c_pat[c_n][1][ 7];
#if SPRITE_HEIGHT == 16
            r_pat[t0 +  8] |= c_pat[c_n][1][ 8];
            r_pat[t0 +  9] |= c_pat[c_n][1][ 9];
            r_pat[t0 + 10] |= c_pat[c_n][1][10];
            r_pat[t0 + 11] |= c_pat[c_n][1][11];
            r_pat[t0 + 12] |= c_pat[c_n][1][12];
            r_pat[t0 + 13] |= c_pat[c_n][1][13];
            r_pat[t0 + 14] |= c_pat[c_n][1][14];
            r_pat[t0 + 15] |= c_pat[c_n][1][15];
#endif
        }
        c_n1 = c_n;
        goto L2;
L1:     if (c_n < c_n1)
        {
            u = r_pat[t0];
            if      (u & 0x80)
            {
                t0 -= 256;
                i = 1;
            }
            else if (u & 0x40)
            {
                t0 -= 256;
                i = 2;
            }
            else if (u & 0x20)
            {
                t0 -= 256;
                i = 3;
            }
            else if (u & 0x10)
            {
                t0 -= 256;
                i = 4;
            }
            else if (u & 0x08)
            {
                t0 -= 256;
                i = 5;
            }
            else if (u & 0x04)
            {
                t0 -= 256;
                i = 6;
            }
            else if (u & 0x02)
            {
                t0 -= 256;
                i = 7;
            }
            else
                i = 0;
            for (u = 0x80 >> i;
                    !(r_pat[t0     ] & u)
                 && !(r_pat[t0 +  1] & u)
                 && !(r_pat[t0 +  2] & u)
                 && !(r_pat[t0 +  3] & u)
                 && !(r_pat[t0 +  4] & u)
                 && !(r_pat[t0 +  5] & u)
                 && !(r_pat[t0 +  6] & u)
                 && !(r_pat[t0 +  7] & u)
#if SPRITE_HEIGHT == 16
                 && !(r_pat[t0 +  8] & u)
                 && !(r_pat[t0 +  9] & u)
                 && !(r_pat[t0 + 10] & u)
                 && !(r_pat[t0 + 11] & u)
                 && !(r_pat[t0 + 12] & u)
                 && !(r_pat[t0 + 13] & u)
                 && !(r_pat[t0 + 14] & u)
                 && !(r_pat[t0 + 15] & u)
#endif
                 ; u >>= 1
                )
            {
                if (++i == 8)
                {
                    t0 += 256;
                    i = 0;
                    u = 0x100;
                }
            }
            c_t[c_n] = t0;
            c_i[c_n] = i;
            u = 0xFFU >> i;
            c_pat[c_n][0][ 0] = r_pat[t0     ] & u;  r_pat[t0     ] &= ~u;
            c_pat[c_n][0][ 1] = r_pat[t0 +  1] & u;  r_pat[t0 +  1] &= ~u;
            c_pat[c_n][0][ 2] = r_pat[t0 +  2] & u;  r_pat[t0 +  2] &= ~u;
            c_pat[c_n][0][ 3] = r_pat[t0 +  3] & u;  r_pat[t0 +  3] &= ~u;
            c_pat[c_n][0][ 4] = r_pat[t0 +  4] & u;  r_pat[t0 +  4] &= ~u;
            c_pat[c_n][0][ 5] = r_pat[t0 +  5] & u;  r_pat[t0 +  5] &= ~u;
            c_pat[c_n][0][ 6] = r_pat[t0 +  6] & u;  r_pat[t0 +  6] &= ~u;
            c_pat[c_n][0][ 7] = r_pat[t0 +  7] & u;  r_pat[t0 +  7] &= ~u;
#if SPRITE_HEIGHT == 16
            c_pat[c_n][0][ 8] = r_pat[t0 +  8] & u;  r_pat[t0 +  8] &= ~u;
            c_pat[c_n][0][ 9] = r_pat[t0 +  9] & u;  r_pat[t0 +  9] &= ~u;
            c_pat[c_n][0][10] = r_pat[t0 + 10] & u;  r_pat[t0 + 10] &= ~u;
            c_pat[c_n][0][11] = r_pat[t0 + 11] & u;  r_pat[t0 + 11] &= ~u;
            c_pat[c_n][0][12] = r_pat[t0 + 12] & u;  r_pat[t0 + 12] &= ~u;
            c_pat[c_n][0][13] = r_pat[t0 + 13] & u;  r_pat[t0 + 13] &= ~u;
            c_pat[c_n][0][14] = r_pat[t0 + 14] & u;  r_pat[t0 + 14] &= ~u;
            c_pat[c_n][0][15] = r_pat[t0 + 15] & u;  r_pat[t0 + 15] &= ~u;
#endif
            t0 += 256;
            u = 0xFF00U >> i;
            c_pat[c_n][1][ 0] = r_pat[t0     ] & u;  r_pat[t0     ] &= ~u;
            c_pat[c_n][1][ 1] = r_pat[t0 +  1] & u;  r_pat[t0 +  1] &= ~u;
            c_pat[c_n][1][ 2] = r_pat[t0 +  2] & u;  r_pat[t0 +  2] &= ~u;
            c_pat[c_n][1][ 3] = r_pat[t0 +  3] & u;  r_pat[t0 +  3] &= ~u;
            c_pat[c_n][1][ 4] = r_pat[t0 +  4] & u;  r_pat[t0 +  4] &= ~u;
            c_pat[c_n][1][ 5] = r_pat[t0 +  5] & u;  r_pat[t0 +  5] &= ~u;
            c_pat[c_n][1][ 6] = r_pat[t0 +  6] & u;  r_pat[t0 +  6] &= ~u;
            c_pat[c_n][1][ 7] = r_pat[t0 +  7] & u;  r_pat[t0 +  7] &= ~u;
#if SPRITE_HEIGHT == 16
            c_pat[c_n][1][ 8] = r_pat[t0 +  8] & u;  r_pat[t0 +  8] &= ~u;
            c_pat[c_n][1][ 9] = r_pat[t0 +  9] & u;  r_pat[t0 +  9] &= ~u;
            c_pat[c_n][1][10] = r_pat[t0 + 10] & u;  r_pat[t0 + 10] &= ~u;
            c_pat[c_n][1][11] = r_pat[t0 + 11] & u;  r_pat[t0 + 11] &= ~u;
            c_pat[c_n][1][12] = r_pat[t0 + 12] & u;  r_pat[t0 + 12] &= ~u;
            c_pat[c_n][1][13] = r_pat[t0 + 13] & u;  r_pat[t0 + 13] &= ~u;
            c_pat[c_n][1][14] = r_pat[t0 + 14] & u;  r_pat[t0 + 14] &= ~u;
            c_pat[c_n][1][15] = r_pat[t0 + 15] & u;  r_pat[t0 + 15] &= ~u;
#endif
            c_n += 1;
            continue;
        }
L2:     while (--c_n >= 0)
        {
            t0 = c_t[c_n];
            r_pat[t0     ] |= c_pat[c_n][0][ 0];
            r_pat[t0 +  1] |= c_pat[c_n][0][ 1];
            r_pat[t0 +  2] |= c_pat[c_n][0][ 2];
            r_pat[t0 +  3] |= c_pat[c_n][0][ 3];
            r_pat[t0 +  4] |= c_pat[c_n][0][ 4];
            r_pat[t0 +  5] |= c_pat[c_n][0][ 5];
            r_pat[t0 +  6] |= c_pat[c_n][0][ 6];
            r_pat[t0 +  7] |= c_pat[c_n][0][ 7];
#if SPRITE_HEIGHT == 16
            r_pat[t0 +  8] |= c_pat[c_n][0][ 8];
            r_pat[t0 +  9] |= c_pat[c_n][0][ 9];
            r_pat[t0 + 10] |= c_pat[c_n][0][10];
            r_pat[t0 + 11] |= c_pat[c_n][0][11];
            r_pat[t0 + 12] |= c_pat[c_n][0][12];
            r_pat[t0 + 13] |= c_pat[c_n][0][13];
            r_pat[t0 + 14] |= c_pat[c_n][0][14];
            r_pat[t0 + 15] |= c_pat[c_n][0][15];
#endif
            t0 += 256;
            r_pat[t0     ] |= c_pat[c_n][1][ 0];
            r_pat[t0 +  1] |= c_pat[c_n][1][ 1];
            r_pat[t0 +  2] |= c_pat[c_n][1][ 2];
            r_pat[t0 +  3] |= c_pat[c_n][1][ 3];
            r_pat[t0 +  4] |= c_pat[c_n][1][ 4];
            r_pat[t0 +  5] |= c_pat[c_n][1][ 5];
            r_pat[t0 +  6] |= c_pat[c_n][1][ 6];
            r_pat[t0 +  7] |= c_pat[c_n][1][ 7];
#if SPRITE_HEIGHT == 16
            r_pat[t0 +  8] |= c_pat[c_n][1][ 8];
            r_pat[t0 +  9] |= c_pat[c_n][1][ 9];
            r_pat[t0 + 10] |= c_pat[c_n][1][10];
            r_pat[t0 + 11] |= c_pat[c_n][1][11];
            r_pat[t0 + 12] |= c_pat[c_n][1][12];
            r_pat[t0 + 13] |= c_pat[c_n][1][13];
            r_pat[t0 + 14] |= c_pat[c_n][1][14];
            r_pat[t0 + 15] |= c_pat[c_n][1][15];
#endif
            t0 -= 256;
            i = c_i[c_n];
            u = 0x80U >> i;
            if (i == 0)
            {
                t1 = t0;
                v = 1;
            }
            else
            {
                t1 = t0 + 256;
                v = u<<1;
            }
            b = 0;
            while (!(u & r_pat[t0]))
            {
                if (++i == 8)
                {
                    t0 += 256;
                    i = 0;
                    u = 0x80;
                    v >>= 1;
                }
                else if (i == 1)
                {
                    t1 += 256;
                    u >>= 1;
                    v = 0x80;
                }
                else
                {
                    u >>= 1;
                    v >>= 1;
                }
                if (!b && (
                       r_pat[t1     ] & v
                    || r_pat[t1 +  1] & v
                    || r_pat[t1 +  2] & v
                    || r_pat[t1 +  3] & v
                    || r_pat[t1 +  4] & v
                    || r_pat[t1 +  5] & v
                    || r_pat[t1 +  6] & v
                    || r_pat[t1 +  7] & v
#if SPRITE_HEIGHT == 16
                    || r_pat[t1 +  8] & v
                    || r_pat[t1 +  9] & v
                    || r_pat[t1 + 10] & v
                    || r_pat[t1 + 11] & v
                    || r_pat[t1 + 12] & v
                    || r_pat[t1 + 13] & v
                    || r_pat[t1 + 14] & v
                    || r_pat[t1 + 15] & v
#endif
                   )) b = 1;
                if (b && (
                       r_pat[t0     ] & u
                    || r_pat[t0 +  1] & u
                    || r_pat[t0 +  2] & u
                    || r_pat[t0 +  3] & u
                    || r_pat[t0 +  4] & u
                    || r_pat[t0 +  5] & u
                    || r_pat[t0 +  6] & u
                    || r_pat[t0 +  7] & u
#if SPRITE_HEIGHT == 16
                    || r_pat[t0 +  8] & u
                    || r_pat[t0 +  9] & u
                    || r_pat[t0 + 10] & u
                    || r_pat[t0 + 11] & u
                    || r_pat[t0 + 12] & u
                    || r_pat[t0 + 13] & u
                    || r_pat[t0 + 14] & u
                    || r_pat[t0 + 15] & u
#endif
                   ))
                {
                    c_t[c_n] = t0;
                    c_i[c_n] = i;
                    u = 0xFFU >> i;
                    c_pat[c_n][0][ 0] = r_pat[t0     ] & u;  r_pat[t0     ] &= ~u;
                    c_pat[c_n][0][ 1] = r_pat[t0 +  1] & u;  r_pat[t0 +  1] &= ~u;
                    c_pat[c_n][0][ 2] = r_pat[t0 +  2] & u;  r_pat[t0 +  2] &= ~u;
                    c_pat[c_n][0][ 3] = r_pat[t0 +  3] & u;  r_pat[t0 +  3] &= ~u;
                    c_pat[c_n][0][ 4] = r_pat[t0 +  4] & u;  r_pat[t0 +  4] &= ~u;
                    c_pat[c_n][0][ 5] = r_pat[t0 +  5] & u;  r_pat[t0 +  5] &= ~u;
                    c_pat[c_n][0][ 6] = r_pat[t0 +  6] & u;  r_pat[t0 +  6] &= ~u;
                    c_pat[c_n][0][ 7] = r_pat[t0 +  7] & u;  r_pat[t0 +  7] &= ~u;
#if SPRITE_HEIGHT == 16
                    c_pat[c_n][0][ 8] = r_pat[t0 +  8] & u;  r_pat[t0 +  8] &= ~u;
                    c_pat[c_n][0][ 9] = r_pat[t0 +  9] & u;  r_pat[t0 +  9] &= ~u;
                    c_pat[c_n][0][10] = r_pat[t0 + 10] & u;  r_pat[t0 + 10] &= ~u;
                    c_pat[c_n][0][11] = r_pat[t0 + 11] & u;  r_pat[t0 + 11] &= ~u;
                    c_pat[c_n][0][12] = r_pat[t0 + 12] & u;  r_pat[t0 + 12] &= ~u;
                    c_pat[c_n][0][13] = r_pat[t0 + 13] & u;  r_pat[t0 + 13] &= ~u;
                    c_pat[c_n][0][14] = r_pat[t0 + 14] & u;  r_pat[t0 + 14] &= ~u;
                    c_pat[c_n][0][15] = r_pat[t0 + 15] & u;  r_pat[t0 + 15] &= ~u;
#endif
                    t0 += 256;
                    u = 0xFF00U >> i;
                    c_pat[c_n][1][ 0] = r_pat[t0     ] & u;  r_pat[t0     ] &= ~u;
                    c_pat[c_n][1][ 1] = r_pat[t0 +  1] & u;  r_pat[t0 +  1] &= ~u;
                    c_pat[c_n][1][ 2] = r_pat[t0 +  2] & u;  r_pat[t0 +  2] &= ~u;
                    c_pat[c_n][1][ 3] = r_pat[t0 +  3] & u;  r_pat[t0 +  3] &= ~u;
                    c_pat[c_n][1][ 4] = r_pat[t0 +  4] & u;  r_pat[t0 +  4] &= ~u;
                    c_pat[c_n][1][ 5] = r_pat[t0 +  5] & u;  r_pat[t0 +  5] &= ~u;
                    c_pat[c_n][1][ 6] = r_pat[t0 +  6] & u;  r_pat[t0 +  6] &= ~u;
                    c_pat[c_n][1][ 7] = r_pat[t0 +  7] & u;  r_pat[t0 +  7] &= ~u;
#if SPRITE_HEIGHT == 16
                    c_pat[c_n][1][ 8] = r_pat[t0 +  8] & u;  r_pat[t0 +  8] &= ~u;
                    c_pat[c_n][1][ 9] = r_pat[t0 +  9] & u;  r_pat[t0 +  9] &= ~u;
                    c_pat[c_n][1][10] = r_pat[t0 + 10] & u;  r_pat[t0 + 10] &= ~u;
                    c_pat[c_n][1][11] = r_pat[t0 + 11] & u;  r_pat[t0 + 11] &= ~u;
                    c_pat[c_n][1][12] = r_pat[t0 + 12] & u;  r_pat[t0 + 12] &= ~u;
                    c_pat[c_n][1][13] = r_pat[t0 + 13] & u;  r_pat[t0 + 13] &= ~u;
                    c_pat[c_n][1][14] = r_pat[t0 + 14] & u;  r_pat[t0 + 14] &= ~u;
                    c_pat[c_n][1][15] = r_pat[t0 + 15] & u;  r_pat[t0 + 15] &= ~u;
#endif
                    c_n += 1;
                    goto L3;
                }
            }
        }
        break;
L3:     ;        
    }
    c_n1 += 1;
    if (c_n1 == 0 || c0_t[0] == -1)
    {
        *c0_n = 0;
        *c0_x = NULL;
        *c0_y = NULL;
        return 0;
    }
    *c0_n = c_n1;
    *c0_x = malloc(c_n1*sizeof(int));
    if (*c0_x == NULL) return 1;
    *c0_y = malloc(c_n1*sizeof(int));
    if (*c0_y == NULL)
    {
        free(*c0_x);
        return 1;
    }
    {
        unsigned u;
        int c;
        for (c = 0; c < c_n1; c += 1)
        {
            (*c0_x)[c] = x0 + (c0_t[c]/256 - 1)*8 + c0_i[c];
            (*c0_y)[c] = y0 + (c0_t[c] & 0xFF);
        }
    }
    return 0;
}
