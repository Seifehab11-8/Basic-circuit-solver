#include <iostream>
#include <string>
#include <vector>
using namespace std;
double gapdetect(string gap, int ie, int i)
{
    int End = i;
    float Req = 0, Req2 = 0;
    string R = "";
    for (int j = i + 2; i <= ie;)
    {
        R = "";
        if (gap[j] == ' ')
            j++;
        if (gap[j] == 'e' || gap[j] == 'E')
            break;
        while (gap[j] != ' ')
        {
            R = R + gap[j];
            j++;
        }
        Req = Req + stof(R);
        Req2 = Req2 + 1 / stof(R);
    }
    if (gap[End] == 'S')
        return Req;
    if (gap[End] == 'P')
        return 1 / Req2;

    return 0;
}
int main()
{
    int ie = 1, is = 0, ip = 0, flag = 0, done = 0, i = 0, flag2 = 0, flag3 = 0;
    int flag4 = 0;
    vector<float> Rtotal;
    string circuit_descripVon;
    float V, rs1, rs2, rtotalp = 0, rtotals = 0;
    cout << "Circuit Descripton: ";
    getline(cin, circuit_descripVon);
    cout << "Voltage Applied: ";
    cin >> V;
    string R = "";
    while (!done)
    {
        for (int kk = 0; kk <= circuit_descripVon.length(); kk++)
        {
            if (circuit_descripVon[kk] == ('e') || circuit_descripVon[kk] == ('E'))
                flag3++;
            if (circuit_descripVon[kk] == ('S') || circuit_descripVon[kk] == ('P'))
                flag4++;
        }
        if (flag3 != flag4)
        {
            cout << "wrong circuit descripVon";
            break;
        }
        for (; ie != 0; ie++)
        {
            if (circuit_descripVon[ie] == 'E')
            {
                flag = 1;
                break;
            }
            if (circuit_descripVon[ie] == 'e')
                break;
        }
        is = ie;
        for (; is > 0; is--)
        {
            if (circuit_descripVon[is] == 'P')
                break;
            if (circuit_descripVon[is] == 'S')
            {
                Rtotal.push_back(gapdetect(circuit_descripVon, ie, is));
                i++;
                circuit_descripVon.erase(is, ie - is + 1);
                ie = 0;
                break;
            }
        }
        ip = ie;
        for (; ip > 0; ip--)
        {
            if (circuit_descripVon[ip] == 'S')
                break;
            if (circuit_descripVon[ip] == 'P')
            {
                Rtotal.push_back(gapdetect(circuit_descripVon, ie, is));
                i++;
                circuit_descripVon.erase(ip, ie - ip + 1);
                ie = 0;
                break;
            }
        }
        ip = 0;
        is = 0;
        ie = 1;
        if (flag == 1)
        {
            for (int j = 1; j < 100;)
            {
                R = "";
                if (circuit_descripVon[j] == ' ')
                    j++;
                if (circuit_descripVon[j] == 'E')
                    break;
                while (circuit_descripVon[j] != ' ')
                {
                    R = R + circuit_descripVon[j];
                    j++;
                    flag2++;
                }
                if (flag2 != 0)
                {
                    Rtotal.push_back(stof(R));
                    i++;
                }
                flag2 = 0;
            }
            done = true;
        }
    }
    if (flag4 == flag3)
    {
        if (circuit_descripVon[0] == 'P')
        {
            for (int h = 0; h < Rtotal.size(); h++)
            {
                rtotalp = rtotalp + 1 / Rtotal[h];
            }
            rtotalp = 1 / rtotalp;
            cout << "Req: " << rtotalp << "\ncurrent: " << V / rtotalp;
        }
        if (circuit_descripVon[0] == 'S')
        {
            for (int k = 0; k < Rtotal.size(); k++)
            {
                rtotals = rtotals + Rtotal[k];
            }
            cout << "Req: " << rtotals << "\ncurrent: " << V / rtotals;
        }
    }
    return 0;
}
