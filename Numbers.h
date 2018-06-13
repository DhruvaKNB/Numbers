#include <iostream>
#include<vector>
#include<math.h>
#include<utility>
#include<fstream>
using namespace std;
int Integer(char a){
    int d = (int)a;
    if(d<0)
        d+=256;
    return d;
}
int bytes(int bits){
    return ceil(bits/8.0);
}
class vec
{
	public:
	vector< short > a;
    void create()
    {
       int j;
	   cout<<"\n Enter the Number ";
       string b;
	   cin>>b;
	   for(j=0;b[j]!='\0';j++)
            a.push_back(b[j]-'0');
    }
};
void make(int n,vec &A){
	int digit;
	int ctr=0;
	int temp=n;
	while(temp!=0){
        temp/=10;
        ctr++;
    }
    A.a.resize(ctr);
    ctr=0;
	int t=A.a.size()-1;
	while(n!=0){
		A.a[t-ctr]=n%10;
		n=n/10;
		ctr++;
	}
}
void sub(vec &A , vec &B)       ///A>B   and A=A-B
{
    int i=0;
    if(A.a.size()!=1){
    while(1){
        if(A.a[i]==0)
            i++;
        else
            break;
    }
    A.a.erase(A.a.begin(),A.a.begin()+i);
    }
    i=0;
    if(B.a.size()!=1){
    while(1){
        if(B.a[i]==0)
            i++;
        else
            break;
    }
    B.a.erase(B.a.begin(),B.a.begin()+i);
    }
    int s1 = A.a.size()-1;
    int s2 = B.a.size() -1;
    ///To check for -ve results..
    if(s2>s1){
        A.a[0]=-1;
        return;
    }
    else if(s1==s2){
        int c=0;
        bool rval = 0;
        while(c<=s1){
            if(A.a[c]==B.a[c])
                c++;
            else if(A.a[c]<B.a[c]){
                rval=1;
                break;
            }
            else
                break;
        }
        if(rval){
            A.a[0]=-1;
            return ;
        }
    }
    while((s1>=0)&&(s2>=0)){
        if(A.a[s1]>=B.a[s2]) 
            A.a[s1]-=B.a[s2];
        else{
            A.a[s1]=10+A.a[s1]-B.a[s2];
            int t=s1-1;
            while(t>=0){
                if(A.a[t]!=0){
                        A.a[t]--;
                        break;
                    }
                else
                    A.a[t--]=9;
            }
        }
        s1--;
        s2--;
    }
    i=0;
    if(A.a.size()!=1){
        while(i<A.a.size()){
            if(A.a[i]==0)
                i++;
            else
                break;
        }
        if(i!=A.a.size())
            A.a.erase(A.a.begin(),A.a.begin()+i);
        else
            A.a.resize(1,0);
        }
    }
void div(vec &A , vec &B , vec &Q , vec &R)  /// Q = A/B R=A%B
{
    if(A.a.size()<B.a.size()){
        Q.a.push_back(0);
        R=A;
        return;
    }
    int i=0;
    int ctr=0;
    vec Copy;
    while(1){
        if(i==A.a.size())
            break;
        R.a.push_back(A.a[i++]);
        Copy=R;
        if(R.a.size()<B.a.size()){
            Q.a.push_back(0);
            continue;
        }
        sub(R,B);
        if(R.a[0]<0){
            Q.a.push_back(0);
            R=Copy;
            continue;
        }
        else{
            Copy=R;
            ctr=1;
        }
        while(1){
            sub(R,B);
            ctr++;
            if(R.a[0]<0){
                R=Copy;
                Q.a.push_back(ctr-1);
                ctr=0;
                break;
            }
            else
                Copy=R;
        }
    }
    i=0;
    if(R.a.size()!=1){
        while(i<R.a.size()){
            if(R.a[i]==0)
                i++;
            else
                break;
        }
        if(i!=R.a.size())
            R.a.erase(R.a.begin(),R.a.begin()+i);
        else
            R.a.resize(1,0);
    }
    i=0;
    if(Q.a.size()!=1){
        while(i<Q.a.size()){
            if(Q.a[i]==0)
                i++;
            else
                break;
        }
        if(i!=Q.a.size())
            Q.a.erase(Q.a.begin(),Q.a.begin()+i);
        else
            Q.a.resize(1,0);
    }
}
void addn(vec &A, vec &B)// adds A to B and stores in A
{
	vec temp;
	unsigned int k,c,tem,t,l,m;
	if(A.a.size()>B.a.size())
		temp.a.resize(A.a.size()+1,0);
	else
		temp.a.resize(B.a.size()+1,0);
	for(k=A.a.size()-1,l=B.a.size()-1,m=temp.a.size()-1,c=1;(c<=A.a.size()&&c<=B.a.size());k--,l--,m--,c++){
		tem=A.a[k]+B.a[l]+temp.a[m];
		temp.a[m]=tem%10;
		temp.a[m-1]=tem/10;
	}
	while(k!=-1)
	temp.a[m--]+=A.a[k--];
	while(l!=-1)
	temp.a[m--]+=B.a[l--];
	if(temp.a[0]==0){
		for(unsigned int i=0;i<temp.a.size()-1;i++)
		temp.a[i]=temp.a[i+1];
		temp.a.pop_back();
	}
	A.a.resize(temp.a.size(),0);
	for(unsigned int t=0;t<temp.a.size();t++)
		A.a[t]=temp.a[t];
}
void multiply(vec &A, vec &B , vec &C) // Multiplies A and B and stores it in C
{
	C.a.resize(A.a.size()+B.a.size(),0);
	unsigned int noda=A.a.size();
	unsigned int nodb=B.a.size();
    unsigned int i,j,k;
	if(noda>=nodb){
		for(k=0;k<nodb;k++){
			vec temp;
			temp.a.resize(A.a.size()+B.a.size(),0);
			unsigned int nodt=temp.a.size();
			for(i=0;i<k;i++)
			temp.a[nodt-i-1]=0;
			int a=0;
			for(j=0;j<noda;j++){
				a=a/10+ A.a[noda-j-1]*B.a[nodb-k-1];
				temp.a[nodt-k-j-1]=a%10;
				if(j==(noda-1))
				temp.a[nodt-k-j-2]=a/10;
			}
			addn(C,temp);
		}
	}
	else{
		for(k=0;k<noda;k++){
			vec temp;
			temp.a.resize(A.a.size()+B.a.size(),0);
			unsigned int nodt=temp.a.size();
			for(i=0;i<k;i++)
			temp.a[nodt-i-1]=0;
			int a=0;
			for(j=0;j<nodb;j++){
				a=a/10+ A.a[noda-k-1]*B.a[nodb-j-1];
				temp.a[nodt-k-j-1]=a%10;
				if(j==(nodb-1))
				temp.a[nodt-k-j-2]=a/10;
			}
			addn(C,temp);
		}
	}
	if(C.a[0]==0){
		for(unsigned int i=0;i<C.a.size()-1;i++)
		C.a[i]=C.a[i+1];
		C.a.pop_back();
	}
}
void display(vec &A)
{
    unsigned int i;
    for(i=0;i<A.a.size();i++)
        cout<<A.a[i];
}
void divby2( vec &a){
    int li=a.a.size()-1;
    while(li>=0){
        int t=a.a[li];
        a.a[li] = (t>>1);
        if(((t)&(1))&&(li!=(a.a.size()-1)))
            a.a[li+1]+=5;
            li--;
    }
    if((a.a[0]==0)&&(a.a.size()!=1))
        a.a.erase(a.a.begin());
}
bool zero( vec &a){
    return (a.a[0]==0);
}
bool rem(vec &a){
    return ((a.a[a.a.size()-1])&(1));
}
vector < bool > binary ( vec &a){
    vector < bool > rval;
    while (! (zero(a)) ){
        rval.push_back(rem(a));
        divby2(a);
    }
    return rval;
}
void shift( vector < bool > &t , vector < short > &g){
    bool arg=t[t.size()-1];
    for(int i=t.size()-1;i>0;i--)
        t[i]=t[i-1];
    t[0]=0;
    for(int i=0;i<g.size();i++)
        if(g[i]>4)
            g[i]+=3;
    int li = g.size()-1;
    while(li){
        g[li]<<=1;
        if((g[li-1])&(8))
            g[li]++;
        g[li]&=15;
        li--;
    }
    g[0]<<=1;
    if(arg)
        g[0]++;
    g[0]&=15;
}
class Int{
    private:
    char* num;
    int bits;
    bool sign;
    ///makes number from binary array..
    friend void make_num( vector <bool> &temp , Int &d);
    ///makes binary array from num...
    friend vector < bool > make_binary(Int &d);
    friend void make_Int(vec &a , bool sign , Int &d);
    friend vec make_vec(Int &d);
    public:
    Int(){
        sign=0;
        bits=0;
    };
    Int(long long int n){
        sign=0;
        bits=0;
        if(n<0)
            sign=1,n*=-1;
        vector < bool > temp;
        while(n!=0){
            temp.push_back((n)&(1));
            n>>=1;
        }
        bits = temp.size();
        int t = bytes(bits);
        num = new char[t];
        make_num(temp , *this);
        if(bits==0){
            bits=1;
            num = new char[1];
            num[0]=0;
        }
    };
    Int(string a , long long size,bool s=0){
        bits=size;
        sign=s;
        num = new char[bytes(bits)];
        for(int i=0;i<a.length();i++)
            num[i]=a[i];
    }
    void display(){
        cout<<" Sign : "<<sign<<endl;
        cout<<" Bits : "<<bits<<endl;
        int t = bytes(bits);
        for(int i=0;i<t;i++){
            cout<<Integer(num[i])<<" ";
        }
        cout<<endl;
    };
    ///0 gives LSB.if this=sum(a[i]*2^i)  .. given i gives a[i]
    ///first argument indicates validity (1:valid) and second argument is the bit itself.
    pair < bool , bool > ith_bit(int t){
        pair < bool , bool > rval;
        rval.first=0;
        if(t>(bits-1)){
            return rval;
        }
        rval.first=1;
        int n = num[(t>>3)];
        int shift = t%8;
        rval.second = ( n & (1<<shift) ) >> shift ; 
        return rval;
    }
    int ith_digit(int i){
        if(i<0)
            return -1;
        vector < bool > binary = make_binary(*(this));
        int bits = binary.size();
        int digits = ceil(bits/3.321928);
        vector < short > g;
        g.resize(digits,0);
        while(bits--)
            shift(binary,g);
        int li = g.size()-1;
        while(g[li]==0)
            li--;
        g.erase(g.begin()+li+1,g.end());
        if(i>(g.size()-1))
            return -1;
        else
            return g[i];
    }
    ///I/O

