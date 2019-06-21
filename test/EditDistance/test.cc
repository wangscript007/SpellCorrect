#include "EditDistance.h"

using namespace wd;

void test()
{
    string a , b;
    cin >> a>>b;
    EditDistance t(a, b);
    cout << t.work() << endl;
}

int main()
{
    test();
    return 0;
}
