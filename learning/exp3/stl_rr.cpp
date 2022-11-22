#include <bits/stdc++.h>
using namespace std;

typedef struct process
{
    int pid, at, bt, ct, tat, wt;
}process;

bool cSort(process &a, process &b)
{
    if(a.at < b.at)
        return true;
    return false;
}

int main()
{
    int n, tq;
    cin>>n>>tq;
    vector<process> arr(n);
    for(int i=0;i<n;i++)
    {
        arr[i].pid = i;
        cin>>arr[i].at;
    }

    for(int i=0;i<n;i++)
        cin>>arr[i].bt;

    queue<process> que;
    vector<pair<int, int>> gantt;
    sort(arr.begin(), arr.end(), cSort);

    que.push(arr[0]);
    int nextP = 1;
    while(que.size())
    {
        process exe = que.front();
        que.pop();

        int executionTime = min(exe.bt, tq);
        exe.bt -= executionTime;
        
        for(int i=0;i<executionTime;i++)
            gantt.push_back({exe.pid, exe.at});

        while(nextP < n)
        {
            if(arr[nextP].at <= gantt.size() && arr[nextP].bt > 0)
                que.push(arr[nextP]);
            else
                break;
            nextP++;
        }
        
        if(exe.bt > 0)
            que.push(exe);
    }
    for(int i = 0, j = 0; i<gantt.size(); i++, j++)
    {
        if(gantt[i].second > j)
            cout<<"-1 ";
        else
            cout<<gantt[i].first +1<<" ";
    }
    cout<<endl;

    return 0;
}