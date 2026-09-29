/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x && !y)return 1;
    if(!x)return 0;
    if(!y)return 0;
    else
    return !(x >> 31 ^ y >> 31);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int max = 0,shift = 0;
    shift = (v >> 16  > 0) << 4;
    v >>= shift;
    max |= shift;
    
    shift = (v >> 8  > 0) << 3; 
    v >>= shift;
    max |= shift;
    
    shift = (v >> 4 > 0) << 2;
    v >>= shift;
    max |= shift;

    shift = (v >> 2 > 0) << 1;
    v >>= shift;
    max |= shift;

    shift = (v >> 1 > 0);
    v >>= shift;
    max |= shift;
    return max;
}
/*
> 这些数字的二进制1 的位置互不重叠！
> 16: 10000
> 8 : 01000
> 4 : 00100
> 2 : 00010
> 1 : 00001

所以当它们做 | 运算，效果就等价于加法
max |= shift 就等于 max = max + shift
*/



/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17  
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int n_3 = n << 3;
    int m_3 = m << 3;
    int N_ = x >> n_3 & 0xff;
    int M_ = x >> m_3 & 0xff;
    int mask = ~ ((0xff << n_3) | (0xff << m_3));   //把待交换部分清零
    x = x & mask;
    x = (N_ << m_3) | x;
    x = (M_ << n_3) | x;
    return x;
}

/*kl
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    v = (v << 16) | (v >> 16);
    v = ((v & 0xff00ff00) >> 8) | ((v & 0x00ff00ff) << 8);
    v = ((v & 0xf0f0f0f0) >> 4) | ((v & 0x0f0f0f0f) << 4);
    v = ((v & 0xcccccccc) >> 2) | ((v & 0x33333333) << 2);
    v = ((v & 0xaaaaaaaa) >> 1) | ((v & 0x55555555) << 1);
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    x = 0xffffffff >> n & x >> n;
    return x;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int count = 0,shift = 0;
    shift = !(~(x >> 16) & 0x0000ffff) << 4;
    count += shift;
    x = x << shift;

    shift = !(~(x >> 24) & 0x000000ff) << 3;
    count += shift;
    x = x << shift;

    shift = !(~(x >> 28) & 0x0000000f) << 2;
    count += shift;
    x = x << shift;

    shift = !(~(x >> 30) & 0x00000003) << 1;
    count += shift;
    x = x << shift;

    shift = !(~(x >> 31) & 0x00000001);
    count += shift;
    x = x << shift;
    
    shift = !(~(x >> 31) & 0x00000001);
    count += shift;
    x = x << shift;
    return count;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
 unsigned float_i2f(int x) {
    unsigned sign;
    unsigned ux;
    unsigned frac;
    unsigned tail;
    int e;
    int shift;

    if (!x)
        return 0;

    sign = x & 0x80000000;
    ux = x;

    if (sign)
        ux = -x;

    /* 找最高位 1 */
    e = 31;
    while (!(ux & (1U << e)))
        e = e - 1;

    if (e > 23) {
        shift = e - 23;

        /* 被丢弃的低 shift 位 */
        tail = ux & ((1U << shift) - 1);

        /* 保留最高 24 位 */
        ux = ux >> shift;

        /*
         * 最近偶数舍入：
         *
         * tail >  1000... -> 进1
         * tail == 1000... 且 ux 为奇数 -> 进1
         *
         * 合并为：
         * tail + (ux & 1) > 2^(shift-1)
         */
        if (tail + (ux & 1) > (1U << (shift - 1)))
            ux = ux + 1;

        /*
         * 舍入后若产生第24位以上的进位，
         * 指数加1。
         */
        e = e + (ux >> 24);

        frac = ux & 0x7fffff;
    }
    else {
        frac = (ux << (23 - e)) & 0x7fffff;
    }

    return sign | ((e + 127) << 23) | frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned exp = (uf >> 23) & 0xff;
    unsigned sigh = (uf >> 31) << 31;
    unsigned frac = uf & 0x007fffff;
    if(exp == 0xff)return uf;
    if(exp == 0)return sigh | (frac << 1);
    exp += 1;
    if(exp == 0xff)return sigh | (0xff << 23);
    return sigh | (exp << 23) | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
 int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign;
    unsigned exp;
    unsigned mant_hi;
    unsigned val;
    int e;

    sign = uf2 >> 31;
    exp = (uf2 >> 20) & 0x7ff;

    /*
     * exp 最大只能是 0x7ff。
     * 所以 exp > 0x7fe
     * 等价于 exp == 0x7ff。
     *
     * 即 NaN 或 ±Infinity。
     */
    if (exp > 0x7fe)
        return 0x80000000u;

    e = exp - 1023;

    /* |x| < 1，向 0 截断得到 0 */
    if (e < 0)
        return 0;

    /* 超过 int 可以表示的范围 */
    if (e > 31)
        return 0x80000000u;

    /*
     * double：
     *
     * 1.FFFFFFFFF...
     *
     * uf2 低20位保存 fraction 的高20位。
     * 加回隐藏的 1。
     */
    mant_hi = (uf2 & 0xfffff) | 0x100000;

    /*
     * 如果 e <= 20：
     *
     * 整数部分全部位于：
     *
     * 1 + fraction高20位
     *
     * 中，不需要使用 uf1。
     */
    if (e <= 20) {
        val = mant_hi >> (20 - e);
    }
    else {
        /*
         * e > 20：
         *
         * 整数部分还需要 uf1 中的一部分。
         *
         * [mant_hi][uf1]
         *
         * mant_hi 左移 e-20，
         * uf1 取最高的 e-20 位。
         */
        val = (mant_hi << (e - 20))
            | (uf1 >> (52 - e));
    }

    /*
     * 此时已知 e <= 31。
     *
     * 所以 e > 30 就等价于 e == 31，
     * 不需要使用非法的 ==。
     */
    if (e > 30) {
        /*
         * 正数：
         * 2^31 及以上全部溢出。
         */
        if (!sign)
            return 0x80000000u;

        /*
         * 负数允许截断后的 magnitude 恰好是：
         *
         * 0x80000000
         *
         * 即 -2147483648。
         *
         * 如果低31位存在1，说明已经超过这个范围。
         */
        if (val & 0x7fffffff)
            return 0x80000000u;

        return 0x80000000u;
    }

    if (sign)
        return -val;

    return val;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x < -149)return 0;
    if(x >= 128)return 0x7f800000;
    if(x < -126)return 1U << (x + 149);
    int exp = x + 127;
    return(exp << 23);
}
