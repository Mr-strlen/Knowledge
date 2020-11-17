#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <stdlib.h>

using namespace std;
 
const double eps = 1e-8;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxn = 60;
int sgn(int x)
{
    if(x == 0)return 0;
    if(x < 0)return -1;
    else return 1;
}
struct Point
{
    double x,y;
    Point(){}
    Point(double _x,double _y)
    {
        x = _x;
        y = _y;
    }
    void input()
    {
        scanf("%lf%lf",&x,&y);
    }
    bool operator == (Point b)const
    {
        return sgn(x-b.x) == 0 && sgn(y-b.y) == 0;
    }
    bool operator < (Point b)const
    {
        return sgn(x-b.x)== 0?sgn(y-b.y)<0:x<b.x;
    }
    Point operator -(const Point &b)const
    {
        return Point(x-b.x,y-b.y);
    }
    Point operator +(const Point &b)const
    {
        return Point(x+b.x,y+b.y);
    }
    //叉积
    double operator ^(const Point &b)const
    {
        return x*b.y - y*b.x;
    }
    //点积
    double operator *(const Point &b)const
    {
        return x*b.x + y*b.y;
    }
};
struct Line
{
    Point s,e;
    Line(){}
    Line(Point _s,Point _e)
    {
        s = _s;
        e = _e;
    }
    bool operator ==(Line v)
    {
        return (s == v.s)&&(e == v.e);
    }
    void input()
    {
        s.input();
        e.input();
    }
    //两线段相交判断
    //2 规范相交
    //1 非规范相交
    //0 不相交
    int segcrossseg(Line v)
    {
        int d1 = sgn((e-s)^(v.s-s));
        int d2 = sgn((e-s)^(v.e-s));
        int d3 = sgn((v.e-v.s)^(s-v.s));
        int d4 = sgn((v.e-v.s)^(e-v.s));
        if( (d1^d2)==-2 && (d3^d4)==-2 )return 2;
        return (d1==0 && sgn((v.s-s)*(v.s-e))<=0) ||
            (d2==0 && sgn((v.e-s)*(v.e-e))<=0) ||
            (d3==0 && sgn((s-v.s)*(s-v.e))<=0) ||
            (d4==0 && sgn((e-v.s)*(e-v.e))<=0);
    }
    //直线和线段相交判断
    //2 规范相交
    //1 非规范相交
    //0 不相交
    int linecrossseg(Line v)
    {
        int d1 = sgn((e-s)^(v.s-s));
        int d2 = sgn((e-s)^(v.e-s));
        if((d1^d2)==-2) return 2;
        return (d1==0||d2==0);
    }
};
Line line[maxn][maxn];
Point p1[maxn],p2[maxn];
//求线段的中垂线
inline Line getMidLine(const Point &a, const Point &b) {
    Point mid = (a + b);
    mid.x/=2.0;
    mid.y/=2.0;
    Point tp = b-a;
    return Line(mid, mid+Point(-tp.y, tp.x));
}
 
inline Point intersect(const Point &a, const Point &b, const Point &l, const Point &r) {
    Point ret = a;
    double t = ((a.x - l.x) * (l.y - r.y) - (a.y - l.y) * (l.x - r.x))
            / ((a.x - b.x) * (l.y - r.y) - (a.y - b.y) * (l.x - r.x));
    ret.x += (b.x - a.x) * t;
    ret.y += (b.y - a.y) * t;
    return ret;
}
 
inline bool dotOnSeg(const Point &p, const Point &l, const Point &r) {  //判点在线段上
    return (p.x-l.x)*(p.x-r.x) < eps
    && (p.y-l.y)*(p.y-r.y) < eps;
}
 
double dis(Point a,Point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
 
int n,m;
 
bool check(const Point &p, int &a) {
    double d = dis(p, p2[a]);
    for(int i = 0; i < m; i++){
        if(i==a) continue;
        if(d > dis(p, p2[i])+eps) return 0;
    }
    return 1;
}
 
int main()
{
    int q;
    while(~scanf("%d%d",&n,&m)){
        for(int i=0;i<n;i++)
            p1[i].input();
        for(int i=0;i<m;i++)
            p2[i].input();
        for(int i=0;i<m;i++){
            for(int j=i+1;j<m;j++){
                line[i][j]=getMidLine(p2[i],p2[j]);
            }
        }
        scanf("%d",&q);
        while(q--){
            int a,b;
            scanf("%d%d",&a,&b);
            if(a==b){
                puts("0");
                continue;
            }
            a--,b--;
            Line tmp =Line(p1[a],p1[b]);
            int ans = 0;
            for(int i=0;i<m;i++){
                for(int j=i+1;j<m;j++){
                    if(line[i][j].linecrossseg(tmp)){//判断直线与线段是否相交
                        Point c = intersect(p1[a],p1[b],line[i][j].s,line[i][j].e);//求线段与直线的交点
                        if(dotOnSeg(c, p1[a], p1[b]))
                            ans+=check(c,i);
                    }
                }
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}

