L1-043 阅览室（20 分）
天梯图书阅览室请你编写一个简单的图书借阅统计程序。当读者借书时，管理员输入书号并按下S键，程序开始计时；当读者还书时，管理员输入书号并按下E键，程序结束计时。书号为不超过1000的正整数。当管理员将0作为书号输入时，表示一天工作结束，你的程序应输出当天的读者借书次数和平均阅读时间。

注意：由于线路偶尔会有故障，可能出现不完整的纪录，即只有S没有E，或者只有E没有S的纪录，系统应能自动忽略这种无效纪录。另外，题目保证书号是书的唯一标识，同一本书在任何时间区间内只可能被一位读者借阅。

输入格式：

输入在第一行给出一个正整数N（<= 10），随后给出N天的纪录。每天的纪录由若干次借阅操作组成，每次操作占一行，格式为：

书号（[1, 1000]内的整数） 键值（“S”或“E”） 发生时间（hh:mm，其中hh是[0,23]内的整数，mm是[0, 59]内整数）

每一天的纪录保证按时间递增的顺序给出。

输出格式：

对每天的纪录，在一行中输出当天的读者借书次数和平均阅读时间（以分钟为单位的精确到个位的整数时间）。

输入样例：
3
1 S 08:10
2 S 08:35
1 E 10:00
2 E 13:16
0 S 17:00
0 S 17:00
3 E 08:10
1 S 08:20
2 S 09:00
1 E 09:20
0 E 17:00

输出样例：
2 196
0 0
1 60

分析：模拟借书还书，输出当天借书次数和平均借书时间，四舍五入可以用加 0.5 然后强转成int，用isborrow数组标记书是否背借走
注意：如果出现连续两次借书，以第二次为成功借阅为成功借阅，（个人理解应该是第一次借书成功，第二次为非法借书，可题目只有按照第二次为借书成功计算）如果连续两次还书，以第一次还书为成功

#include <iostream>
#include <cstring>
using namespace std;
int main() {
    int n;
    cin >> n;
    int id, h, m, cnt = 0, sum = 0,  isborr[1010] = {0}, time[1010] = {0};
    char type, temp;
    for(int day = 0; day < n; ) {
        cin >> id >> type >> h >> temp >> m;
        if(id == 0) {
            if(cnt == 0)
                printf("0 0\n");
            else
                printf("%d %d\n", cnt, (int)(1.0 * sum / cnt + 0.5));
            day++;
            cnt = sum = 0;
            memset(isborr, 0, sizeof(isborr));
        }else if(type == 'S') {
            isborr[id] = 1;
            time[id] = h * 60 + m;
        }else if(type == 'E' && isborr[id] == 1) {
            isborr[id] = 0;
            sum += h * 60 + m - time[id];
            cnt++;
        }
    }
    return 0;
}