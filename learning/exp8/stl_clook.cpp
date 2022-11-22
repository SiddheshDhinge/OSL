#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, head;
    cin>>n>>head;
    vector<int> req(n);
    for(int i=0;i<n;i++)
        cin>>req[i];
    
    sort(req.begin(), req.end());

    vector<int> from, to;
    int seekTime = 0;
    auto mid = lower_bound(req.begin(), req.end(), head);

    for(auto it = mid; it != req.end(); it++)
    {
        from.push_back(head);
        to.push_back(*it);
        seekTime += abs(head - *it);
        head = *it;
    }

    for(auto it = req.begin(); it!=mid; it++)
    {
        from.push_back(head);
        to.push_back(*it);
        seekTime += abs(head - *it);
        head = *it;
    }

    for(int i: from)
        cout<<i<<" ";
    cout<<endl;
    for(int i: to)
        cout<<i<<" ";
    cout<<endl;
    cout<<seekTime<<endl;

    return 0;
}