    friend istream & operator >> (istream &in , Int &tt){
        string a;
        cin>>a;
        int si=0;
        if(a[0]=='-')
            tt.sign=1,si++;
        while(a[si]=='0')
            si++;
        if(si==a.length()){
            tt = Int(0);
            return in;
        }
        vec d;
        for(int j=si;a[j]!='\0';j++)
            d.a.push_back(a[j]-'0');
        vector < bool > temp = binary(d);
        tt.bits = temp.size();
        int t = bytes(tt.bits);
        tt.num = new char[t];
        make_num(temp,tt);
        return in;
    }
    friend ostream & operator << (ostream &out , Int &tt){
        vector < bool > binary= make_binary(tt);
        if(binary.size()==1){
            if(tt.sign)
                cout<<"-";
            cout<<binary[0];
            return out;
        }
        int bits = binary.size();
        int digits = ceil(bits/3.321928);
        vector < short > g;
        g.resize(digits,0);
        while(bits--)
            shift(binary,g);
        int li = g.size()-1;
        while(g[li]==0)
            li--;
        g.erase(g.begin()+li+1,g.end());
        if(tt.sign)
            cout<<"-";
        while(!(g.empty())){
            cout<<g.back();
            g.pop_back();
        }
        return out;
    }
    void negative(Int &rval){
        rval = *(this);
        rval.sign = !(rval.sign);
        return;
    }
    void add(Int &a , Int &b , Int &cc){
        vector < bool > b1 = make_binary(a);
        vector < bool > b2 = make_binary(b);
        vector < bool > c;
        int s = max(b1.size(),b2.size());
        b1.resize(s,0);
        b2.resize(s,0);
        c.resize(s+1,0);
        short carry=0;
        for(int i=0;i<s;i++){
            short res = b1[i] + b2[i] + carry;
            if(res > 1){
                c[i] = res-2;
                carry = 1;
            }
            else{
                carry=0;
                c[i]=res;
            }
        }
        if(carry)
            c[s] = carry;
        else
            c.pop_back();
        cc.bits = c.size();
        cc.sign = a.sign;
        cc.num = new char [bytes(cc.bits)];
        make_num(c,cc);
        return;
    }
    void sub(Int &a , Int &b,Int &cc){
        vector < bool > c;
        bool sign = a.sign;
        if(a==b)
            c.resize(1,0),sign=0;
        else{
            vector < bool > b1 = make_binary(a);
            vector < bool > b2 = make_binary(b);
            int s = max(b1.size(),b2.size());
            b1.resize(s,0);
            b2.resize(s,0);
            c.resize(s,0);
            for(int i=0;i<s;i++){
                short res = b1[i] - b2[i];
                if(res < 0){
                    c[i] = 1;
                    int start = i+1;
                    while(start<s){
                        if(b1[start]==0)
                            b1[start]=1;
                        else{
                            b1[start]=0;
                            break;
                        }
                    start++;
                    }
                }
                else
                    c[i]=res;
            }
            int st = c.size()-1;
            while((c[st]==0)&&(st>=0))
                st--;
            c.erase(c.begin()+1+st,c.end());        
        }
        cc.bits = c.size();
        cc.sign = sign;
        cc.num = new char [bytes(cc.bits)];
        make_num(c,cc);
        return;
    }
    void mul(Int &a , Int &b,Int &cc){
        vec aa , bb ,c;
        aa = make_vec(a);
        bb = make_vec(b);
        multiply(aa,bb,c);
        bool s = a.sign ^ b. sign ;
        make_Int(c,s,cc);
        return;
    }
    void divide(Int &a , Int &b , Int &qq , Int &rr){
        vec aa , bb , q ,r;
        aa = make_vec(a);
        bb = make_vec(b);
        div(aa,bb,q,r);
        bool s = a.sign ^ b. sign ;
        make_Int(q,s,qq);
        make_Int(r,0,rr);
        return;
    }
    /// Operator Overloading with Int
    Int& operator = (const Int &d){
        bits=d.bits;
        sign = d.sign;
        int size=bytes(bits);
        num = new char[size];
        for(int i=0;i<size;i++)
            num[i] = d.num[i];
        return *this;
    }
    bool operator == (const Int &d){
        if(sign!=d.sign)
            return 0;
        int d1 = bytes(bits);
        int d2 = bytes(d.bits);
        if(d1!=d2)
            return 0;
        for(int i=0;i<d1;i++)
            if(d.num[i]!=num[i])
                return 0;
        return 1;
    }
    bool operator != (const Int &d){
        if(sign!=d.sign)
            return 1;
        int d1 = bytes(bits);
        int d2 = bytes(d.bits);
        if(d1!=d2)
            return 1;
        for(int i=0;i<d1;i++)
            if(d.num[i]!=num[i])
                return 1;
        return 0;
    }
    bool operator > ( Int& d){
        bool s1 = sign;
        bool s2 = d.sign;
        int d1=bits;
        int d2=d.bits;
        bool a,b;
        if ((s1) && (!s2))
            return 0;
        if ((!s1) && (s2))
            return 1;
        if( (!s1) && (!s2) )   ///both positive
        {
            if( d1 > d2 )
                return 1;
            else{
                if( d2 > d1)
                    return 0;
                d1--;
                while(d1>=0){
                    a=ith_bit(d1).second;
                    b=d.ith_bit(d1).second;
                    if ( a > b )
                        return 1;
                    if ( b > a )
                        return 0;
                    d1--;
                }
                return 0;
            }
        }
        if( (s1) && (s2) )    ///both negative
           {
            if( d1 > d2 )
                return 0;
            else{
                if( d2 > d1)
                    return 1;
                d1--;
                while(d1>=0){
                    a=ith_bit(d1).second;
                    b=d.ith_bit(d1).second;
                    if ( b > a )
                        return 1;
                    if ( a > b )
                        return 0;
                    d1--;
                }
                return 0;
            }
        }
    }
    bool operator < ( Int& d){
        bool s1 = sign;
        bool s2 = d.sign;
        int d1=bits;
        int d2=d.bits;
        bool a,b;
        if ((s1) && (!s2))
            return 1;
        if ((!s1) && (s2))
            return 0;
        if( (!s1) && (!s2) )   ///both positive
        {
            if( d1 < d2 )
                return 1;
            else{
                if( d2 < d1)
                    return 0;
                d1--;
                while(d1>=0){
                    a=ith_bit(d1).second;
                    b=d.ith_bit(d1).second;
                    if ( a < b )
                        return 1;
                    if ( b < a )
                        return 0;
                    d1--;
                }
                return 0;
            }
        }
        if( (s1) && (s2) )    ///both negative
           {
            if( d1 < d2 )
                return 0;
            else{
                if( d2 < d1)
                    return 1;
                d1--;
                while(d1>=0){
                    a=ith_bit(d1).second;
                    b=d.ith_bit(d1).second;
                    if ( b < a )
                        return 1;
                    if ( a < b )
                        return 0;
                    d1--;
                }
                return 0;
            }
        }
    }
    bool operator <= ( Int& d){
        bool s1 = sign;
        bool s2 = d.sign;
        int d1=bits;
        int d2=d.bits;
        bool a,b;
        if ((s1) && (!s2))
            return 1;
        if ((!s1) && (s2))
            return 0;
        if( (!s1) && (!s2) )   ///both positive
        {
            if( d1 > d2 )
                return 0;
            else{
                if( d2 > d1)
                    return 1;
                d1--;
                while(d1>=0){
                    a=ith_bit(d1).second;
                    b=d.ith_bit(d1).second;
                    if ( a > b )
                        return 0;
                    if ( b > a )
                        return 1;
                    d1--;
                }
                return 1;
            }
        }
        if( (s1) && (s2) )    ///both negative
           {
            if( d1 > d2 )
                return 1;
            else{
                if( d2 > d1)
                    return 0;
                d1--;
                while(d1>=0){
                    a=ith_bit(d1).second;
                    b=d.ith_bit(d1).second;
                    if ( b > a )
                        return 0;
                    if ( a > b )
                        return 1;
                    d1--;
                }
                return 1;
            }
        }
    }
    bool operator >= ( Int& d){
        bool s1 = sign;
        bool s2 = d.sign;
        int d1=bits;
        int d2=d.bits;
        bool a,b;
        if ((s1) && (!s2))
            return 0;
        if ((!s1) && (s2))
            return 1;
        if( (!s1) && (!s2) )   ///both positive
        {
            if( d1 < d2 )
                return 0;
            else{
                if( d2 < d1)
                    return 1;
                d1--;
                while(d1>=0){
                    a=ith_bit(d1).second;
                    b=d.ith_bit(d1).second;
                    if ( a < b )
                        return 0;
                    if ( b < a )
                        return 1;
                    d1--;
                }
                return 1;
            }
        }
        if( (s1) && (s2) )    ///both negative
           {
            if( d1 < d2 )
                return 1;
            else{
                if( d2 < d1)
                    return 0;
                d1--;
                while(d1>=0){
                    a=ith_bit(d1).second;
                    b=d.ith_bit(d1).second;
                    if ( b < a )
                        return 0;
                    if ( a < b )
                        return 1;
                    d1--;
                }
                return 1;
            }
        }
    }
    Int operator | (Int &d){
        vector < bool > lhs = make_binary(*this);
        vector < bool > rhs = make_binary(d);
        int size = max(lhs.size(),rhs.size());
        lhs.resize(size,0);
        rhs.resize(size,0);
        for(int i=0;i<size;i++)
            lhs[i]=((lhs[i])|(rhs[i]));
        size=lhs.size()-1;
        while((lhs[size]==0)&&(size>=0))
            size--;
        lhs.erase(lhs.begin()+size+1,lhs.end());
        if(size<0)
          lhs.push_back(0);
        size=lhs.size();
        Int dd;
        dd.bits = size;
        dd.num = new char[bytes(size)];
        dd.sign= ((*this).sign | d.sign);
        make_num(lhs,dd);
        return dd;
    }
    Int operator & (Int &d){
        vector < bool > lhs = make_binary(*this);
        vector < bool > rhs = make_binary(d);
        int size = max(lhs.size(),rhs.size());
        lhs.resize(size,0);
        rhs.resize(size,0);
        for(int i=0;i<size;i++)
            lhs[i]=((lhs[i])&(rhs[i]));
        size=lhs.size()-1;
        while((lhs[size]==0)&&(size>=0))
            size--;
        lhs.erase(lhs.begin()+size+1,lhs.end());
        if(size<0)
          lhs.push_back(0);
        size=lhs.size();
        Int dd;
        dd.bits = size;
        dd.num = new char[bytes(size)];
        dd.sign= ((*this).sign & d.sign);
        make_num(lhs,dd);
        return dd;
    }
    Int operator ^ (Int &d){
        vector < bool > lhs = make_binary(*this);
        vector < bool > rhs = make_binary(d);
        int size = max(lhs.size(),rhs.size());
        lhs.resize(size,0);
        rhs.resize(size,0);
        for(int i=0;i<size;i++)
            lhs[i]=((lhs[i])^(rhs[i]));
        size=lhs.size()-1;
        while((lhs[size]==0)&&(size>=0))
            size--;
        lhs.erase(lhs.begin()+size+1,lhs.end());
        if(size<0)
          lhs.push_back(0);
        size=lhs.size();
        Int dd;
        dd.bits = size;
        dd.num = new char[bytes(size)];
        dd.sign= ((*this).sign ^ d.sign);
        make_num(lhs,dd);
        return dd;
    }
    Int& operator |= (Int &d){
        vector < bool > lhs = make_binary(*this);
        vector < bool > rhs = make_binary(d);
        int size = max(lhs.size(),rhs.size());
        lhs.resize(size,0);
        rhs.resize(size,0);
        for(int i=0;i<size;i++)
            lhs[i]=((lhs[i])|(rhs[i]));
        size=lhs.size()-1;
        while((lhs[size]==0)&&(size>=0))
            size--;
        lhs.erase(lhs.begin()+size+1,lhs.end());
        if(size<0)
          lhs.push_back(0);
        size=lhs.size();
        Int dd;
        dd.bits = size;
        dd.num = new char[bytes(size)];
        dd.sign= ((*this).sign | d.sign);
        make_num(lhs,dd);
        *this = dd;
        return *this;
    }
    Int& operator &= (Int &d){
        vector < bool > lhs = make_binary(*this);
        vector < bool > rhs = make_binary(d);
        int size = max(lhs.size(),rhs.size());
        lhs.resize(size,0);
        rhs.resize(size,0);
        for(int i=0;i<size;i++)
            lhs[i]=((lhs[i])&(rhs[i]));
        size=lhs.size()-1;
        while((lhs[size]==0)&&(size>=0))
            size--;
        lhs.erase(lhs.begin()+size+1,lhs.end());
        if(size<0)
          lhs.push_back(0);
        size=lhs.size();
        Int dd;
        dd.bits = size;
        dd.num = new char[bytes(size)];
        dd.sign= ((*this).sign & d.sign);
        make_num(lhs,dd);
        *this = dd;
        return *this;
    }
    Int& operator ^= (Int &d){
        vector < bool > lhs = make_binary(*this);
        vector < bool > rhs = make_binary(d);
        int size = max(lhs.size(),rhs.size());
        lhs.resize(size,0);
        rhs.resize(size,0);
        for(int i=0;i<size;i++)
            lhs[i]=((lhs[i])^(rhs[i]));
        size=lhs.size()-1;
        while((lhs[size]==0)&&(size>=0))
            size--;
        lhs.erase(lhs.begin()+size+1,lhs.end());
        if(size<0)
          lhs.push_back(0);
        size=lhs.size();
        Int dd;
        dd.bits = size;
        dd.num = new char[bytes(size)];
        dd.sign= ((*this).sign ^ d.sign);
        make_num(lhs,dd);
        *this = dd;
        return *this;
    }    
    Int operator ! (){
        vector < bool > lhs = make_binary(*this);
        int size = lhs.size();
        for(int i=0;i<size;i++)
            lhs[i] = !(lhs[i]);
        size=lhs.size()-1;
        while((lhs[size]==0)&&(size>=0))
            size--;
        lhs.erase(lhs.begin()+size+1,lhs.end());
        if(size<0)
          lhs.push_back(0);
        size=lhs.size();
        Int dd;
        dd.bits = size;
        dd.num = new char[bytes(size)];
        dd.sign= (*this).sign;
        make_num(lhs,dd);
        return dd;
    }
    Int operator + (Int &d){
        bool s1 = sign;
        bool s2 = d.sign;
        bool rsign;
        Int rval;
        if(s1==s2){
            add((*this) , d , rval);
            return rval;
        }
        ///s1 is -ve s2 is +ve
        else if ((s1)&&(!s2)){
            Int temp; 
            (*this).negative(temp);
            if(temp > d ){
                sub(temp,d,rval);
                rval.sign=1;
                return rval;
            }
            else{
                sub(d,temp,rval);
                rval.sign=0;
                return rval;
            }
        }
        else{
            Int temp; 
            d.negative(temp);
            if(temp <= (*this) ){
                sub((*this),temp,rval);
                rval.sign=0;
                return rval;
            }
            else{
                sub(temp,(*this),rval);
                rval.sign=1;
                return rval;
            }
        }
    }
    Int operator - (Int &d){
        bool s1 = sign;
        bool s2 = d.sign;
        bool rsign;
        Int rval;
        if(s1!=s2){
            add((*this) , d , rval);
            rval.sign=s1;
            return rval;
        }
        ///both -ve
        else if (s1){
            if((*this) >= d ){
                sub(d,(*this),rval);
                rval.sign=0;
                return rval;
            }
            else{
                sub((*this),d,rval);
                rval.sign=1;
                return rval;
            }
        }
        else{
            if(d <= (*this) ){
                sub((*this),d,rval);
                rval.sign=0;
                return rval;
            }
            else{
                sub(d,(*this),rval);
                rval.sign=1;
                return rval;
            }
        }
    }
    Int operator * (Int &d){
        Int rval;
        mul(*(this),d,rval);
        return rval;
    }
    Int operator / (Int &d){
        Int rval,t;
        divide(*(this),d,rval,t);
        return rval;
    }
    Int operator % (Int &d){
        Int rval,t;
        divide(*(this),d,rval,t);
        return t;
    }
    Int& operator += (Int &d){
        bool s1 = sign;
        bool s2 = d.sign;
        bool rsign;
        Int rval;
        if(s1==s2){
            add((*this) , d , rval);
            *this = rval;
            return *this;
        }
        ///s1 is -ve s2 is +ve
        else if ((s1)&&(!s2)){
            Int temp; 
            (*this).negative(temp);
            if(temp > d ){
                sub(temp,d,rval);
                rval.sign=1;
                *this = rval;
                return *this;
            }
            else{
                sub(d,temp,rval);
                rval.sign=0;
                *this = rval;
                return *this;
            }
        }
        else{
            Int temp; 
            d.negative(temp);
            if(temp <= (*this) ){
                sub((*this),temp,rval);
                rval.sign=0;
                *this = rval;
                return *this;
            }
            else{
                sub(temp,(*this),rval);
                rval.sign=1;
                *this = rval;
                return *this;
            }
        }
    }
    Int& operator -= (Int &d){
        bool s1 = sign;
        bool s2 = d.sign;
        bool rsign;
        Int rval;
        if(s1!=s2){
            add((*this) , d , rval);
            rval.sign=s1;
            *this = rval;
            return *this;
        }
        ///both -ve
        else if (s1){
            if((*this) >= d ){
                sub(d,(*this),rval);
                rval.sign=0;
                *this = rval;
                return *this;
            }
            else{
                sub((*this),d,rval);
                rval.sign=1;
                *this = rval;
                return *this;
            }
        }
        else{
            if(d <= (*this) ){
                sub((*this),d,rval);
                rval.sign=0;
                *this = rval;
                return *this;
            }
            else{
                sub(d,(*this),rval);
                rval.sign=1;
                *this = rval;
                return *this;
            }
        }
    }
    Int& operator *= (Int &d){
        Int rval;
        mul(*(this),d,rval);
        *this = rval;
        return *this;
    }
    Int& operator /= (Int &d){
        Int rval,t;
        divide(*(this),d,rval,t);
        *this = rval;
        return *this;
    }
    Int& operator %= (Int &d){
        Int rval,t;
        divide(*(this),d,rval,t);
        *this = rval;
        return *this;
    }
    Int operator++ (){
        Int t(1);
        Int m;
        m=(*this);
        (*this) = t+m;
        return *this;
    }
    Int operator-- (){
        Int t(-1);
        Int m;
        m=(*this);
        (*this) = t+m;
        return *this;
    }
    Int operator++( int ){
        Int t(1);
        Int m;
        m=(*this);
        (*this) = t+m;
        return m;
    }
    Int operator--( int ){
        Int t(-1);
        Int m;
        m=(*this);
        (*this) = t+m;
        return m;
    }
    ///Operator Overloading with int
    Int& operator = (const long long& d){
        *this = Int(d);
        return *this;
    }
    bool operator == (const long long &t){
        Int d(t);
        if(sign!=d.sign)
            return 0;
        int d1 = bytes(bits);
        int d2 = bytes(d.bits);
        if(d1!=d2)
            return 0;
        for(int i=0;i<d1;i++)
            if(d.num[i]!=num[i])
                return 0;
        return 1;
    }
    bool operator != (const long long &t){
        Int d(t);
        if(sign!=d.sign)
            return 1;
        int d1 = bytes(bits);
        int d2 = bytes(d.bits);
        if(d1!=d2)
            return 1;
        for(int i=0;i<d1;i++)
            if(d.num[i]!=num[i])
                return 1;
        return 0;
    }
    bool operator > ( const long long &t){
        Int d(t);
        bool s1 = sign;
        bool s2 = d.sign;
        int d1=bits;
        int d2=d.bits;
        bool a,b;
        if ((s1) && (!s2))
            return 0;
        if ((!s1) && (s2))
            return 1;
        if( (!s1) && (!s2) )   ///both positive
        {
            if( d1 > d2 )
                return 1;
            else{
                if( d2 > d1)
                    return 0;
                d1--;
                while(d1>=0){
                    a=ith_bit(d1).second;
                    b=d.ith_bit(d1).second;
                    if ( a > b )
                        return 1;
                    if ( b > a )
                        return 0;
                    d1--;
                }
                return 0;
            }
        }
        if( (s1) && (s2) )    ///both negative
           {
            if( d1 > d2 )
                return 0;
            else{
                if( d2 > d1)
                    return 1;
                d1--;
                while(d1>=0){
                    a=ith_bit(d1).second;
                    b=d.ith_bit(d1).second;
                    if ( b > a )
                        return 1;
                    if ( a > b )
                        return 0;
                    d1--;
                }
                return 0;
            }
        }
    }
    bool operator < ( const long long &t){
        Int d(t);
        bool s1 = sign;
        bool s2 = d.sign;
        int d1=bits;
        int d2=d.bits;
        bool a,b;
        if ((s1) && (!s2))
            return 1;
        if ((!s1) && (s2))
            return 0;
        if( (!s1) && (!s2) )   ///both positive
        {
            if( d1 < d2 )
                return 1;
            else{
                if( d2 < d1)
                    return 0;
                d1--;
                while(d1>=0){
                    a=ith_bit(d1).second;
                    b=d.ith_bit(d1).second;
                    if ( a < b )
                        return 1;
                    if ( b < a )
                        return 0;
                    d1--;
                }
                return 0;
            }
        }
        if( (s1) && (s2) )    ///both negative
           {
            if( d1 < d2 )
                return 0;
            else{
                if( d2 < d1)
                    return 1;
                d1--;
                while(d1>=0){
                    a=ith_bit(d1).second;
                    b=d.ith_bit(d1).second;
                    if ( b < a )
                        return 1;
                    if ( a < b )
                        return 0;
                    d1--;
                }
                return 0;
            }
        }
    }
    bool operator <= ( const long long &t){
        Int d(t);
        bool s1 = sign;
        bool s2 = d.sign;
        int d1=bits;
        int d2=d.bits;
        bool a,b;
        if ((s1) && (!s2))
            return 1;
        if ((!s1) && (s2))
            return 0;
        if( (!s1) && (!s2) )   ///both positive
        {
            if( d1 > d2 )
                return 0;
            else{
                if( d2 > d1)
                    return 1;
                d1--;
                while(d1>=0){
                    a=ith_bit(d1).second;
                    b=d.ith_bit(d1).second;
                    if ( a > b )
                        return 0;
                    if ( b > a )
                        return 1;
                    d1--;
                }
                return 1;
            }
        }
        if( (s1) && (s2) )    ///both negative
           {
            if( d1 > d2 )
                return 1;
            else{
                if( d2 > d1)
                    return 0;
                d1--;
                while(d1>=0){
                    a=ith_bit(d1).second;
                    b=d.ith_bit(d1).second;
                    if ( b > a )
                        return 0;
                    if ( a > b )
                        return 1;
                    d1--;
                }
                return 1;
            }
        }
    }
    bool operator >= ( const long long &t){
        Int d(t);
        bool s1 = sign;
        bool s2 = d.sign;
        int d1=bits;
        int d2=d.bits;
        bool a,b;
        if ((s1) && (!s2))
            return 0;
        if ((!s1) && (s2))
            return 1;
        if( (!s1) && (!s2) )   ///both positive
        {
            if( d1 < d2 )
                return 0;
            else{
                if( d2 < d1)
                    return 1;
                d1--;
                while(d1>=0){
                    a=ith_bit(d1).second;
                    b=d.ith_bit(d1).second;
                    if ( a < b )
                        return 0;
                    if ( b < a )
                        return 1;
                    d1--;
                }
                return 1;
            }
        }
        if( (s1) && (s2) )    ///both negative
           {
            if( d1 < d2 )
                return 1;
            else{
                if( d2 < d1)
                    return 0;
                d1--;
                while(d1>=0){
                    a=ith_bit(d1).second;
                    b=d.ith_bit(d1).second;
                    if ( b < a )
                        return 0;
                    if ( a < b )
                        return 1;
                    d1--;
                }
                return 1;
            }
        }
    }
    Int operator >> (const long long &d){
        long long t=d;
        vector < bool > binary=make_binary(*(this));
        if(t>0){
            ///right shift by d
            while(t>0){
                if(binary.size()==0)
                    break;
                int start=0;
                while(start<(binary.size()-1)){
                    binary[start]=binary[start+1];
                    start++;
                }
                binary.pop_back();
                t--;
            }
        }
        else if(t<0){
            ///left shift by d
            t=(-1*t);
            while(t>0){
                binary.push_back(0);
                int start=binary.size()-1;
                while(start>0){
                    binary[start]=binary[start-1];
                    start--;
                }
                binary[0]=0;
                t--;
            }
        }
        if(binary.size()==0)
            return Int(0);
        Int dd;
        dd.sign = (*this).sign;
        dd.bits = binary.size();
        dd.num = new char[bytes(dd.bits)];
        make_num(binary,dd);
        return dd;
    }
    Int operator << (const long long &d){
        long long t=-1*d;
        vector < bool > binary=make_binary(*(this));
        if(t>0){
            ///right shift by d
            while(t>0){
                if(binary.size()==0)
                    break;
                int start=0;
                while(start<(binary.size()-1)){
                    binary[start]=binary[start+1];
                    start++;
                }
                binary.pop_back();
                t--;
            }
        }
        else if(t<0){
            ///left shift by d
            t=(-1*t);
            while(t>0){
                binary.push_back(0);
                int start=binary.size()-1;
                while(start>0){
                    binary[start]=binary[start-1];
                    start--;
                }
                binary[0]=0;
                t--;
            }
        }
        if(binary.size()==0)
            return Int(0);
        Int dd;
        dd.sign = (*this).sign;
        dd.bits = binary.size();
        dd.num = new char[bytes(dd.bits)];
        make_num(binary,dd);
        return dd;
    }
    Int& operator >>= (const long long &d){
        long long t=d;
        vector < bool > binary=make_binary(*(this));
        if(t>0){
            ///right shift by d
            while(t>0){
                if(binary.size()==0)
                    break;
                int start=0;
                while(start<(binary.size()-1)){
                    binary[start]=binary[start+1];
                    start++;
                }
                binary.pop_back();
                t--;
            }
        }
        else if(t<0){
            ///left shift by d
            t=(-1*t);
            while(t>0){
                binary.push_back(0);
                int start=binary.size()-1;
                while(start>0){
                    binary[start]=binary[start-1];
                    start--;
                }
                binary[0]=0;
                t--;
            }
        }
        if(binary.size()==0){
            *this = Int(0);
            return *this;
        }
        bits = binary.size();
        num = new char[bytes(bits)];
        make_num(binary,*this);
        return *this;
    }
    Int& operator <<= (const long long &d){
        long long t=-1*d;
        vector < bool > binary=make_binary(*(this));
        if(t>0){
            ///right shift by d
            while(t>0){
                if(binary.size()==0)
                    break;
                int start=0;
                while(start<(binary.size()-1)){
                    binary[start]=binary[start+1];
                    start++;
                }
                binary.pop_back();
                t--;
            }
        }
        else if(t<0){
            ///left shift by d
            t=(-1*t);
            while(t>0){
                binary.push_back(0);
                int start=binary.size()-1;
                while(start>0){
                    binary[start]=binary[start-1];
                    start--;
                }
                binary[0]=0;
                t--;
            }
        }
        if(binary.size()==0){
            *this = Int(0);
            return *this;
        }
        bits = binary.size();
        num = new char[bytes(bits)];
        make_num(binary,*this);
        return *this;
    }
    Int operator | (long long &t){
        Int d(t);
        vector < bool > lhs = make_binary(*this);
        vector < bool > rhs = make_binary(d);
        int size = max(lhs.size(),rhs.size());
        lhs.resize(size,0);
        rhs.resize(size,0);
        for(int i=0;i<size;i++)
            lhs[i]=((lhs[i])|(rhs[i]));
        size=lhs.size()-1;
        while((lhs[size]==0)&&(size>=0))
            size--;
        lhs.erase(lhs.begin()+size+1,lhs.end());
        if(size<0)
          lhs.push_back(0);
        size=lhs.size();
        Int dd;
        dd.bits = size;
        dd.num = new char[bytes(size)];
        dd.sign= ((*this).sign | d.sign);
        make_num(lhs,dd);
        return dd;
    }
    Int operator & (long long &t){
        Int d(t);
        vector < bool > lhs = make_binary(*this);
        vector < bool > rhs = make_binary(d);
        int size = max(lhs.size(),rhs.size());
        lhs.resize(size,0);
        rhs.resize(size,0);
        for(int i=0;i<size;i++)
            lhs[i]=((lhs[i])&(rhs[i]));
        size=lhs.size()-1;
        while((lhs[size]==0)&&(size>=0))
            size--;
        lhs.erase(lhs.begin()+size+1,lhs.end());
        if(size<0)
          lhs.push_back(0);
        size=lhs.size();
        Int dd;
        dd.bits = size;
        dd.num = new char[bytes(size)];
        dd.sign= ((*this).sign & d.sign);
        make_num(lhs,dd);
        return dd;
    }
    Int operator ^ (long long &t){
        Int d(t);
        vector < bool > lhs = make_binary(*this);
        vector < bool > rhs = make_binary(d);
        int size = max(lhs.size(),rhs.size());
        lhs.resize(size,0);
        rhs.resize(size,0);
        for(int i=0;i<size;i++)
            lhs[i]=((lhs[i])^(rhs[i]));
        size=lhs.size()-1;
        while((lhs[size]==0)&&(size>=0))
            size--;
        lhs.erase(lhs.begin()+size+1,lhs.end());
        if(size<0)
          lhs.push_back(0);
        size=lhs.size();
        Int dd;
        dd.bits = size;
        dd.num = new char[bytes(size)];
        dd.sign= ((*this).sign ^ d.sign);
        make_num(lhs,dd);
        return dd;
    }
    Int& operator |= (long long &t){
        Int d(t);
        vector < bool > lhs = make_binary(*this);
        vector < bool > rhs = make_binary(d);
        int size = max(lhs.size(),rhs.size());
        lhs.resize(size,0);
        rhs.resize(size,0);
        for(int i=0;i<size;i++)
            lhs[i]=((lhs[i])|(rhs[i]));
        size=lhs.size()-1;
        while((lhs[size]==0)&&(size>=0))
            size--;
        lhs.erase(lhs.begin()+size+1,lhs.end());
        if(size<0)
          lhs.push_back(0);
        size=lhs.size();
        Int dd;
        dd.bits = size;
        dd.num = new char[bytes(size)];
        dd.sign= ((*this).sign | d.sign);
        make_num(lhs,dd);
        *this = dd;
        return *this;
    }
    Int& operator &= (long long &t){
        Int d(t);
        vector < bool > lhs = make_binary(*this);
        vector < bool > rhs = make_binary(d);
        int size = max(lhs.size(),rhs.size());
        lhs.resize(size,0);
        rhs.resize(size,0);
        for(int i=0;i<size;i++)
            lhs[i]=((lhs[i])&(rhs[i]));
        size=lhs.size()-1;
        while((lhs[size]==0)&&(size>=0))
            size--;
        lhs.erase(lhs.begin()+size+1,lhs.end());
        if(size<0)
          lhs.push_back(0);
        size=lhs.size();
        Int dd;
        dd.bits = size;
        dd.num = new char[bytes(size)];
        dd.sign= ((*this).sign & d.sign);
        make_num(lhs,dd);
        *this = dd;
        return *this;
    }
    Int& operator ^= (long long &t){
        Int d(t);
        vector < bool > lhs = make_binary(*this);
        vector < bool > rhs = make_binary(d);
        int size = max(lhs.size(),rhs.size());
        lhs.resize(size,0);
        rhs.resize(size,0);
        for(int i=0;i<size;i++)
            lhs[i]=((lhs[i])^(rhs[i]));
        size=lhs.size()-1;
        while((lhs[size]==0)&&(size>=0))
            size--;
        lhs.erase(lhs.begin()+size+1,lhs.end());
        if(size<0)
          lhs.push_back(0);
        size=lhs.size();
        Int dd;
        dd.bits = size;
        dd.num = new char[bytes(size)];
        dd.sign= ((*this).sign ^ d.sign);
        make_num(lhs,dd);
        *this = dd;
        return *this;
    }
    Int operator + (long long &t){
        Int d(t);
        bool s1 = sign;
        bool s2 = d.sign;
        bool rsign;
        Int rval;
        if(s1==s2){
            add((*this) , d , rval);
            return rval;
        }
        ///s1 is -ve s2 is +ve
        else if ((s1)&&(!s2)){
            Int temp; 
            (*this).negative(temp);
            if(temp > d ){
                sub(temp,d,rval);
                rval.sign=1;
                return rval;
            }
            else{
                sub(d,temp,rval);
                rval.sign=0;
                return rval;
            }
        }
        else{
            Int temp; 
            d.negative(temp);
            if(temp <= (*this) ){
                sub((*this),temp,rval);
                rval.sign=0;
                return rval;
            }
            else{
                sub(temp,(*this),rval);
                rval.sign=1;
                return rval;
            }
        }
    }
    Int operator - (long long &t){
        Int d(t);
        bool s1 = sign;
        bool s2 = d.sign;
        bool rsign;
        Int rval;
        if(s1!=s2){
            add((*this) , d , rval);
            rval.sign=s1;
            return rval;
        }
        ///both -ve
        else if (s1){
            if((*this) >= d ){
                sub(d,(*this),rval);
                rval.sign=0;
                return rval;
            }
            else{
                sub((*this),d,rval);
                rval.sign=1;
                return rval;
            }
        }
        else{
            if(d <= (*this) ){
                sub((*this),d,rval);
                rval.sign=0;
                return rval;
            }
            else{
                sub(d,(*this),rval);
                rval.sign=1;
                return rval;
            }
        }
    }
    Int operator * (long long &t){
        Int d(t);
        Int rval;
        mul(*(this),d,rval);
        return rval;
    }
    Int operator / (long long &tt){
        Int d(tt);
        Int rval,t;
        divide(*(this),d,rval,t);
        return rval;
    }
    Int operator % (long long &tt){
        Int d(tt);
        Int rval,t;
        divide(*(this),d,rval,t);
        return t;
    }
    Int& operator += (long long &t){
        Int d(t);
        bool s1 = sign;
        bool s2 = d.sign;
        bool rsign;
        Int rval;
        if(s1==s2){
            add((*this) , d , rval);
            *this = rval;
            return *this;
        }
        ///s1 is -ve s2 is +ve
        else if ((s1)&&(!s2)){
            Int temp; 
            (*this).negative(temp);
            if(temp > d ){
                sub(temp,d,rval);
                rval.sign=1;
                *this = rval;
                return *this;
            }
            else{
                sub(d,temp,rval);
                rval.sign=0;
                *this = rval;
                return *this;
            }
        }
        else{
            Int temp; 
            d.negative(temp);
            if(temp <= (*this) ){
                sub((*this),temp,rval);
                rval.sign=0;
                *this = rval;
                return *this;
            }
            else{
                sub(temp,(*this),rval);
                rval.sign=1;
                *this = rval;
                return *this;
            }
        }
    }
    Int& operator -= (long long &t){
        Int d(t);
        bool s1 = sign;
        bool s2 = d.sign;
        bool rsign;
        Int rval;
        if(s1!=s2){
            add((*this) , d , rval);
            rval.sign=s1;
            *this = rval;
            return *this;
        }
        ///both -ve
        else if (s1){
            if((*this) >= d ){
                sub(d,(*this),rval);
                rval.sign=0;
                *this = rval;
                return *this;
            }
            else{
                sub((*this),d,rval);
                rval.sign=1;
                *this = rval;
                return *this;
            }
        }
        else{
            if(d <= (*this) ){
                sub((*this),d,rval);
                rval.sign=0;
                *this = rval;
                return *this;
            }
            else{
                sub(d,(*this),rval);
                rval.sign=1;
                *this = rval;
                return *this;
            }
        }
    }
    Int& operator *= (long long &t){
        Int d(t);
        Int rval;
        mul(*(this),d,rval);
        *this = rval;
        return *this;
    }
    Int& operator /= (long long &tt){
        Int d(tt);
        Int rval,t;
        divide(*(this),d,rval,t);
        *this = rval;
        return *this;
    }
    Int& operator %= (long long &tt){
        Int d(tt);
        Int rval,t;
        divide(*(this),d,rval,t);
        *this = rval;
        return *this;
    }
    long long integer(){
        long long rval=0;
        int s = bytes(bits);
        long long exp = 1;
        for(int i=0;i<s;i++){
            rval +=(exp*Integer(num[i]));
            exp = (exp<<8);
        }
        if(sign)
            rval*=-1;
        return rval;
    }
    ///utility functions for random class
    void swap (int i){
        int size = bytes(this->bits);
        if(i>=(this->bits));
            i%=(this->bits);
        bool s1 = this->ith_bit(i).second;
        bool s2 = this->ith_bit(this->bits-1-i).second;
        int index = i>>3;
        int offset = i%8;
        int n = Integer(this->num[index]);
        if(s2){
            int t = (1)<<(offset);
            n = ((n) | (t));
        }
        else{
            int t = 255 - ((1)<(offset));
            n = ((n) & (t));
        }
        this->num[index] = (char)n;
        index=(this->bits-1-i)>>3;
        offset = (this->bits-1-i)%8;
        n = Integer(this->num[index]);
        if(s1){
            int t = (1)<<(offset);
            n = ((n) | (t));
        }
        else{
            int t = 255 - ((1)<(offset));
            n = ((n) & (t));
        }
        this->num[index] = (char)n;
    }
    int getsize(){
        return bytes(this->bits);
    }
    int getbits(){
        return bits;
    }
    void setbits(int n){
        bits = n;
    }
    void setnum(int n){
        num = new char[n];
    }
    void copy(string &a){
        int s = bytes(bits);
        for(int i=0;i<s;i++){
            a[i]=num[i];
        }
    }
    void eliminate(){
        int i=0;
        while(Integer(num[i])==0)
            i++;
        int s = bytes(bits);
        char* temp = new char[s-i];
        for(int t=i;t<s;t++)
            temp[t-i]=num[t];
        num=temp;
        bits-=(8*(i-1));
    }
};
void make_num(vector <bool> &temp , Int &d){
    int num=0;
    int t=1;
    int ctr=0;
    int index=0;
    for(int i=0;i<temp.size();i++){
        if((ctr%8==0)&&(ctr!=0)){
            d.num[index++]=num;
            num=0;
        }
        num+=(temp[i]*(t<<(i%8)));
        ctr++;
    }
    d.num[index]=num;
}
vector < bool > make_binary(Int &d){
    if((d.bits==1)&&(Integer(d.num[0])==0)){
        vector < bool > rval;
        rval.resize(1,0);
        return rval;
    }
    int t = bytes(d.bits);
    vector< bool > rval;
    int size=0;
    for(int i=0;i<t;i++){
        int num = Integer(d.num[i]);
        while(num){
            rval.push_back((num)&(1));
            num>>=1;
        }
        size+=8;
        rval.resize(size,0);
    }
    size=rval.size()-1;
    while((rval[size]==0)&&(size>=0))
        size--;
    rval.erase(rval.begin()+size+1,rval.end());
    return rval;
}
vec make_vec(Int &tt){
    vec rval;
    vector < bool > binary= make_binary(tt);
    if(binary.size()==1){
        rval.a.resize(1);
        rval.a[0]=binary[0];
        return rval;
    }
    int bits = binary.size();
    int digits = ceil(bits/3.321928);
    vector < short > g;
    g.resize(digits,0);
    while(bits--)
        shift(binary,g);
    int li = g.size()-1;
    while(g[li]==0)
        li--;
    g.erase(g.begin()+li+1,g.end());
    int size=g.size();
    rval.a.resize(size);
    for(int i=0;i<size;i++){
        rval.a[i]=g[size-1-i];
    }
    return rval;
}
void make_Int(vec &a , bool sign , Int &d){
    d.sign = sign;
    vector < bool > bin = binary(a);
    if(bin.size()==0)
        bin.push_back(0);
    d.bits = bin.size();
    d.num = new char[bytes(d.bits)];
    make_num(bin,d);
}
Int factorial(int n){
    vec temp,fact;
    fact.a.resize(1,1);
	for(int i=2;i<=n;i++){
		make(i,temp);
		vec t;
		multiply(fact,temp,t);
		fact.a.resize(t.a.size(),0);
        for(int z=0;z<t.a.size();z++)
            fact.a[z]=t.a[z];
	}
	vector < bool > bin = binary(fact);
    Int rval;
    rval.setbits(bin.size());
    rval.setnum(bytes(rval.getbits()));
    make_num(bin,rval);
    return rval;
}
class helper{
    public:
    long long a;
    long long b;
    long long c;
    long long d;
    helper(long long aa=0,long long bb=0,long long cc=0,long long dd=0){
        a=aa;
        b=bb;
        c=cc;
        d=dd;
    }
};
class Random{
    private:
    long long startbit;
    Int fact;
    long long size;
    long long arg_one;
    long long prev;
    public:
    Random(long long n){
        fact = factorial(n);
       // fact.eliminate();
        ifstream fin;
        fin.open("binary.dat",ios::in|ios::binary);
        if(!fin){
            fin.close();
            helper bb;
            bb.b=fact.getbits();
            int div = n%17;
            if(div<=1)
                div+=2;
            bb.a = bb.b /div;
            bb.c=n;
            bb.d=0;
            ofstream fout;
            fout.open("binary.dat",ios::out|ios::binary);
            fout.write((char*)&bb,sizeof(bb));
            fout.close();
            string a;
            a.resize(fact.getsize());
            fact.copy(a);
            int ss = fact.getsize();
            fout.open("binary.txt",ios::out);
            for(int i=0;i<ss;i++)
                fout<<a[i];
            fout.close();
            startbit=bb.a;
            size=bb.b;
            arg_one=bb.c;
            prev=bb.d;
        }
        else{
            helper bb;
            fin.read((char*)&bb,sizeof(bb));
            fin.close();
            if(bb.c==n){
                startbit = bb.a;
                size=bb.b;
                arg_one=n;
                prev=bb.d;
                string red;
                char ch;
                fin.open("binary.txt",ios::in);
                while(!(fin.eof())){
                    fin>>ch;
                    red+=ch;
                }
                fin.close();
                fact = Int(red,size);
            }
            else{
                bb.b=fact.getbits();
                int div = n%17;
                if(div<=1)
                    div+=2;
                bb.a = bb.b /div;
                bb.c=n;
                bb.d=0;
                ofstream fout;
                fout.open("binary.dat",ios::out|ios::binary);
                fout.write((char*)&bb,sizeof(bb));
                fout.close();
                string a;
                a.resize(fact.getsize());
                fact.copy(a);
                int ss = fact.getsize();
                fout.open("binary.txt",ios::out);
                for(int i=0;i<ss;i++)
                    fout<<a[i];
                fout.close();
                startbit=bb.a;
                size=bb.b;
                arg_one=bb.c;
                prev=bb.d;
            }
        }
    };
    Random(){
        startbit=0;
    }
    ~Random(){
        helper bb(this->startbit,this->size,this->arg_one,this->prev);
        string a;
        a.resize(fact.getsize());
        fact.copy(a);
        int ss = fact.getsize();
        ofstream fout;
        fout.open("binary.txt",ios::out);
        for(int i=0;i<ss;i++)
            fout<<a[i];
        fout.close();
        fout.open("binary.dat",ios::out|ios::binary);
        fout.write((char*)&bb,sizeof(bb));
        fout.close();
    }
    int getsize(){
        return size;
    }
    int random (long long n){
        if(n==0)
            return 0;
        int offset;
        if(n>arg_one)
            offset = n%arg_one;
        else
            offset = arg_one%n;
        int ctr=0;
        long long t=n;
        while(t){
            t>>=1;
            ctr++;
        }
        int si = (startbit + offset)%size;
        startbit = (startbit + offset + ctr)%size;
        vector < bool > bin;
        while(ctr){
            bin.push_back(fact.ith_bit(si).second);
            si++;
            if(si>=size)
                si-=size;
            fact.swap(si);
            ctr--;
        }
        int rval=0;
        for(int i=0;i<bin.size();i++)
            rval+=((1<<i)*(bin[i]));
        prev= (prev&((1<<(ctr))-1))^(rval);
        if(prev>n)
            return prev=prev%n;
        return prev;
    }
};
