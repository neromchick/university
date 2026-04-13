using System.Numerics;

namespace task33
{
    public class Calculator
    {
        public BigInteger GetLcm(BigInteger x, BigInteger y)
        {
            if (x == 0 || y == 0) return 0;
            BigInteger gcd = GetGcd(x, y);
            return BigInteger.Abs((x / gcd) * y);
        }

        private BigInteger GetGcd(BigInteger x, BigInteger y)
        {
            while (y != 0)
            {
                x %= y;
                (x, y) = (y, x);
            }
            return x;
        }
    }
}
