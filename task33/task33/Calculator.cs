using System.Runtime.InteropServices;

namespace task33
{
    public class Calculator
    {
        public long GetLcm(long x, long y)
        {
            if (x == 0 || y == 0) return 0;
            return Math.Abs(x * y) / GetGcd(x, y);
        }

        private long GetGcd(long x, long y)
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
