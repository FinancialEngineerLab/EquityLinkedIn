
#include "rate.hpp"
#include <iostream>
#include "interpolater.hpp"

void Rate::set_const_rate(double v)
{
    //if vector is null
    // r : private member
    if(r.empty()==true && r.empty()==true)
    {
        ts.push_back(1.0);
        r.push_back(1.0);
    }
    else
    {
        std::vector<double>::iterator it;
        for(it=r.begin();it!=r.end();it++)
        {
            *it=v;
        }
    }
}
void Rate::print() const
{
    std::cout << std::fixed;
    std::cout.precision(4);
    auto iter_r=r.begin();
    
    for(auto iter=ts.begin();iter!=ts.end();iter++)
    {
        std::cout << *iter << " " << *iter_r << std::endl;
        iter_r++;
    }

}

int Rate::getSize() const
{
    return r.size();
}

double Rate::getIntpRate(double t) const
{
    interpolator f;
    return f.intp1d(r,ts,t);
}

std::vector<double> Rate::get_rate() const
{
    return r;
}


double Rate::getForward(double t) const
{
    double result, drdt;
    if(t<=ts.front())
    {
        result=r.front();
        return result;
    }
    else if(t>=ts.back())
    {
        result=r.back();
        return result;
    }
    std::vector<double>::const_iterator iter_r=r.begin();
    
    for(std::vector<double>::const_iterator
        iter=ts.begin();iter!=ts.end()-1;++iter)
    {
        if(t < *(iter+1) && t>=*iter)
        {
            //( (begin + x + 1)-(begin + x) )/(current+1 - current)
            // * : index! -> rate from " ts "  !
            drdt = (*(iter_r+1) - *iter_r) / (*(iter+1) -*iter);
            
            result = ((t - *iter) * *(iter_r+1) + (*(iter+1) - t) * *iter_r) / (*(iter+1) - *iter);//interpolated
            result = result + drdt * (t + 1 / 365); // d_t=1/365
            return result;
        }
        iter_r++; // begin to end
    }

    throw std::logic_error("can't find proper forward !");
    return 1;
}
